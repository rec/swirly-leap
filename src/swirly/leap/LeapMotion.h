#pragma once

#include <swirly/leap/Config.h>
#include <swirly/max/MaxFrameHandler.h>
#include <swirly/leap/Listener.h>

namespace swirly {
namespace leap {

struct LeapMotion {
    LeapMotion(Logger const& logger)
            : config_(logger, controller_),
              frameHandler_(config_),
              listener_(config_, frameHandler_, controller_) {
    }

    Leap::Controller controller_;
    Config config_;
    MaxFrameHandler frameHandler_;
    Listener listener_;
};

}  // namespace leap
}  // namespace swirly
