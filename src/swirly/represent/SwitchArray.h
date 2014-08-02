#pragma once

#include <swirly/represent/Switch.h>

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
    virtual bool empty() const { return any(); }

    /** Return true if any of the switches has this value. */
    bool any(bool isSet = true) const;

    bool isOn(unsigned int i) const { return switches_[i].second; }
    string const& name(unsigned int i) const { return switches_[i].first; }

    /** Describe this SwitchArray as a list of its enabled switch names. */
    virtual void describe(Representation&) const;

    /** Turn all the switches on. */
    virtual void setAll();

  private:
    vector<pair<string, Switch>> switches_;
};

}  // namespace leap
}  // namespace swirly
