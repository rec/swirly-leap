#include <swirly/represent/MasterRepresenter.h>
#include <swirly/leap/Config.h>

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

template <typename Part>
void add(Representation const& rep, typename MasterRepresenter::Map& map) {
    map[partName<Part>()].reset(new SwitchedPartRepresenterMap<Part>(rep));
}

template <typename Part>
void add(typename MasterRepresenter::Map& map) {
    add<Part>(Representation{partName<Part>()}, map);
}

}  // namespace

MasterRepresenter::MasterRepresenter(
    Logger const& logger, Controller& controller)
        : logger_(logger), controller_(controller) {
    add<Hand>({"left", "right"}, map_);
    add<Finger>({"thumb", "index", "middle", "ring", "pinky"}, map_);

    add<Tool>(map_);
    add<CircleGesture>(map_);
    add<KeyTapGesture>(map_);
    add<ScreenTapGesture>(map_);
    add<SwipeGesture>(map_);
}

void MasterRepresenter::dump() const {
    for (auto& i: map_)
        i.second->dump(i.first, logger_);
}

void MasterRepresenter::finish() {
    if (!getPartMap<CircleGesture>()->partMap().representers().empty())
        controller_.enableGesture(Gesture::TYPE_CIRCLE);

    if (!getPartMap<SwipeGesture>()->partMap().representers().empty())
        controller_.enableGesture(Gesture::TYPE_SWIPE);

    if (!getPartMap<ScreenTapGesture>()->partMap().representers().empty())
        controller_.enableGesture(Gesture::TYPE_SCREEN_TAP);

    if (!getPartMap<KeyTapGesture>()->partMap().representers().empty())
        controller_.enableGesture(Gesture::TYPE_KEY_TAP);

    for (auto &i: map_)
        i.second->finish();
}

void MasterRepresenter::set(string const& s) {
    auto const value = splitEquals(s, Config::VALUE_SEPARATOR);
    auto const& name = value.first;
    auto const& values = value.second;
    if (name.empty() or values.empty()) {
        logger_.err("Don't understand argument " + s);
        return;
    }

    auto i = map_.find(name);
    if (i != map_.end()) {
        for (auto const& v: values) {
            if (!i->second->set(v))
                logger_.err("Don't understand switch value " + s);
        }
    } else {
        logger_.err("Don't understand argument " + s);
    }
}

void MasterRepresenter::setAll() {
    for (auto& i: map_)
        i.second->setAll();
}

}  // namespace leap
}  // namespace swirly
