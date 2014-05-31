#pragma include once

#include "Base.h"

namespace swirly {
namespace leap {

struct Config;

class MaxObject {
  public:
    static void maxRegister();

  private:
    struct Max {
        t_object object_;
        MaxObject *maxObject_;
    };

    MaxObject(Max* max, t_symbol *s, long argc, t_atom *argv);
    ~MaxObject();

    static void maxFree(Max*);
    static void* maxNew(t_symbol *s, long argc, t_atom *argv);

    static void maxBang(Max*);
    static void maxAssist(Max *max, void *b, long m, long a, char *s);

    void bang();
    void assist(void *b, long m, long a, char *s);

    Max *const max_;
    unique_ptr<Config> config_;

    static t_class* CLASS_POINTER;
};

}  // namespace leap
}  // namespace swirly
