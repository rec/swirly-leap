#include <functional>

#include "Switch.h"

namespace swirly {
namespace leap {

class Config {
  public:
    typedef std::function<void(bool, const char*, const char*)> Logger;

    Config(Logger);

    bool verbose_ = false;
    bool json_ = false;
    bool all_ = false;
    bool running_ = false;

    SwitchArray hands_;
    SwitchArray fingers_;
    SwitchArray tools_;
    SwitchArray gestures_;

    static auto const VALUE_SEPARATOR = '+';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(string const&);
    void finishArguments();
    void dump();

    Logger const logger_;

  private:
    void circle(string const&);
    void finger(string const&);
    void hand(string const&);
    void keytap(string const&);
    void screentap(string const&);
    void swipe(string const&);
    void tool(string const&);
};

}  // namespace leap
}  // namespace swirly
