#pragma once

#include <swirly/leap/Config.h>
#include <swirly/leap/FrameHandler.h>
#include <swirly/leap/Listener.h>

namespace swirly {
namespace leap {

struct LeapMotion {
    LeapMotion(Logger const& logger)
            : config_(logger),
              frameHandler_(config_),
              listener_(config_, frameHandler_) {
    }
    Config config_;
    MaxFrameHandler frameHandler_;
    Listener listener_;
};

}  // namespace leap
}  // namespace swirly
