#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>

namespace swirly {
namespace leap {

class MaxFrameHandler : public FrameHandler {
  public:
    using FrameHandler::FrameHandler;
    void callback(Representation const&) override {}

  private:
    static const int MAXIMUM_OUTPUT_SYMBOLS = 16;
    t_atom atoms[MAXIMUM_OUTPUT_SYMBOLS];
};

}  // namespace leap
}  // namespace swirly
