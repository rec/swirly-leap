#include <sstream>

#include "MaxObject.h"
#include "Config.h"

#include "leap/Leap.h"

namespace swirly {
namespace leap {

t_class* MaxObject::CLASS_POINTER;

void MaxObject::maxRegister() {
    CLASS_POINTER = class_new(
        "SwirlyLeap",
        (method) maxNew,
        (method) maxFree,
        sizeof(Max),
        nullptr, A_GIMME, 0);
    class_addmethod(CLASS_POINTER,
                    (method) MaxObject::maxAssist, "assist", A_CANT, 0);
    class_addmethod(CLASS_POINTER,
                    (method) MaxObject::maxBang, "bang", 0);
    class_register(CLASS_BOX, CLASS_POINTER);
}

void MaxObject::maxFree(Max* max) {
    delete max->maxObject_;
}

void* MaxObject::maxNew(t_symbol *s, long argc, t_atom *argv) {
    Max* max = static_cast<Max*>(object_alloc(CLASS_POINTER));
    if (max)
        max->maxObject_ = new MaxObject(max, s, argc, argv);
    return max;
}

void MaxObject::maxBang(Max* max) {
    max->maxObject_->bang();
}

void MaxObject::maxAssist(Max *max, void *b, long m, long a, char *s) {
    max->maxObject_->assist(b, m, a, s);
}

MaxObject::~MaxObject() {}

MaxObject::MaxObject(Max* max, t_symbol *s, long argc, t_atom *argv)
        : max_(max), config_(new Config) {
    t_object* object = &max_->object_;
    object_post(object, "%s", s->s_name);
    object_post(object, "Built: %s, %s", __DATE__, __TIME__);
    object_post(object, "%ld arguments", argc);

    for (auto i = 0; i < argc; ++i) {
        if ((argv + i)->a_type == A_SYM) {
            const char* s = atom_getsym(argv + i)->s_name;
            object_post(object,
                        "arg %ld: symbol (%s)",
                        i, s);
            config_->addArgument(s, object);
        } else {
            object_error(object, "forbidden argument");
        }
    }

    object_post(object, "debug=%s", config_->debug_ ? "true" : "false");
    for (auto const& addresses: config_->addresses_) {
        object_post(object, "");
        for (auto const& a: addresses)
            object_post(object, a.c_str());
    }
}

void MaxObject::bang() {
    post("bang!\n");
}

void MaxObject::assist(void *b, long m, long a, char *s) {
    sprintf(s, "%s %ld", m == ASSIST_INLET ? "inlet" : "outlet", a);
}

}  // namespace leap
}  // namespace swirly
