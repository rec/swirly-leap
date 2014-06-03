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

    SwitchArray<2> hands_;
    SwitchArray<5> fingers_[2];

    static auto const VALUE_SEPARATOR = '+';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    // void addArgument(const string &str, t_object* object);
    void addArgument(string const&);
    void finishArguments();
    void dump();

  private:
    void circle(string const&);
    void finger(string const&);
    void hand(string const&);
    void keytap(string const&);
    void screentap(string const&);
    void swipe(string const&);
    void tool(string const&);

    Logger const logger_;
};

}  // namespace leap
}  // namespace swirly
