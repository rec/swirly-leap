#pragma include once

#include <sstream>
#include <string>
#include <vector>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

using namespace std;

namespace swirly {

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

    void bang();
    void assist(void *b, long m, long a, char *s);

    typedef vector<string> Address;
    typedef vector<Address> Addresses;

    Max *const max_;
    bool debug_ = false;
    bool json_ = false;
    bool all_ = false;
    Addresses addresses_;

    static auto const ADDRESS_SEPARATOR = '.';
    static auto const FLAG_PREFIX = '-';

    void addArgument(const string &s);
};

}  // namespace swirly
