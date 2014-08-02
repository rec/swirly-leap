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

    virtual void handleRepresentation(Representation const&) = 0;

  private:
    Config& config_;
    void* outlet_ = nullptr;
};

class MaxFrameHandler : public FrameHandler {
  public:
    using FrameHandler::FrameHandler;
    void handleRepresentation(Representation const&) override {}
};


}  // namespace leap
}  // namespace swirly
