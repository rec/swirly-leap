#pragma once

#include <swirly/property/Switch.h>

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

    bool any(bool isSet = true) const;

    bool isSet(unsigned int index) const;
    string const& name(unsigned int i) { return switches_[i].first; }

    /** Return the name, if that switch item is enabled, else the empty string.
     */
    string enabledName(unsigned int index) const;

    /** Represent this SwitchArray as a list of its enabled switch names. */
    virtual void represent(Representation&) const;

  private:
    vector<pair<string, Switch>> switches_;
};

}  // namespace leap
}  // namespace swirly
