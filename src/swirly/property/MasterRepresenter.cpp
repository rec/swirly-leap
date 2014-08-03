#include <swirly/property/MasterRepresenter.h>
#include <swirly/leap/Config.h>

namespace swirly {
namespace leap {

namespace {

template <typename Part>
void add(Representation const& rep, typename MasterRepresenter::Map& map) {
    map[partName<Part>()].reset(new SwitchedPartRepresenterMap<Part>(rep));
}

}  // namespace

MasterRepresenter::MasterRepresenter() {
    add<Hand>({"left", "right"}, map_);
    add<Finger>({"thumb", "index", "middle", "ring", "pinky"}, map_);
    add<Tool>({"tool"}, map_);
    add<CircleGesture>({"circle"}, map_);
    add<KeyTapGesture>({"keytap"}, map_);
    add<ScreenTapGesture>({"screentap"}, map_);
    add<SwipeGesture>({"swipe"}, map_);
}

void MasterRepresenter::dump(Logger const& logger) const {
    for (auto& i: map_)
        i.second->dump(i.first, logger);
}

void MasterRepresenter::finish() {
    for (auto &i: map_)
        i.second->finish();
}

void MasterRepresenter::set(string const& s, Logger const& logger) {
    auto const value = splitEquals(s, Config::VALUE_SEPARATOR);
    auto const& name = value.first;
    auto const& values = value.second;
    if (name.empty() or values.empty()) {
        logger.err("Don't understand argument " + s);
        return;
    }

    auto i = map_.find(name);
    if (i != map_.end()) {
        for (auto const& v: values) {
            if (!i->second->set(v))
                logger.err("Don't understand switch value " + s);
        }
    } else {
        logger.err("Don't understand argument " + s);
    }
}

void MasterRepresenter::setAll() {
    for (auto& i: map_)
        i.second->setAll();
}

}  // namespace leap
}  // namespace swirly
