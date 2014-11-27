#pragma once

#include <swirly/max/MessageBuffer.h>
#include <swirly/max/Message.h>

namespace swirly {
namespace leap {

class ListBuffer : public MessageBuffer {
  public:
    void clear() override
    {
        messages_.clear();
    }

    void add(Representation const& rep) override
    {
        messages_.push_back(makeMessage(rep));
    }

    void send(void* outlet) override
    {
        for (auto& m: messages_)
            m.send (outlet);
    }

  private:
    Messages messages_;
};

}  // namespace leap
}  // namespace swirly
