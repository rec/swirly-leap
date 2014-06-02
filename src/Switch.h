#include <strings.h>
#include <stdlib.h>

#include <array>

#include "Base.h"

namespace swirly {
namespace leap {

enum Switch { UNSET_SWITCH, OFF_SWITCH, ON_SWITCH };

template <int SIZE>
class SwitchArray {
  public:
    SwitchArray() {
        items_.fill(UNSET_SWITCH);
    }

    void finish() {
        auto setting = wasSet_ ? OFF_SWITCH : ON_SWITCH;
        for (auto& s: items_) {
            if (s == UNSET_SWITCH)
                s = setting;
        }
    }

    bool isEnabled(uint i) const {
        return i < SIZE and items_[i] == ON_SWITCH;
    }

    bool set(string const& name) {
        bool success = true;
        if (name == "all") {
            items_.fill(ON_SWITCH);
        } else if (name == "none") {
            items_.fill(OFF_SWITCH);
        } else if (isdigit(name[0])) {
            auto i = atoi(name.c_str());
            success = (i < 0 || i >= SIZE);
            if (success)
                items_[i] = ON_SWITCH;
        } else {
            success = false;
        }

        wasSet_ = wasSet_ or success;
        return success;
    }

  private:
    bool wasSet_ = false;
    array<Switch, SIZE> items_;
};

}  // namespace leap
}  // namespace swirly
