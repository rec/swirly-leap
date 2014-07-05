#include <swirly/base/Base.h>

namespace swirly {
namespace leap {

struct Logger {
    virtual ~Logger() {}
    virtual void log(string const&) const = 0;
    virtual void err(string const&) const = 0;

    // error is a MACRO in the Max headers - for shame!
};

}  // namespace leap
}  // namespace swirly
