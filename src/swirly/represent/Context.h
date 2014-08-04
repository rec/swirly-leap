#pragma once

#include <leap/Leap.h>

#include <swirly/base/Base.h>

using namespace Leap;

namespace swirly {
namespace leap {

class Config;

struct Context {
    explicit Context(Frame const& f, Config const& c)
            : frame_(f), box_(frame_.interactionBox()), config_(c) {
    }

    Leap::Frame frame_;
    Leap::InteractionBox box_;
    Config const& config_;
};

}  // namespace leap
}  // namespace swirly
