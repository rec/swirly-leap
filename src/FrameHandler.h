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
    FrameHandler(Config& config) : config_(config) {}
    void onFrame(Leap::Frame const&);

  private:
    Config& config_;
};

}  // namespace leap
}  // namespace swirly
