#include "SwitchArray.h"

namespace swirly {
namespace leap {

SwitchArray::SwitchArray(const char** names, int size) {
    enabled_.resize(size);
    names_.reserve(size);
    for (auto i = 0; i < size; ++i)
        names_.push_back(names[i]);
}

void SwitchArray::finish() {
    for (auto& s: enabled_)
        s.finish(unset_);
}

bool SwitchArray::isEnabled(uint i) const {
    return i < enabled_.size() and enabled_[i].isEnabled();;
}

bool SwitchArray::set(string const& name) {
    bool success = true;
    if (name == "all") {
        for (auto& e: enabled_)
            e.set(true);
    } else if (name == "none") {
        for (auto& e: enabled_)
            e.set(false);
    } else if (isdigit(name[0])) {
        auto i = atoi(name.c_str()) - 1;
        success = i >= 0 and i < enabled_.size();
        if (success)
            enabled_[i].set(true);
    } else {
        success = false;
        for (auto i = 0; i < enabled_.size(); ++i) {
            if (names_[i] == name) {
                enabled_[i].set(true);
                success = true;
                break;
            }
        }
    }

    unset_ = unset_ and !success;
    return success;
}

}  // namespace leap
}  // namespace swirly
