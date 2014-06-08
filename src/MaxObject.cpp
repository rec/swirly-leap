#include <sstream>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "MaxObject.h"
#include "Callback.h"
#include "LeapMotion.h"

namespace swirly {
namespace leap {

namespace {

t_class* CLASS_POINTER;

} // namespace

using namespace std::placeholders;

MaxObject::MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv)
        : maxStruct_(maxStruct),
          object_(&maxStruct_->object_),
          logger_(bind(&MaxObject::log, this, _1, _2)),
          leap_(new LeapMotion(logger_)) {
    log(s->s_name);
    log("Built: " __DATE__ ", " __TIME__);

    outlet_ = outlet_new(maxStruct_, nullptr);
    leap_->frameHandler_.setOutlet(outlet_);

    for (auto i = 0; i < argc; ++i) {
        if ((argv + i)->a_type == A_SYM)
            leap_->config_.addArgument(atom_getsym(argv + i)->s_name);
        else
            log("forbidden argument", false);
    }
    leap_->config_.finishArguments();
}

MaxObject::~MaxObject() {}

void MaxObject::log(string const& message, bool error) {
    if (error)
        object_error(object_, "%s", message.c_str());
    else
        object_post(object_, "%s", message.c_str());
}

void MaxObject::bang() {
    if (!leap_->listener_.sendFrame())
        log("bang: Can't send frame while running.");
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
