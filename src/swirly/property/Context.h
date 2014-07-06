#pragma once

#include <leap/Leap.h>

#include <swirly/base/Base.h>

using namespace Leap;

namespace swirly {
namespace leap {

struct Context {
    explicit Context(Frame const& frame)
            : frame_(frame), box_(frame_.interactionBox()) {
    }

    Leap::Frame frame_;
    Leap::InteractionBox box_;
};

}  // namespace leap
}  // namespace swirly
