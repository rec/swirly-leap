#include <swirly/leap/Listener.h>

#include <swirly/base/Logger.h>
#include <swirly/leap/Config.h>
#include <swirly/leap/FrameHandler.h>

namespace swirly {
namespace leap {

Listener::Listener(
    Config& config,
    FrameHandler& frameHandler,
    Controller& controller)
        : config_(config),
          frameHandler_(frameHandler),
          controller_(controller) {
    config_.addCallback(bind(&Listener::configCallback, this));
}

void Listener::configCallback() {
    setRunning(config_.isRunning());
}

bool Listener::sendFrame() {
    if (!running_)
        onFrame(controller_);

    return !running_;
}

void Listener::setRunning(bool running) {
    if (running != running_) {
        running_ = running;
        if (running_)
            controller_.addListener(*this);
        else
            controller_.removeListener(*this);
    }
}

Listener::~Listener() {
    setRunning(false);
}

void Listener::onInit(Controller const&) {
    verbose("onInit");
}

void Listener::onExit(Controller const&) {
    verbose("onExit");
}

void Listener::onConnect(Controller const&) {
    log("onConnect");
}

void Listener::onDisconnect(Controller const&) {
    log("onDisconnect");
}

void Listener::onFrame(Controller const& controller) {
    verbose("onFrame");
    frameHandler_.onFrame(controller.frame());
}

void Listener::onFocusGained(Controller const&) {
    verbose("onFocusGained");
}

void Listener::onFocusLost(Controller const&) {
    verbose("onFocusLost");
}

void Listener::onDeviceChange(Controller const&) {
    verbose("onDeviceChange");
}

void Listener::onServiceConnect(Controller const&) {
    verbose("onServiceConnect");
}

void Listener::onServiceDisconnect(Controller const&) {
    log("onServiceDisconnect");
}

void Listener::log(string const& message) {
    config_.logger_.log(message);
}

void Listener::verbose(string const& message) {
    if (config_.isVerbose())
        log(message);
}

}  // namespace leap
}  // namespace swirly
