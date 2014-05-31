#include "Base.h"

namespace swirly {

struct LeapConfig {
    typedef vector<string> Address;
    typedef vector<Address> Addresses;

    Addresses addresses_;

    bool debug_ = false;
    bool json_ = false;
    bool all_ = false;
    bool poll_ = false;

    static auto const ADDRESS_SEPARATOR = '.';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(const string &str, t_object* object) {
        string s = (str[0] == OPTION_PREFIX) ? str.substr(1) : str;
        if (s[0] == FLAG_PREFIX) {
            if (s == "-debug")
                debug_ = true;
            else if (s == "-json")
                json_ = true;
            else if (s == "-all")
                all_ = true;
            else if (s == "-poll")
                poll_ = true;
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
