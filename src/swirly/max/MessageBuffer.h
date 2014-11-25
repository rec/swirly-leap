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

class MessageBuffer {
  public:
    virtual ~MessageBuffer() = default;
    virtual void clear() = 0;
    virtual void add(Representation const&) = 0;
    virtual void send(void* outlet) = 0;
};

unique_ptr<MessageBuffer> makeListBuffer();
unique_ptr<MessageBuffer> makeDictionaryBuffer();

}  // namespace leap
}  // namespace swirly
