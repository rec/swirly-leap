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
                : switch_ == OFF_SWITCH ? "off" : "on";
    }

  private:
    enum Value { UNSET_SWITCH, OFF_SWITCH, ON_SWITCH };

    Value switch_;
};

class SwitchArray {
  public:
    SwitchArray() {}
    SwitchArray(const char** names, int size);

    void finish();
    bool isEnabled(uint i) const;
    bool set(string const& name);

    template <typename Logger>
    void dump(Logger logger) {
        for (auto i = 0; i < enabled_.size(); ++i) {
            auto s = string(names_[i]) + "=" + enabled_[i].name();
            logger(false, "%s", s.c_str());
        }
    }

    vector<string> const& names() const { return names_; }

  private:
    bool unset_ = true;
    vector<Switch> enabled_;
    vector<string> names_;
};

}  // namespace leap
}  // namespace swirly
