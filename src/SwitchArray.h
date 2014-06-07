#pragma include once

#include "Switch.h"

namespace swirly {
namespace leap {

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
