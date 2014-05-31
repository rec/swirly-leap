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

typedef vector<string> Address;
typedef vector<Address> Addresses;

struct LeapMotion {
    bool debug_ = false;
    bool json_ = false;
    bool all_ = false;
    Addresses addresses_;

    static auto const ADDRESS_SEPARATOR = '.';
    static auto const FLAG_PREFIX = '-';

    void addArgument(const string &s, t_object* object) {
        if (s[0] == FLAG_PREFIX) {
            if (s == "-debug")
                debug_ = true;
            else if (s == "-json")
                json_ = true;
            else if (s == "-all")
                all_ = true;
            else
                object_post(object, "ERROR: Didn't understand flag %s.",
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
};

}  // namespace swirly
