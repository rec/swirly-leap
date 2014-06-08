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

}  // namespace

void FrameHandler::onFrame(Frame const& frame) {
    if (!outlet_) {
        config_.logger_("No outlet!", true);
        return;
    }
    config_.logger_("FrameHandler", false);
    if (auto hProp = config_.switches().get<Hand>()) {
        Representation rep{"hand", ""};
        auto const& hands = frame.hands();
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handType != NO_HAND and (*hProp)[handType]) {
                rep[1] = handType == LEFT_HAND ? "left" : "right";
                propertiesToMax(outlet_, hand, hProp->properties_, rep);
            }
        }
    }
#if 0

    auto const& fingers = frame.fingers();
    for (auto const& finger: fingers) {
    }

    auto const& tools = frame.tools();
    for (auto const& tool: tools) {
    }

    auto const& gestures = frame.gestures();
    for (auto const& gesture: gestures) {
    }
#endif
#if 0
fingers=all, none, * or left or right or 1+2+4 or thumb+index+middle+ring+little or numeric
hands=all, none or left or right
tools=all/none
swipe , circle , screentap , keytap

#endif
}

}  // namespace leap
}  // namespace swirly
