#include "leap/Leap.h"

#include "Config.h"
#include "ArraySize.h"
#include "PropertySwitchArray.h"
#include "Split.h"

using namespace Leap;

namespace swirly {
namespace leap {

Config::Config(Logger const& logger)
        : logger_(logger), switches_(new PropertySwitchArrayMap) {
    switches_->add<Hand>({"left", "right"});
    switches_->add<Finger>({"thumb", "index", "middle", "ring", "pinky"});
    switches_->add<Tool>({"tool"});
    switches_->add<CircleGesture>({"circle"});
    switches_->add<KeyTapGesture>({"keytap"});
    switches_->add<ScreenTapGesture>({"screentap"});
    switches_->add<SwipeGesture>({"swipe"});
}

Config::~Config() {}

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
            logger_.err("Don't understand flag " + s);
        return;
    }

    auto const value = splitEquals(s, Config::VALUE_SEPARATOR);
    auto const& name = value.first;
    auto const& values = value.second;
    if (name.empty() or values.empty()) {
        logger_.err("Don't understand argument " + s);
        return;
    }

    auto i = switches_->find(name);
    if (i != switches_->end()) {
        for (auto const& v: values) {
            if (!i->second->set(v))
                logger_.err("Don't understand switch value " + s);
        }
    } else {
        logger_.err("Don't understand argument " + s);
    }
}

void Config::finishArguments() {
    for (auto& s: *switches_)
        s.second->finish();
    updateCallbacks();
    dump();
}

void Config::dump() {
    for (auto& s: *switches_)
        s.second->dump(s.first, logger_);
}

}  // namespace leap
}  // namespace swirly
