#include "LeapMotion.h"

extern "C" {

#include "ext.h"
#include "ext_obex.h"

}

namespace swirly {

struct MaxLeapMotion {
    t_object object_;
    LeapMotion *leapMotion_;
};

t_class* classPointer;

void SwirlyLeap_bang(MaxLeapMotion *x) {
    post("bang\n");
}

void SwirlyLeap_assist(MaxLeapMotion *x, void *b, long m, long a, char *s) {
    sprintf(s, "%s %ld", m == ASSIST_INLET ? "inlet" : "outlet", a);
}

void SwirlyLeap_free(MaxLeapMotion* mlm) {
    delete mlm->leapMotion_;
}

void *SwirlyLeap_new(t_symbol *s, long argc, t_atom *argv) {
    MaxLeapMotion* mlm = static_cast<MaxLeapMotion*>(object_alloc(classPointer));
    if (!mlm)
        return nullptr;
    auto leapMotion = new LeapMotion;
    mlm->leapMotion_ = leapMotion;

    t_object* object = &mlm->object_;
    object_post(object, "%s", s->s_name);
    object_post(object, "Built: %s, %s", __DATE__, __TIME__);
    object_post(object, "%ld arguments", argc);

    for (auto i = 0; i < argc; ++i) {
        if ((argv + i)->a_type == A_SYM) {
            const char* s = atom_getsym(argv + i)->s_name;
            object_post(object,
                        "arg %ld: symbol (%s)",
                        i, s);
            leapMotion->addArgument(s, object);
        } else {
            object_error(object, "forbidden argument");
        }
    }

    object_post(object, "debug=%s", leapMotion->debug_ ? "true" : "false");
    for (auto const& addresses: leapMotion->addresses_) {
        object_post(object, "");
        for (auto const& a: addresses)
            object_post(object, a.c_str());
    }

    return object;
}

void main() {
    classPointer = class_new(
        "SwirlyLeap",
        (method) SwirlyLeap_new,
        (method) SwirlyLeap_free,
        sizeof(MaxLeapMotion),
        nullptr, A_GIMME, 0);

  class_addmethod(classPointer, (method)SwirlyLeap_assist, "assist", A_CANT, 0);
  class_addmethod(classPointer, (method)SwirlyLeap_bang, "bang", 0);

	class_register(CLASS_BOX, classPointer);
}

}  // namespace swirly

int C74_EXPORT main(void) {
    swirly::main();
    return 0;
}
