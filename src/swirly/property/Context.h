#pragma once

#include <leap/Leap.h>

#include <swirly/base/Base.h>

using namespace Leap;

namespace swirly {
namespace leap {

struct Context {
    Leap::InteractionBox box_;
};

}  // namespace leap
}  // namespace swirly
