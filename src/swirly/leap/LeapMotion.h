#pragma once

#include <swirly/leap/Config.h>
#include <swirly/max/MaxFrameHandler.h>
#include <swirly/max/MaxObject.h>
#include <swirly/leap/Listener.h>

namespace swirly {
namespace leap {

struct LeapMotion {
    LeapMotion(MaxObject& maxObject)
            : config_(maxObject, controller_),
              frameHandler_(config_),
              listener_(config_, frameHandler_, controller_) {
        frameHandler_.afterFrameEnd = [&] () { maxObject.startClock(); };
        maxObject.clockCallback = [this] () { frameHandler_.send(); };
    }

    Leap::Controller controller_;
    Config config_;
    MaxFrameHandler frameHandler_;
    Listener listener_;
};

}  // namespace leap
}  // namespace swirly
