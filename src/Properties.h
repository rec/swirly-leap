#pragma once

#include <string.h>

#include "Base.h"

namespace swirly {
namespace leap {

class Properties {
  public:
    virtual bool addProperty(string const& name) = 0;
    virtual ~Properties() {}
};

}  // namespace leap
}  // namespace swirly
