#include <strings.h>
#include <stdlib.h>

#include <array>

#include "Base.h"

namespace swirly {
namespace leap {

enum Switch { UNSET_SWITCH, OFF_SWITCH, ON_SWITCH };

inline const char* name(Switch s) {
    return s == UNSET_SWITCH ? "(unset)" :
           s == OFF_SWITCH ? "off" : "on";
}

template <int SIZE>
class SwitchArray {
  public:
    SwitchArray(const char** names) {
        enabled_.fill(UNSET_SWITCH);
        for (auto i = 0; i < SIZE; ++i)
            names_[i] = names[i];
    }

    void finish() {
        auto setting = wasSet_ ? OFF_SWITCH : ON_SWITCH;
        for (auto& s: enabled_) {
            if (s == UNSET_SWITCH)
                s = setting;
        }
    }

    bool isEnabled(uint i) const {
        return i < SIZE and enabled_[i] == ON_SWITCH;
    }

    bool set(string const& name) {
        bool success = true;
        if (name == "all") {
            enabled_.fill(ON_SWITCH);
        } else if (name == "none") {
            enabled_.fill(OFF_SWITCH);
        } else if (isdigit(name[0])) {
            auto i = atoi(name.c_str()) - 1;
            success = i >= 0 and i < SIZE;
            if (success)
                enabled_[i] = ON_SWITCH;
        } else {
            success = false;
            for (auto i = 0; !success and i < SIZE; ++i) {
                if (names_[i] == name) {
                    enabled_[i] = ON_SWITCH;
                    success = true;
                }
            }
        }

        wasSet_ = wasSet_ or success;
        return success;
    }

    template <typename Logger>
    void dump(Logger logger) {
        for (auto i = 0; i < SIZE; ++i) {
            auto s = string(names_[i]) + "=" + name(enabled_[i]);
            logger(false, "%s", s.c_str());
        }
    }

  private:
    bool wasSet_ = false;
    array<Switch, SIZE> enabled_;
    array<const char*, SIZE> names_;
};

}  // namespace leap
}  // namespace swirly
