extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "MaxObject.h"
#include "Callback.h"
#include "LeapMotion.h"
#include "Split.h"

namespace swirly {
namespace leap {

namespace {

t_class* CLASS_POINTER;

} // namespace

using namespace std::placeholders;

MaxObject::MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv)
        : maxStruct_(maxStruct),
          object_(&maxStruct_->object_),
          leap_(new LeapMotion(*this)) {
    log(string(s->s_name) + ", built " __DATE__ ", " __TIME__);

    outlet_ = outlet_new(maxStruct_, nullptr);
    leap_->frameHandler_.setOutlet(outlet_);

    for (auto i = 0; i < argc; ++i) {
        if ((argv + i)->a_type == A_SYM)
            leap_->config_.addArgument(atom_getsym(argv + i)->s_name);
        else
            err("forbidden argument");
    }
    leap_->config_.finishArguments();
}

MaxObject::~MaxObject() {}

void MaxObject::log(string const& message) const {
    auto parts = split(message, '\r');
    for (auto& p: parts)
        object_post(object_, "%s", p.c_str());
}

void MaxObject::err(string const& message) const {
    auto parts = split(message, '\r');
    for (auto& p: parts)
        object_error(object_, "ERROR: %s", p.c_str());
}

void MaxObject::bang() {
    if (!leap_->listener_.sendFrame())
        err("bang: Can't send frame while running.");
}

void MaxObject::setRunning(bool isRunning) {
    leap_->config_.setRunning(isRunning);
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

void maxInt(MaxStruct *max, long n) {
    max->maxObject_->setRunning(n);
}

void bang(MaxStruct *max) {
    max->maxObject_->bang();
}

void start(MaxStruct *max) {
    max->maxObject_->setRunning(true);
}

void stop(MaxStruct *max) {
    max->maxObject_->setRunning(false);
}

void assist(MaxStruct *max, void *b, long m, long a, char *s) {
    auto message = (m == ASSIST_INLET) ?
            "bang, start, stop" : "leap data messages";
    sprintf(s, "%s %ld", message, a);
}

void registerMaxObject() {
    CLASS_POINTER = class_new("SwirlyLeap",
        (method) maxNew, (method) maxDelete,
        sizeof(MaxStruct), nullptr, A_GIMME, 0);

    class_addmethod(CLASS_POINTER, (method) assist, "assist", A_CANT, 0);
    class_addmethod(CLASS_POINTER, (method) bang, "bang", 0);
    class_addmethod(CLASS_POINTER, (method) start, "start", 0);
    class_addmethod(CLASS_POINTER, (method) stop, "stop", 0);
    class_addmethod(CLASS_POINTER, (method) maxInt, "int", A_LONG, 0);
    class_register(CLASS_BOX, CLASS_POINTER);
}

}  // namespace leap
}  // namespace swirly
