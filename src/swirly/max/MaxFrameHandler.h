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

    void callback(Representation const& rep) override {
        makeMessage(rep).send(outlet_);
    }

    void frameStart() override {
        callback({"framestart"});
    }

    void frameEnd() override {
        callback({"framend"});
    }
};

}  // namespace leap
}  // namespace swirly
