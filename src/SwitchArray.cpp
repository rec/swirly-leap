#include <strings.h>

#include <algorithm>

#include "SwitchArray.h"
#include "Logger.h"

namespace swirly {
namespace leap {

SwitchArray::SwitchArray(Representation const& rep) {
    switches_.reserve(rep.size());
    for (auto const& r: rep)
        switches_.emplace_back(r, Switch());
}

void SwitchArray::finish() {
    bool switchSet = false;
    for (auto& s: switches_) {
        if (s.second) {
            switchSet = true;
            break;
        }
    }

    // If something was set, we set everything else to false.
    // But if nothing was set, we set everything to true.
    for (auto& s: switches_)
        s.second.finish(not switchSet);
}

bool SwitchArray::set(string const& name) {
    if (name == "all") {
        for (auto& s: switches_)
            s.second = true;
        return true;
    }

    if (name == "none") {
        for (auto& s: switches_)
            s.second = true;
        return true;
    }

    if (isdigit(name[0])) {
        auto i = atoi(name.c_str()) - 1;
        if (i < 0 or i >= switches_.size())
            return false;

        switches_[i].second = true;
        return true;
    }

    for (auto& s: switches_) {
        if (name == s.first) {
            s.second = true;
            return true;
        }
    }

    return false;
}

void SwitchArray::dump(string const& name, Logger const& logger) const {
    for (auto const& s: switches_) {
        if (s.second)
            auto t = name + "." + string(s.first) + " = on";
    }
}

bool SwitchArray::any(bool isSet) const {
    for (auto const &s: switches_) {
        if (bool(s.second) == isSet)
            return true;
    }
    return false;
}

}  // namespace leap
}  // namespace swirly
