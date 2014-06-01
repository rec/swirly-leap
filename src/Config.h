#include <array>

#include "Base.h"

namespace swirly {
namespace leap {

struct Config {
    typedef vector<string> Address;
    typedef vector<Address> Addresses;

    Addresses addresses_;

    bool verbose_ = false;
    bool json_ = false;
    bool all_ = false;

    array<bool, 2> hands_;

    static auto const ADDRESS_SEPARATOR = '.';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(const string &str, t_object* object);
    void dump(t_object* object);
};

}  // namespace leap
}  // namespace swirly
