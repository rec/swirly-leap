#pragma include once

#include "Base.h"

namespace swirly {
namespace leap {

class Switch {
  public:
    Switch() : switch_(UNSET_SWITCH) {}

    void set(bool on) {
        switch_ = on ? ON_SWITCH : OFF_SWITCH;
    }

    bool isEnabled() const {
        return switch_ == ON_SWITCH;
    }

    void finish(bool on = true) {
        if (switch_ == UNSET_SWITCH)
            set(on);
    }

    const char* name() const {
        return switch_ == UNSET_SWITCH ? "(unset)"
                : switch_ == OFF_SWITCH ? "off"
                : "on";
    }

  private:
    enum Value { UNSET_SWITCH, OFF_SWITCH, ON_SWITCH };

    Value switch_;
};

}  // namespace leap
}  // namespace swirly
