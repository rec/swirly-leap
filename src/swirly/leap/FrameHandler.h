#include <swirly/base/Callback.h>
#include <swirly/property/Represent.h>

namespace Leap {
class Frame;
}

namespace swirly {
namespace leap {

class Config;

class FrameHandler {
  public:
    typedef Callback<Representation const&> OutputCallback;

    FrameHandler(Config& config, OutputCallback& callback)
            : config_(config), callback_(callback) {
    }
    void setOutlet(void* outlet) { outlet_ = outlet; }
    void onFrame(Leap::Frame const&);

  private:
    Config& config_;
    OutputCallback& callback_;
    void* outlet_ = nullptr;
};

class MaxFrameHandler : public FrameHandler,
                        public FrameHandler::OutputCallback {
  public:
    MaxFrameHandler(Config& config) : FrameHandler(config, *this) {}
    void callback(Representation const&) override {}
};


}  // namespace leap
}  // namespace swirly
