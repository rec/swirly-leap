#pragma once

#include "Switch.h"

namespace swirly {
namespace leap {

struct Logger;

class SwitchArray {
  public:
    SwitchArray() {}
    SwitchArray(Representation const&);
    virtual ~SwitchArray() {}

    void finish();
    virtual bool set(string const& name);
    virtual void dump(string const& name, Logger const&) const;

    string const& name(unsigned int i) const { return switches_[i].first; }

    bool any(bool isSet = true) const;

    Switch const& operator[](int i) const { return switches_[i].second; }
    Switch& operator[](int i) { return switches_[i].second; }

  private:
    vector<pair<string, Switch>> switches_;
};

}  // namespace leap
}  // namespace swirly
