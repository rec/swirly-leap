#include <swirly/leap/LeapUtil.h>
#include <swirly/leap/Getter.h>

namespace swirly {
namespace leap {

HandType whichHand(Hand const& hand) {
    if (hand.isLeft())
        return LEFT_HAND;
    if (hand.isRight())
        return RIGHT_HAND;
    return NO_HAND;
}

const char* HAND_NAME[] = {"left", "right", ""};

}  // namespace leap
}  // namespace swirly
