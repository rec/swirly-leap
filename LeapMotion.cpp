#include "LeapMotion.h"

namespace swirly {

t_class* LeapMotion::CLASS_POINTER;

void LeapMotion::maxRegister() {
    CLASS_POINTER = class_new(
        "SwirlyLeap",
        (method) maxNew,
        (method) maxFree,
        sizeof(Max),
        nullptr, A_GIMME, 0);
    class_addmethod(CLASS_POINTER,
                    (method) LeapMotion::maxAssist, "assist", A_CANT, 0);
    class_addmethod(CLASS_POINTER,
                    (method) LeapMotion::maxBang, "bang", 0);
    class_register(CLASS_BOX, CLASS_POINTER);
}

void LeapMotion::maxFree(Max* max) {
    delete max->leapMotion_;
}

void* LeapMotion::maxNew(t_symbol *s, long argc, t_atom *argv) {
    Max* max = static_cast<Max*>(object_alloc(CLASS_POINTER));
    if (max)
        max->leapMotion_ = new LeapMotion(max, s, argc, argv);
    return max;
}

void LeapMotion::maxBang(Max* max) {
    max->leapMotion_->bang();
}

void LeapMotion::maxAssist(Max *max, void *b, long m, long a, char *s) {
    max->leapMotion_->assist(b, m, a, s);
}

LeapMotion::LeapMotion(Max* max, t_symbol *s, long argc, t_atom *argv)
        : max_(max) {
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
            addArgument(s);
        } else {
            object_error(object, "forbidden argument");
        }
    }

    object_post(object, "debug=%s", debug_ ? "true" : "false");
    for (auto const& addresses: addresses_) {
        object_post(object, "");
        for (auto const& a: addresses)
            object_post(object, a.c_str());
    }
}

void LeapMotion::bang() {
    post("bang!\n");
}

void LeapMotion::assist(void *b, long m, long a, char *s) {
    sprintf(s, "%s %ld", m == ASSIST_INLET ? "inlet" : "outlet", a);
}


void LeapMotion::addArgument(const string &s) {
    if (s[0] == FLAG_PREFIX) {
        if (s == "-debug")
            debug_ = true;
        else if (s == "-json")
            json_ = true;
        else if (s == "-all")
            all_ = true;
        else
            object_post(&max_->object_, "ERROR: Didn't understand flag %s.",
                        s.c_str());
    } else {
        Address address;
        stringstream ss(s);
        string item;
        while (getline(ss, item, ADDRESS_SEPARATOR))
            address.push_back(item);
        addresses_.push_back(address);
    }
}

}  // namespace swirly
