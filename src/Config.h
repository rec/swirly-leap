#include <functional>
#include <map>

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

    static auto const VALUE_SEPARATOR = '+';
    static auto const FLAG_PREFIX = '-';
    static auto const OPTION_PREFIX = '@';

    void addArgument(string const&);
    void finishArguments();
    void dump();

    Logger const logger_;

  private:
    map<string, SwitchArray> switches_;
};

}  // namespace leap
}  // namespace swirly
