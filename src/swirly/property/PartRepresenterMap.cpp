#include <leap/Leap.h>

#include <swirly/property/PartRepresenterMap.h>
#include <swirly/property/GetterRepresenter.h>
#include <swirly/property/BoxRepresenter.h>

using namespace Leap;

namespace swirly {
namespace leap {

template <typename Part>
bool PartRepresenterMap<Part>::addRepresenter(string const& name) {
    if (name == "*") {
        representers_ = getDefault().representers_;
    } else if (name == "-") {
        representers_.clear();
    } else {
        auto i = getDefault().representers_.find(name);
        if (i == getDefault().representers_.end())
            return false;
        representers_[name] = i->second;
    }

    return true;
}

template <typename Part>
void PartRepresenterMap<Part>::dump(
        string const& name, Logger const& logger) const {
    if (not empty()) {
        string result;
        for (auto& p: representers_) {
            if (not result.empty())
                result += "+";
            result += p.first;
        }
        logger.log(name + "=" + result);
    }
}

template <typename Part>
void PartRepresenterMap<Part>::represent(Representation& rep) const {
    for (auto& p: representers_)
        rep.push_back(p.first);
}


template <typename Part>
void fillDefault(PartRepresenterMap<Part>&);

template <typename Part>
PartRepresenterMap<Part> newDefault() {
    PartRepresenterMap<Part> representer;
    fillDefault(representer);
    return representer;
}

template <typename Part>
const PartRepresenterMap<Part>& PartRepresenterMap<Part>::getDefault() {
    static auto const REPRESENTER = newDefault<Part>();
    return REPRESENTER;
}

#define PROP(CLASS, NAME) \
    addGetter(prop, #NAME, &CLASS::NAME)

#define BOX(CLASS, NAME) \
    do {                                                            \
        addBox(prop, #NAME, &CLASS::NAME, Restrict::CLAMP);        \
        addBox(prop, #NAME "Free", &CLASS::NAME, Restrict::FREE);  \
        addGetter(prop, #NAME "Raw", &CLASS::NAME);                \
    } while (false)


template <>
void fillDefault(PartRepresenterMap<Finger>& prop) {
    PROP(Pointable, direction);
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, timeVisible);
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);

    BOX(Pointable, stabilizedTipPosition);
    BOX(Pointable, tipPosition);
    BOX(Pointable, tipVelocity);
}

template <>
void fillDefault(PartRepresenterMap<Tool>& prop) {
    PROP(Pointable, direction);
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, timeVisible);
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);

    BOX(Pointable, stabilizedTipPosition);
    BOX(Pointable, tipPosition);
    BOX(Pointable, tipVelocity);
}

template <>
void fillDefault(PartRepresenterMap<Bone>& prop) {
    PROP(Bone, basis); // A matrix - what to do with that?
    PROP(Bone, direction);
    PROP(Bone, length);
    PROP(Bone, type);
    PROP(Bone, width);

    BOX(Bone, center);
}

template <>
void fillDefault(PartRepresenterMap<Hand>& prop) {
    PROP(Hand, basis);
    PROP(Hand, confidence);
    PROP(Hand, direction);
    PROP(Hand, grabStrength);
    PROP(Hand, palmNormal);
    PROP(Hand, palmWidth);
    PROP(Hand, pinchStrength);
    PROP(Hand, sphereRadius);
    PROP(Hand, timeVisible);

    BOX(Hand, palmPosition);
    BOX(Hand, palmVelocity);
    BOX(Hand, sphereCenter);
    BOX(Hand, stabilizedPalmPosition);
}

template <>
void fillDefault(PartRepresenterMap<SwipeGesture>& prop) {
    PROP(SwipeGesture, direction);
    PROP(SwipeGesture, durationSeconds);
    PROP(SwipeGesture, id);
    PROP(SwipeGesture, position);
    PROP(SwipeGesture, speed);
    PROP(SwipeGesture, startPosition);
}

template <>
void fillDefault(PartRepresenterMap<CircleGesture>& prop) {
    PROP(CircleGesture, center);
    PROP(CircleGesture, durationSeconds);
    PROP(CircleGesture, id);
    PROP(CircleGesture, normal);
    PROP(CircleGesture, progress);
    PROP(CircleGesture, radius);
}

template <>
void fillDefault(PartRepresenterMap<ScreenTapGesture>& prop) {
    PROP(ScreenTapGesture, direction);
    PROP(ScreenTapGesture, durationSeconds);
    PROP(ScreenTapGesture, id);
    PROP(ScreenTapGesture, position);
    PROP(ScreenTapGesture, progress);
}

template <>
void fillDefault(PartRepresenterMap<KeyTapGesture>& prop) {
    PROP(KeyTapGesture, direction);
    PROP(KeyTapGesture, durationSeconds);
    PROP(KeyTapGesture, id);
    PROP(KeyTapGesture, position);
    PROP(KeyTapGesture, progress);
}

#undef BOX
#undef PROP

template class PartRepresenterMap<Finger>;
template class PartRepresenterMap<Tool>;
template class PartRepresenterMap<Bone>;
template class PartRepresenterMap<Hand>;

template class PartRepresenterMap<SwipeGesture>;
template class PartRepresenterMap<ScreenTapGesture>;
template class PartRepresenterMap<KeyTapGesture>;
template class PartRepresenterMap<CircleGesture>;

}  // namespace leap
}  // namespace swirly
