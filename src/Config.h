#include "Base.h"

namespace swirly {
namespace leap {

struct Config {
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

    void dump(t_object* object) {
        object_post(object, "debug=%s", debug_ ? "true" : "false");
        for (auto const& addresses: addresses_) {
            object_post(object, "");
            for (auto const& a: addresses)
                object_post(object, a.c_str());
        }
    }
};

}  // namespace leap
}  // namespace swirly
