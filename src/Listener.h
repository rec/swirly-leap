#include "leap/Leap.h"

#include "Base.h"
#include "Callback.h"

namespace swirly {
namespace leap {

class Config;
class FrameHandler;

class Listener : public Leap::Listener {
  public:
    Listener(Config&, FrameHandler&);
    ~Listener();

    void initialize();

    typedef Leap::Controller Controller;

    void onInit(Controller const&) override;
    void onConnect(Controller const&) override;
    void onDisconnect(Controller const&) override;
    void onExit(Controller const&) override;
    void onFrame(Controller const&) override;
    void onFocusGained(Controller const&) override;
    void onFocusLost(Controller const&) override;
    void onDeviceChange(Controller const&) override;
    void onServiceConnect(Controller const&) override;
    void onServiceDisconnect(Controller const&) override;

  private:
    Controller controller_;
    Config& config_;
    FrameHandler& frameHandler_;
    bool initialized_ = false;

    void log(const char*);
    void verbose(const char*);
};

}  // namespace leap
}  // namespace swirly
