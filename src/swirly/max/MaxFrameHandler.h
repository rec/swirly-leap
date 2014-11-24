#pragma once

#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>
#include <swirly/max/Gensym.h>
#include <swirly/max/Message.h>

extern "C" {
#include "ext_critical.h"
}

namespace swirly {
namespace leap {

class MaxFrameHandler : public FrameHandler {
  public:
    using FrameHandler::FrameHandler;

    void frameCallback(Representation const& rep) override {
        messages_.push_back(makeMessage(rep));
    }

    void frameStart() override {
        frameCallback({"framestart"});
    }

    void frameEnd() override {
        frameCallback({"framend"});
        for (auto& m: messages_) {
            critical_enter (0);
            m.send (outlet_);
            critical_exit (0);
        }
        messages_.clear();
    }

    Messages messages_;
};

}  // namespace leap
}  // namespace swirly
