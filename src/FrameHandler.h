#include "Base.h"
#include "Callback.h"

namespace Leap {
class Frame;
}

namespace swirly {
namespace leap {

class Config;

class FrameHandler {
  public:
    FrameHandler(Config& config) : config_(config), outlet_(nullptr) {}
    void setOutlet(void* outlet) { outlet_ = outlet; }
    void onFrame(Leap::Frame const&);

  private:
    Config& config_;
    void* outlet_;
};

}  // namespace leap
}  // namespace swirly
