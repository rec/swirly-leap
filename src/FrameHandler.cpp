#include <array>

#include "FrameHandler.h"
#include "Config.h"

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

enum HandType { LEFT, RIGHT, NO_HAND };

HandType whichHand(Hand const& hand) {
    if (hand.isLeft())
        return LEFT;
    if (hand.isRight())
        return RIGHT;
    return NO_HAND;
}

}  // namespace

void FrameHandler::onFrame(Frame const& frame) {
    auto const& hands = frame.hands();
    for (auto const& hand: hands) {
        auto handType = whichHand(hand);
        if (handType != NO_HAND and config_.hands_[handType]) {
            // Process hand.
        }
    }

    auto const& fingers = frame.fingers();
    for (auto const& finger: fingers) {
    }

    auto const& tools = frame.tools();
    for (auto const& tool: tools) {
    }

    auto const& gestures = frame.gestures();
    for (auto const& gesture: gestures) {
    }
#if 0
fingers=all, none, * or left or right or 1+2+4 or thumb+index+middle+ring+little or numeric
hands=all, none or left or right
tools=all/none
swipe , circle , screentap , keytap

#endif
}

}  // namespace leap
}  // namespace swirly
