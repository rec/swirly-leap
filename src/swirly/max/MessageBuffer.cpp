#include <swirly/max/MessageBuffer.h>
#include <swirly/max/Message.h>

namespace swirly {
namespace leap {

namespace {

struct ListBuffer : public MessageBuffer {
    void clear() override
    {
        messages.clear();
    }

    void add(Representation const& rep) override
    {
        messages.push_back(makeMessage(rep));
    }

    void send(void* outlet) override
    {
        for (auto& m: messages)
            m.send (outlet);
    }

    Messages messages;
};

} // namespace

unique_ptr<MessageBuffer> makeListBuffer()
{
    return make_unique<ListBuffer>();
}

}  // namespace leap
}  // namespace swirly
