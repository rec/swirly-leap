#include "Listener.h"
#include "Callback.h"
#include "Config.h"

namespace swirly {
namespace leap {

Listener::Listener(t_object* o, Config& config, FrameCallback& callback)
        : object_(o), config_(config), callback_(callback) {
}

void Listener::initialize() {
    if (not initialized_) {
        initialized_ = true;
        controller_.addListener(*this);
    }
}

Listener::~Listener() {
    if (initialized_)
        controller_.removeListener(*this);
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
    callback_.callback(controller.frame());
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

void Listener::log(const char* message) {
    object_post(object_, message);
}

void Listener::verbose(const char* message) {
    if (config_.verbose_)
        log(message);
}

}  // namespace leap
}  // namespace swirly
