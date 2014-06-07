#include "SwitchArray.h"

namespace swirly {
namespace leap {

SwitchArray::SwitchArray(const char** names, int size) {
    switches_.reserve(size);
    for (auto i = 0; i < size; ++i)
        switches_.emplace_back(names[i], Switch());
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
    return properties_ and properties_->addProperty(name);
}

void SwitchArray::dump(Logger logger) {
    for (auto const& s: switches_) {
        auto t = s.first + "=" + s.second.name();
        logger(false, "%s", t.c_str());
    }
}

}  // namespace leap
}  // namespace swirly
