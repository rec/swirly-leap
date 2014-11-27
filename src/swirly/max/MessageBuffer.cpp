#include <swirly/max/MessageBuffer.h>
#include <swirly/max/DictBuffer.h>
#include <swirly/max/ListBuffer.h>

namespace swirly {
namespace leap {

unique_ptr<MessageBuffer> makeListBuffer()
{
    return make_unique<ListBuffer>();
}

unique_ptr<MessageBuffer> makeDictionaryBuffer() {
    return {};
}

}  // namespace leap
}  // namespace swirly
