#include "Listener.h"

namespace swirly {
namespace leap {

Listener::Listener(t_object* o) : object_(o) {}

void Listener::startListening() {
    controller_.addListener(*this);
}

Listener::~Listener() {
   controller_.removeListener(*this);
}

void Listener::onInit(Controller const& controller) {
    log("onInit");
}

void Listener::onExit(Controller const& controller) {
    log("onExit");
}

void Listener::onConnect(Controller const& controller) {
    log("onConnect");
}

void Listener::onDisconnect(const Controller& Controller) {
    log("onDisconnect");
}

void Listener::onFrame(Controller const& controller) {
    log("onFrame");
}

void Listener::onFocusGained(Controller const& controller) {
    log("onFocusGained");
}

void Listener::onFocusLost(Controller const& controller) {
    log("onFocusLost");
}

void Listener::onDeviceChange(Controller const& controller) {
    log("onDeviceChange");
}

void Listener::onServiceConnect(Controller const& controller) {
    log("onServiceConnect");
}

void Listener::onServiceDisconnect(Controller const& controller) {
    log("onServiceDisconnect");
}

void Listener::log(const char* message) {
    object_post(object_, message);
}

}  // namespace leap
}  // namespace swirly
