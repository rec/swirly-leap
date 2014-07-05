#include <array>

#include "leap/Leap.h"

#include "FrameHandler.h"

#include "Config.h"
#include "LeapUtil.h"
#include "PropertiesToMax.h"
#include "PropertySwitchArray.h"

using namespace Leap;

namespace swirly {
namespace leap {

void FrameHandler::onFrame(Frame const& frame) {
    if (!outlet_) {
        config_.logger_.err("No outlet!");
        return;
    }
    if (auto handProperties = config_.switches().get<Hand>()) {
        Representation rep{"hand", ""};
        auto const& hands = frame.hands();
        auto& switches = handProperties->switches_;
        auto& properties = handProperties->properties_;
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handType != NO_HAND and switches[handType].second) {
                rep[1] = HAND_NAME[handType];
                propertiesToMax(outlet_, hand, properties, rep);
            }
        }
    }

    if (auto fingerProperties = config_.switches().get<Finger>()) {
        Representation rep{"finger", "", ""};
        auto const& fingers = frame.fingers();
        auto& switches = fingerProperties->switches_;
        auto properties = fingerProperties->properties_;
        for (auto const& finger: fingers) {
            auto fingerType = finger.type();
            auto sw = switches[fingerType];
            if (sw.second) {
                auto handType = whichHand(finger.hand());
                if (handType != NO_HAND) {
                    rep[1] = HAND_NAME[handType];
                    rep[2] = sw.first;
                    propertiesToMax(outlet_, finger, properties, rep);
                }
            }
        }
    }

    if (auto toolProperties = config_.switches().get<Tool>()) {
        Representation rep{"tool", "", ""};
        auto const& tools = frame.tools();
        auto properties = toolProperties->properties_;
        auto toolCount = 0;
        for (auto const& tool: tools) {
            auto handType = whichHand(tool.hand());
            if (handType != NO_HAND) {
                rep[1] = HAND_NAME[handType];
                rep[2] = to_string(toolCount);
                propertiesToMax(outlet_, tool, properties, rep);
            }
            toolCount++;
        }
    }
}

}  // namespace leap
}  // namespace swirly
