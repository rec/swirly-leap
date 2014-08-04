#pragma once

#include <string.h>

#include <swirly/base/Base.h>

namespace swirly {
namespace leap {

class RepresenterMap {
  public:
    virtual bool addRepresenter(string const& name) = 0;
    virtual ~RepresenterMap() {}
};

}  // namespace leap
}  // namespace swirly
