#pragma include once

#include "Base.h"

namespace Leap {
class Frame;
}

namespace swirly {
namespace leap {

class FrameCallback {
  public:
    virtual void callback(Leap::Frame const&) = 0;
    virtual ~FrameCallback() {}
};

}  // namespace leap
}  // namespace swirly
