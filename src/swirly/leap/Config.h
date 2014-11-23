#include <swirly/represent/SwitchArray.h>

namespace Leap {
class Controller;
}

namespace swirly {
namespace leap {

class MasterRepresenter;

class Config {
  public:
    Config(Logger const&, Leap::Controller&);
    ~Config();

    static auto const VALUE_SEPARATOR = '+';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(string const&);
    void finish();
    void dump();

    Representation getHand() const;
    Representation setHand(Representation const&);

    Logger const& logger_;

    MasterRepresenter const& representers() const { return *masterRepresenter_; }

    typedef function<void()> Callback;

    void addCallback(Callback cb) {
        callbacks_.push_back(cb);
    }

    void setRunning(bool running) {
        if (running != running_) {
            running_ = running;
            updateCallbacks();
        }
    }

    bool isRunning() const { return running_; }
    bool isVerbose() const { return verbose_; }

  private:
    bool all_ = false;
    bool verbose_ = false;
    bool running_ = false;

    void updateCallbacks() {
        for (auto& cb: callbacks_)
            cb();
    }

    unique_ptr<MasterRepresenter> masterRepresenter_;
    vector<Callback> callbacks_;
};

}  // namespace leap
}  // namespace swirly
