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

    bool any(bool isSet = true) const;

    vector<pair<string, Switch>> switches_;
};

}  // namespace leap
}  // namespace swirly
