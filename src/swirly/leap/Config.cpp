#include <leap/Leap.h>

#include <swirly/leap/Config.h>

#include <swirly/base/ArraySize.h>
#include <swirly/represent/MasterRepresenter.h>
#include <swirly/represent/PartRepresenterMap.h>
#include <swirly/util/Split.h>

using namespace Leap;

namespace swirly {
namespace leap {

Config::Config(Logger const& logger, Controller& controller)
        : logger_(logger),
          masterRepresenter_(new MasterRepresenter(logger, controller)) {
}

Config::~Config() {}

void Config::addArgument(const string &str) {
    string s = (str[0] == OPTION_PREFIX) ? str.substr(1) : str;
    if (s[0] == FLAG_PREFIX) {
        if (s == "-verbose")
            verbose_ = true;
        else if (s == "-all")
            all_ = true;
        else
            logger_.err("Don't understand flag " + s);
        return;
    }

    masterRepresenter_->set(s);
}

void Config::finish() {
    if (all_)
        masterRepresenter_->setAll();

    masterRepresenter_->finish();
    updateCallbacks();
    dump();
}

void Config::dump() {
    masterRepresenter_->dump();
}

Representation Config::getHand() const {
    Representation rep;
    if (auto hand = masterRepresenter_->getPartMap<Hand>())
        hand->describe(rep);
    return rep;
}

Representation Config::setHand(Representation const& rep) {
    Representation failure;
    return failure;
}

}  // namespace leap
}  // namespace swirly
