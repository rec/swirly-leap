#pragma once

#include "Config.h"
#include "FrameHandler.h"
#include "Listener.h"

namespace swirly {
namespace leap {

struct LeapMotion {
    LeapMotion(Logger const& logger)
            : config_(logger),
              frameHandler_(config_),
              listener_(config_, frameHandler_) {
    }
    Config config_;
    FrameHandler frameHandler_;
    Listener listener_;
};

}  // namespace leap
}  // namespace swirly
