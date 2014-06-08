#pragma once

#include "Switch.h"

namespace swirly {
namespace leap {

class SwitchArray {
  public:
    SwitchArray() {}
    SwitchArray(Representation const&);
    virtual ~SwitchArray() {}

    void finish();
    virtual bool set(string const& name);
    void dump(Logger);

    Switch const& operator[](int i) const { return switches_[i].second; }
    Switch& operator[](int i) { return switches_[i].second; }

  private:
    vector<pair<string, Switch>> switches_;
};

}  // namespace leap
}  // namespace swirly
