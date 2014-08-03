#include <leap/Leap.h>

#include <swirly/leap/Config.h>

#include <swirly/base/ArraySize.h>
#include <swirly/property/SwitchedPartRepresenterMap.h>
#include <swirly/property/PartRepresenterMap.h>
#include <swirly/util/Split.h>

using namespace Leap;

namespace swirly {
namespace leap {

Config::Config(Logger const& logger)
        : logger_(logger), switches_(new SwitchedPartRepresenterMapMap) {
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

    switches_->set(s, logger_);
}

void Config::finishArguments() {
    switches_->finish();
    updateCallbacks();
    dump();
}

void Config::dump() {
    switches_->dump(logger_);
}

Representation Config::getHand() const {
    Representation rep;
    if (auto hand = switches_->get<Hand>())
        hand->represent(rep);
    return rep;
}

Representation Config::setHand(Representation const& rep) {
    Representation failure;
    return failure;
}

}  // namespace leap
}  // namespace swirly
