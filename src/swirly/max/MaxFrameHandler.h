#pragma once

#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>
#include <swirly/max/Gensym.h>
#include <swirly/max/Message.h>

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
        messages_.push_back(makeMessage(rep));
    }

    void frameStart() override {
        messages_.clear();
        frameCallback({"framestart"});
    }

    void frameEnd() override {
        frameCallback({"framend"});
        {
            lock_guard <mutex> lock (mutex_);
            messages_.swap(nextMessages_);
        }

        afterFrameEnd();
    }

    void outputMessages() {
        Messages messages;
        {
            lock_guard <mutex> lock (mutex_);
            messages.swap(nextMessages_);
        }
        for (auto& m: messages)
            m.send (outlet_);
    }

  private:
    mutex mutex_;
    Messages messages_, nextMessages_;
};

}  // namespace leap
}  // namespace swirly
