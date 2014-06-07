#include <sstream>

#include "Config.h"
#include "ArraySize.h"

namespace swirly {
namespace leap {

namespace {

typedef pair<string, vector<string>> StringValues;

StringValues splitEquals(string const& s) {
    StringValues result;
    auto pos = s.find('=');
    if (pos && pos != string::npos && pos != s.size() - 1) {
        result.first = s.substr(0, pos);

        stringstream ss(s.substr(pos + 1));
        string item;
        while (getline(ss, item, Config::VALUE_SEPARATOR))
            result.second.push_back(item);
    }
    return result;
}

const char* HANDS[] = {"left", "right"};
const char* FINGERS[] = {"thumb", "index", "middle", "ring", "little"};
const char* TOOLS[] = {"tool"};
const char* CIRCLE[] = {"circle"};
const char* KEYTAP[] = {"keytap"};
const char* SCREENTAP[] = {"screentap"};
const char* SWIPE[] = {"swipe"};

}  // namespace

Config::Config(Logger logger)
        : logger_(logger) {
    switches_["hand"] = SwitchArray(HANDS, arraysize(HANDS));
    switches_["finger"] = SwitchArray(FINGERS, arraysize(FINGERS));
    switches_["tool"] = SwitchArray(TOOLS, arraysize(TOOLS));

    switches_["circle"] = SwitchArray(CIRCLE, arraysize(CIRCLE));
    switches_["keytap"] = SwitchArray(KEYTAP, arraysize(KEYTAP));
    switches_["screentap"] = SwitchArray(SCREENTAP, arraysize(SCREENTAP));
    switches_["swipe"] = SwitchArray(SWIPE, arraysize(SWIPE));
}

void Config::addArgument(const string &str) {
    string s = (str[0] == OPTION_PREFIX) ? str.substr(1) : str;
    if (s[0] == FLAG_PREFIX) {
        if (s == "-verbose")
            verbose_ = true;
        else if (s == "-json")
            json_ = true;
        else if (s == "-all")
            all_ = true;
        else
            logger_(true, "ERROR: Don't understand flag %s.", s.c_str());
        return;
    }

    auto const value = splitEquals(s);
    auto const& name = value.first;
    auto const& values = value.second;
    if (name.empty() or values.empty()) {
        logger_(true, "ERROR: Don't understand argument %s.", s.c_str());
        return;
    }

    auto i = switches_.find(name);
    if (i != switches_.end()) {
        for (auto const& v: values)
            i->second.set(v);
    } else {
        logger_(true, "ERROR: Don't understand argument %s.", s.c_str());
    }
}

void Config::finishArguments() {
    for (auto& s: switches_)
        s.second.finish();
    dump();
}

void Config::dump() {
    for (auto& s: switches_)
        s.second.dump(logger_);
}

}  // namespace leap
}  // namespace swirly
