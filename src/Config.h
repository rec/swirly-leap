#include "Switch.h"

namespace swirly {
namespace leap {

struct Config {
    bool verbose_ = false;
    bool json_ = false;
    bool all_ = false;

    SwitchArray<2> hands_;

    static auto const VALUE_SEPARATOR = '+';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(const string &str, t_object* object);
    void finishArguments();
    void dump(t_object* object);

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
