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
    config_.logger_(false, "FrameHandler");
    if (auto hProp = config_.switches().get<Hand>()) {
        auto& h = *hProp;
        auto const& hands = frame.hands();
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handType != NO_HAND and h[handType]) {
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
