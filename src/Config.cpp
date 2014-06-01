#include "Config.h"

namespace swirly {
namespace leap {

void Config::addArgument(const string &str, t_object* object) {
    string s = (str[0] == OPTION_PREFIX) ? str.substr(1) : str;
    if (s[0] == FLAG_PREFIX) {
        if (s == "-verbose")
            verbose_ = true;
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

void Config::dump(t_object* object) {
}

}  // namespace leap
}  // namespace swirly
