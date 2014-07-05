#pragma once

#include <swirly/base/Base.h>

namespace swirly {
namespace leap {

template <typename Output>
struct Callback {
    virtual void callback(Output) = 0;
    virtual ~Callback() {}
};

}  // namespace leap
}  // namespace swirly
