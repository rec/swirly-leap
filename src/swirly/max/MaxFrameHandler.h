#pragma once

#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>
#include <swirly/max/Gensym.h>
#include <swirly/max/Message.h>
#include <swirly/max/MessageBuffer.h>

extern "C" {
#include "ext_critical.h"
}

#include <mutex>

namespace swirly {
namespace leap {

class MaxFrameHandler : public FrameHandler {
  public:
    using FrameHandler::FrameHandler;

    function <void()> afterFrameEnd;

    void frameCallback(Representation const& rep) override {
        messages_->add(rep);
    }

    void frameStart() override {
        messages_->clear();
        frameCallback({"framestart"});
    }

    void frameEnd() override {
        frameCallback({"framend"});
        {
            lock_guard <mutex> lock (mutex_);
            nextMessages_.swap(messages_);
        }

        afterFrameEnd();
    }

    void outputMessages() {
        {
            lock_guard <mutex> lock (mutex_);
            nextMessages_.swap(outletMessages_);
        }
        outletMessages_->send (outlet_);
    }

  private:
    mutex mutex_;

    unique_ptr<MessageBuffer> messages_ = makeListBuffer();
    unique_ptr<MessageBuffer> nextMessages_ = makeListBuffer();
    unique_ptr<MessageBuffer> outletMessages_ = makeListBuffer();
};

}  // namespace leap
}  // namespace swirly
