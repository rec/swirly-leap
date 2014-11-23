#include <swirly/base/Callback.h>
#include <swirly/represent/Represent.h>

namespace Leap {
class Frame;
}

namespace swirly {
namespace leap {

class Config;

class FrameHandler : public Callback<Representation const&> {
  public:
    FrameHandler(Config& config) : config_(config) { }
    void setOutlet(void* outlet) { outlet_ = outlet; }
    void onFrame(Leap::Frame const&);
    virtual void frameStart() = 0;
    virtual void frameEnd() = 0;
    virtual void callback(Representation const&) = 0;

  protected:
    Config& config_;
    void* outlet_ = nullptr;
};

}  // namespace leap
}  // namespace swirly
