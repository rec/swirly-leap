#pragma once

#include <string.h>

#include <swirly/base/Base.h>

namespace swirly {
namespace leap {

class Properties {
  public:
    virtual bool addProperty(string const& name) = 0;
    virtual ~Properties() {}
};

}  // namespace leap
}  // namespace swirly
