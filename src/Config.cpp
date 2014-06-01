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
        while (getline(ss, item, '+'))
            result.second.push_back(item);
    }
    return result;
}

}  // namespace

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
            object_error(object, "ERROR: Don't understand flag %s.", s.c_str());
        return;
    }

    auto const value = splitEquals(s);
    auto const& name = value.first;
    auto const& values = value.second;
    if (name.empty() or values.empty()) {
        object_error(object, "ERROR: Don't understand argument %s.", s.c_str());
        return;
    }

    typedef void (Config::*Method)(string const&);
    Method method;
    if (name == "finger")
        method = &Config::finger;
    else if (name == "hand")
        method = &Config::hand;
    else if (name == "tool")
        method = &Config::tool;
    else if (name == "swipe")
        method = &Config::swipe;
    else if (name == "circle")
        method = &Config::circle;
    else if (name == "screentap")
        method = &Config::screentap;
    else if (name == "keytap")
        method = &Config::keytap;
    else if (name != "finger") {
        object_error(object, "ERROR: Don't understand argument %s.", s.c_str());
        return;
    }

    for (auto const& v: values)
        (this->*method)(v);
}

void Config::dump(t_object* object) {
}

void Config::finger(string const& s) {
    auto t = "finger=" + s;
    post(t.c_str());
}

void Config::hand(string const& s) {
    auto t = "hand=" + s;
    post(t.c_str());
}

void Config::tool(string const& s) {
    auto t = "tool=" + s;
    post(t.c_str());
}

void Config::swipe(string const& s) {
    auto t = "swipe=" + s;
    post(t.c_str());
}

void Config::circle(string const& s) {
    auto t = "circle=" + s;
    post(t.c_str());
}

void Config::screentap(string const& s) {
    auto t = "screentap=" + s;
    post(t.c_str());
}

void Config::keytap(string const& s) {
    auto t = "keytap=" + s;
    post(t.c_str());
}

}  // namespace leap
}  // namespace swirly
