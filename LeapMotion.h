#pragma include once

#include <memory>
#include <string>
#include <vector>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

using namespace std;

namespace swirly {

struct LeapConfig;

class LeapMotion {
  public:
    static void maxRegister();

    struct Max {
        t_object object_;
        LeapMotion *leapMotion_;
    };

    static void maxFree(Max*);
    static void* maxNew(t_symbol *s, long argc, t_atom *argv);

    static void maxBang(Max*);
    static void maxAssist(Max *max, void *b, long m, long a, char *s);

  private:
    static t_class* CLASS_POINTER;

    LeapMotion(Max* max, t_symbol *s, long argc, t_atom *argv);
    ~LeapMotion();

    void bang();
    void assist(void *b, long m, long a, char *s);

    Max *const max_;
    unique_ptr<LeapConfig> config_;
};

}  // namespace swirly
