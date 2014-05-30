#include <string>

extern "C" {

#include "ext.h"
#include "ext_obex.h"

}

struct SwirlyLeap {
    t_object ob;
};

t_class* classPointer;

void SwirlyLeap_bang(SwirlyLeap *x) {
    post("bang\n");
}

void SwirlyLeap_assist(SwirlyLeap *x, void *b, long m, long a, char *s) {
    sprintf(s, "%s %ld", m == ASSIST_INLET ? "inlet" : "outlet", a);
}

void SwirlyLeap_free(SwirlyLeap*) {}

void *SwirlyLeap_new(t_symbol *s, long argc, t_atom *argv)
{
    auto x = static_cast<SwirlyLeap*>(object_alloc(classPointer));
    if (x) {
        object_post((t_object *)x, "%s", s->s_name);
        object_post((t_object *)x, "Built: %s, %s", __DATE__, __TIME__);
        object_post((t_object *)x, "%ld arguments", argc);

        for (auto i = 0; i < argc; ++i) {
            if ((argv + i)->a_type == A_SYM) {
                object_post((t_object *)x,
                            "arg %ld: symbol (%s)",
                            i, atom_getsym(argv + i)->s_name);
            } else {
                object_error((t_object *)x, "forbidden argument");
            }
        }
    }
    return x;
}

int C74_EXPORT main(void)
{
    classPointer = class_new(
        "SwirlyLeap",
        (method) SwirlyLeap_new,
        (method) SwirlyLeap_free,
        sizeof(SwirlyLeap),
        nullptr, A_GIMME, 0);

  class_addmethod(classPointer, (method)SwirlyLeap_assist, "assist",		A_CANT, 0);
  class_addmethod(classPointer, (method)SwirlyLeap_bang, "bang", 0);

	class_register(CLASS_BOX, classPointer);
	return 0;
}
