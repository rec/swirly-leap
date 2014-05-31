#include "LeapMotion.h"

extern "C" {

#include "ext.h"
#include "ext_obex.h"

}

struct SwirlyLeap {
    t_object object_;
};

t_class* classPointer;

swirly::LeapMotion LEAP_MOTION;

void SwirlyLeap_bang(SwirlyLeap *x) {
    post("bang\n");
}

void SwirlyLeap_assist(SwirlyLeap *x, void *b, long m, long a, char *s) {
    sprintf(s, "%s %ld", m == ASSIST_INLET ? "inlet" : "outlet", a);
}

void SwirlyLeap_free(SwirlyLeap*) {}

void *SwirlyLeap_new(t_symbol *s, long argc, t_atom *argv)
{
    SwirlyLeap* sl = static_cast<SwirlyLeap*>(object_alloc(classPointer));
    if (!sl)
        return nullptr;
    t_object* object = &sl->object_;
    object_post(object, "%s", s->s_name);
    object_post(object, "Built: %s, %s", __DATE__, __TIME__);
    object_post(object, "%ld arguments", argc);

    for (auto i = 0; i < argc; ++i) {
        if ((argv + i)->a_type == A_SYM) {
            const char* s = atom_getsym(argv + i)->s_name;
            object_post(object,
                        "arg %ld: symbol (%s)",
                        i, s);
            LEAP_MOTION.addArgument(s, object);
        } else {
            object_error(object, "forbidden argument");
        }
    }

    object_post(object, "debug=%s", LEAP_MOTION.debug_ ? "true" : "false");
    for (auto const& addresses: LEAP_MOTION.addresses_) {
        object_post(object, "");
        for (auto const& a: addresses)
            object_post(object, a.c_str());
    }

    return object;
}

int C74_EXPORT main(void)
{
    classPointer = class_new(
        "SwirlyLeap",
        (method) SwirlyLeap_new,
        (method) SwirlyLeap_free,
        sizeof(SwirlyLeap),
        nullptr, A_GIMME, 0);

  class_addmethod(classPointer, (method)SwirlyLeap_assist, "assist", A_CANT, 0);
  class_addmethod(classPointer, (method)SwirlyLeap_bang, "bang", 0);

	class_register(CLASS_BOX, classPointer);
	return 0;
}
