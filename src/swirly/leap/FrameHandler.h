#include <swirly/base/Base.h>
#include <swirly/base/Callback.h>

namespace Leap {
class Frame;
}

namespace swirly {
namespace leap {

class Config;

class FrameHandler {
  public:
    FrameHandler(Config& config) : config_(config) {}
    void setOutlet(void* outlet) { outlet_ = outlet; }
    void onFrame(Leap::Frame const&);

  private:
    Config& config_;
    void* outlet_ = nullptr;
};

}  // namespace leap
}  // namespace swirly
