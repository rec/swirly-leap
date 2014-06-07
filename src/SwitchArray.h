#pragma once

#include "Switch.h"
#include "Properties.h"

namespace swirly {
namespace leap {

class SwitchArray {
  public:
    SwitchArray() {}
    SwitchArray(const char** names, int size);

    void finish();
    bool set(string const& name);
    void dump(Logger);

    Switch const& operator[](int i) const { return switches_[i].second; }
    Switch& operator[](int i) { return switches_[i].second; }

  private:
    vector<pair<string, Switch>> switches_;
    unique_ptr<Properties> properties_;
};

}  // namespace leap
}  // namespace swirly
