#include "leap/Leap.h"

#include "Base.h"
#include "Callback.h"

namespace swirly {
namespace leap {

class Config;

class FrameHandler {
  public:
    FrameHandler(Config& config) : config_(config) {}
    void onFrame(Frame const&);

  private:
    Config& config_;
};

}  // namespace leap
}  // namespace swirly
