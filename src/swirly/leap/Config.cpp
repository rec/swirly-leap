#include <leap/Leap.h>

#include <swirly/leap/Config.h>

#include <swirly/base/ArraySize.h>
#include <swirly/property/PropertySwitchArray.h>
#include <swirly/property/TypedProperties.h>
#include <swirly/util/Split.h>

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

Representation Config::getHand() const {
    Representation rep;
    auto hand = switches_->get<Hand>();

    if (hand->any() and not hand->properties_.empty()) {
        if (hand->any(false)) {
            for (auto& h: hand->switches_)
                if (h.second)
                    rep.push_back(h.first);
        }

        for (auto& h: hand->properties_.properties())
            rep.push_back(h.first);

    } else {
        logger_.err("No hand!");
    }

    return rep;
}

Representation Config::setHand(Representation const& rep) {
    Representation failure;
    return failure;
}


}  // namespace leap
}  // namespace swirly
