#pragma once

#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>
#include <swirly/max/MessageBuffer.h>

#include <mutex>

namespace swirly {
namespace leap {

class MaxFrameHandler : public FrameHandler {
  public:
    explicit MaxFrameHandler(Config&);
    ~MaxFrameHandler();

    function <void()> afterFrameEnd;

    void frameCallback(Representation const& rep) override;
    void frameStart() override;
    void frameEnd() override;
    void send();

  private:
    mutex mutex_;

    unique_ptr<MessageBuffer> messages_, nextMessages_, outletMessages_;
};

}  // namespace leap
}  // namespace swirly
