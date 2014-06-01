#include <array>

#include "Base.h"

namespace swirly {
namespace leap {

struct Config {
    bool verbose_ = false;
    bool json_ = false;
    bool all_ = false;

    array<bool, 2> hands_;

    static auto const ADDRESS_SEPARATOR = '.';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(const string &str, t_object* object);
    void dump(t_object* object);

  private:
    void finger(string const&);
    void hand(string const&);
    void tool(string const&);
    void swipe(string const&);
    void circle(string const&);
    void screentap(string const&);
    void keytap(string const&);
};

}  // namespace leap
}  // namespace swirly
