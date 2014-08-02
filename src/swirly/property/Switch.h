#pragma once

#include <swirly/base/Base.h>

namespace swirly {
namespace leap {

/** Switches are booleans that also have a third state - unset.
 *  Unset switches read as on by default. */
class Switch {
  public:
    Switch() : switch_(UNSET_SWITCH) {}

    Switch& operator=(bool on) {
        switch_ = on ? ON_SWITCH : OFF_SWITCH;
        return *this;
    }

    operator bool() const { return switch_ == ON_SWITCH; }
    bool isOn() const { return switch_ != UNSET_SWITCH; }

    void finish(bool on = true) {
        if (switch_ == UNSET_SWITCH)
            *this = on;
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
