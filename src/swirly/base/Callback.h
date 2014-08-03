#pragma once

#include <swirly/base/Base.h>

namespace swirly {
namespace leap {

template <typename Type>
struct Callback {
    virtual void callback(Type) = 0;
    virtual ~Callback() {}
};

}  // namespace leap
}  // namespace swirly
