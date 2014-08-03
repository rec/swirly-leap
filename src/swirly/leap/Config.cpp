#include <leap/Leap.h>

#include <swirly/leap/Config.h>

#include <swirly/base/ArraySize.h>
#include <swirly/property/MasterRepresenter.h>
#include <swirly/property/PartRepresenterMap.h>
#include <swirly/util/Split.h>

using namespace Leap;

namespace swirly {
namespace leap {

Config::Config(Logger const& logger)
        : logger_(logger), masterRepresenter_(new MasterRepresenter) {
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

    masterRepresenter_->set(s, logger_);
}

void Config::finishArguments() {
    if (all_)
        masterRepresenter_->setAll();

    masterRepresenter_->finish();
    updateCallbacks();
    dump();
}

void Config::dump() {
    masterRepresenter_->dump(logger_);
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
