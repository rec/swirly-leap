#include <sstream>

#include "MaxObject.h"
#include "Config.h"

namespace swirly {
namespace leap {

namespace {

t_class* CLASS_POINTER;

class MaxObject;

// This is the structure that Max will initialize.
struct MaxStruct {
    t_object object_;
    MaxObject *maxObject_;
};

// This is the C++ class contained in this structure.
class MaxObject {
  public:
    MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv)
            : maxStruct_(maxStruct) {
        t_object* object = &maxStruct_->object_;
        object_post(object, "%s", s->s_name);
        object_post(object, "Built: %s, %s", __DATE__, __TIME__);
        object_post(object, "%ld arguments", argc);

        for (auto i = 0; i < argc; ++i) {
            if ((argv + i)->a_type == A_SYM) {
                const char* s = atom_getsym(argv + i)->s_name;
                object_post(object,
                            "arg %ld: symbol (%s)",
                            i, s);
                config_.addArgument(s, object);
            } else {
                object_error(object, "forbidden argument");
            }
        }
        config_.dump(object);
    }

  private:
    MaxStruct *const maxStruct_;
    Config config_;
};

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
    post("bang!\n");
}

void assist(MaxStruct *max, void *b, long m, long a, char *s) {
    sprintf(s, "%s %ld", m == ASSIST_INLET ? "inlet" : "outlet", a);
}

} // namespace

void registerMaxObject() {
    CLASS_POINTER = class_new("SwirlyLeap",
        (method) maxNew, (method) maxDelete,
        sizeof(MaxStruct), nullptr, A_GIMME, 0);

    class_addmethod(CLASS_POINTER, (method) assist, "assist", A_CANT, 0);
    class_addmethod(CLASS_POINTER, (method) bang, "bang", 0);
    class_register(CLASS_BOX, CLASS_POINTER);
}

}  // namespace leap
}  // namespace swirly
