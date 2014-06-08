#include <sstream>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "MaxObject.h"
#include "Callback.h"
#include "LeapMotion.h"
#include "PropertiesToMax.h"

namespace swirly {
namespace leap {

namespace {

t_class* CLASS_POINTER;

} // namespace

MaxObject::MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv)
        : maxStruct_(maxStruct),
          object_(&maxStruct_->object_),
          logger_(bind(
              &MaxObject::log, this,
              placeholders::_1, placeholders::_2, placeholders::_3)),
          leap_(new LeapMotion(logger_)) {
    object_post(object_, "%s", s->s_name);
    object_post(object_, "Built: %s, %s", __DATE__, __TIME__);
    object_post(object_, "%ld arguments", argc);

    for (auto i = 0; i < argc; ++i) {
        if ((argv + i)->a_type == A_SYM) {
            const char* s = atom_getsym(argv + i)->s_name;
            object_post(object_,
                        "arg %ld: symbol (%s)",
                        i, s);
            leap_->config_.addArgument(s);
        } else {
            object_error(object_, "forbidden argument");
        }
    }
    leap_->config_.finishArguments();
    leap_->config_.dump();
    outlet_ = outlet_new(maxStruct_, nullptr);
    leap_->frameHandler_.setOutlet(outlet_);
}

MaxObject::~MaxObject() {}

void MaxObject::log(bool error, const char* format, const char* value) {
    if (error)
        object_error(object_, format, value);
    else
        object_post(object_, format, value);
}

void MaxObject::bang() {
    if (!leap_->listener_.sendFrame())
        log(true, "%s", "bang: Can't send frame while running.");
}

void MaxObject::run() {
    leap_->config_.setRunning(true);
}

void MaxObject::stop() {
    leap_->config_.setRunning(false);
}

void maxDelete(MaxStruct *max) {
    delete max->maxObject_;
}

void* maxNew(t_symbol *s, long argc, t_atom *argv) {
    MaxStruct* max = (MaxStruct*) object_alloc(CLASS_POINTER);
    if (max)
        max->maxObject_ = new MaxObject(max, s, argc, argv);
    return max;
}

void bang(MaxStruct *max) {
    max->maxObject_->bang();
}

void run(MaxStruct *max) {
    max->maxObject_->run();
}

void stop(MaxStruct *max) {
    max->maxObject_->stop();
}

void assist(MaxStruct *max, void *b, long m, long a, char *s) {
    auto message = (m == ASSIST_INLET) ?
            "bang, run, stop, set parameters" : "leap data messages";
    sprintf(s, "%s %ld", message, a);
}

void registerMaxObject() {
    CLASS_POINTER = class_new("SwirlyLeap",
        (method) maxNew, (method) maxDelete,
        sizeof(MaxStruct), nullptr, A_GIMME, 0);

    class_addmethod(CLASS_POINTER, (method) assist, "assist", A_CANT, 0);
    class_addmethod(CLASS_POINTER, (method) bang, "bang", 0);
    class_addmethod(CLASS_POINTER, (method) run, "run", 0);
    class_addmethod(CLASS_POINTER, (method) stop, "stop", 0);
    class_register(CLASS_BOX, CLASS_POINTER);
}

}  // namespace leap
}  // namespace swirly
