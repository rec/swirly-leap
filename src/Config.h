#include "SwitchArray.h"

namespace swirly {
namespace leap {

struct PropertySwitchArrayMap;

class Config {
  public:
    Config(Logger);
    ~Config();

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

    PropertySwitchArrayMap const& switches() const { return *switches_; }

  private:
    unique_ptr<PropertySwitchArrayMap> switches_;
};

}  // namespace leap
}  // namespace swirly
