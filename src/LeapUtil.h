#pragma once

#include "leap/Leap.h"

#include "Base.h"

using namespace Leap;

namespace swirly {
namespace leap {

HandType whichHand(Hand const&);

extern const char* HAND_NAME[];

}  // namespace leap
}  // namespace swirly
