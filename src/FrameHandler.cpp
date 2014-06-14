#include <array>

#include "leap/Leap.h"

#include "FrameHandler.h"
#include "Config.h"
#include "PropertiesToMax.h"
#include "PropertySwitchArray.h"

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

HandType whichHand(Hand const& hand) {
    if (hand.isLeft())
        return LEFT_HAND;
    if (hand.isRight())
        return RIGHT_HAND;
    return NO_HAND;
}

const char* HAND_NAME[] = {"", "left", "right"};

}  // namespace

void FrameHandler::onFrame(Frame const& frame) {
    if (!outlet_) {
        config_.logger_.err("No outlet!");
        return;
    }
    if (auto handProperties = config_.switches().get<Hand>()) {
        Representation rep{"hand", ""};
        auto const& hands = frame.hands();
        auto properties = handProperties->properties_;
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handType != NO_HAND and (*handProperties)[handType]) {
                rep[1] = HAND_NAME[handType];
                propertiesToMax(outlet_, hand, properties, rep);
            }
        }
    }

    if (auto fingerProperties = config_.switches().get<Finger>()) {
        Representation rep{"finger", "", ""};
        auto const& fingers = frame.fingers();
        auto properties = fingerProperties->properties_;
        for (auto const& finger: fingers) {
            auto fingerType = finger.type();
            if ((*fingerProperties)[fingerType]) {
                auto handType = whichHand(finger.hand());
                if (handType != NO_HAND) {
                    rep[1] = HAND_NAME[handType];
                    rep[2] = fingerProperties->name(fingerType);
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
            post(("tool!! " + to_string(toolCount)).c_str());
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
