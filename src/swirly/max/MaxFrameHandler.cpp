#include <swirly/max/MaxFrameHandler.h>
#include <swirly/leap/Config.h>
#include <swirly/max/Gensym.h>
#include <swirly/max/Message.h>

namespace swirly {
namespace leap {

MaxFrameHandler::MaxFrameHandler(Config& config)
        : FrameHandler(config) {
    auto maker = config.isUsingDict() ? makeDictionaryBuffer : makeListBuffer;
    messages_ = maker();
    nextMessages_ = maker();
    outletMessages_ = maker();
}

MaxFrameHandler::~MaxFrameHandler() {}

void MaxFrameHandler::frameCallback(Representation const& rep) {
    messages_->add(rep);
}

void MaxFrameHandler::frameStart() {
    messages_->clear();
    frameCallback({"framestart"});
}

void MaxFrameHandler::frameEnd() {
    frameCallback({"framend"});
    {
        lock_guard <mutex> lock (mutex_);
        nextMessages_.swap(messages_);
    }

    afterFrameEnd();
}

void MaxFrameHandler::send() {
    {
        lock_guard <mutex> lock (mutex_);
        nextMessages_.swap(outletMessages_);
    }
    outletMessages_->send (outlet_);
}

}  // namespace leap
}  // namespace swirly
