#include <sstream>

#include "Config.h"

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

}  // namespace

Config::Config(Logger logger)
        : hands_{HANDS},
          fingers_{FINGERS, FINGERS},
          logger_(logger) {
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

    typedef void (Config::*Method)(string const&);
    Method method;
    if (name == "circle")
        method = &Config::circle;
    else if (name == "finger")
        method = &Config::finger;
    else if (name == "hand")
        method = &Config::hand;
    else if (name == "keytap")
        method = &Config::keytap;
    else if (name == "tool")
        method = &Config::tool;
    else if (name == "screentap")
        method = &Config::screentap;
    else if (name == "swipe")
        method = &Config::swipe;
    else {
        logger_(true, "ERROR: Don't understand argument %s.", s.c_str());
        return;
    }

    for (auto const& v: values)
        (this->*method)(v);
}

void Config::finishArguments() {
    fingers_[0].finish();
    fingers_[1].finish();
    hands_.finish();
    fingers_[0].dump(logger_);
    hands_.dump(logger_);
}

void Config::dump() {
}

void Config::circle(string const& s) {
}

void Config::finger(string const& s) {
    if (!fingers_[0].set(s))
        logger_(true, "ERROR: Couldn't set finger %s", s.c_str());
    fingers_[1].set(s);
}

void Config::hand(string const& s) {
    if (!hands_.set(s))
        logger_(true, "ERROR: Couldn't set hand %s", s.c_str());
}

void Config::keytap(string const& s) {
}

void Config::tool(string const& s) {
}

void Config::screentap(string const& s) {
}

void Config::swipe(string const& s) {
}

}  // namespace leap
}  // namespace swirly
