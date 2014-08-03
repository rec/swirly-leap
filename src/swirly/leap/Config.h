#include <swirly/property/SwitchArray.h>

namespace swirly {
namespace leap {

class SwitchedPartRepresenterMapMap;

class Config {
  public:
    Config(Logger const&);
    ~Config();

    static auto const VALUE_SEPARATOR = '+';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(string const&);
    void finishArguments();
    void dump();

    Representation getHand() const;
    Representation setHand(Representation const&);

    Logger const& logger_;

    SwitchedPartRepresenterMapMap const& switches() const { return *switches_; }

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
    bool verbose_ = false;
    bool json_ = false;
    bool all_ = false;
    bool running_ = false;

    void updateCallbacks() {
        for (auto& cb: callbacks_)
            cb();
    }

    unique_ptr<SwitchedPartRepresenterMapMap> switches_;
    vector<Callback> callbacks_;
};

}  // namespace leap
}  // namespace swirly
