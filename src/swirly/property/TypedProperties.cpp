#include <leap/Leap.h>

#include <swirly/property/TypedProperties.h>
#include <swirly/property/GetterRepresenter.h>
#include <swirly/property/BoxRepresenter.h>

using namespace Leap;

namespace swirly {
namespace leap {

template <typename Data>
bool TypedProperties<Data>::addProperty(string const& name) {
    if (name == "*") {
        properties_ = getDefault().properties_;
    } else if (name == "-") {
        properties_.clear();
    } else {
        auto i = getDefault().properties_.find(name);
        if (i == getDefault().properties_.end())
            return false;
        properties_[name] = i->second;
    }

    return true;
}

template <typename Data>
void TypedProperties<Data>::dump(
    string const& name, Logger const& logger) const {
    if (not empty()) {
        string result;
        for (auto& p: properties_) {
            if (not result.empty())
                result += "+";
            result += p.first;
        }
        logger.log(name + "=" + result);
    }
}

template <typename Data>
void fillDefault(TypedProperties<Data>&);

template <typename Data>
TypedProperties<Data> newDefault() {
    TypedProperties<Data> property;
    fillDefault(property);
    return property;
}

template <typename Data>
const TypedProperties<Data>& TypedProperties<Data>::getDefault() {
    static auto const PROPERTY = newDefault<Data>();
    return PROPERTY;
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
void fillDefault(TypedProperties<Finger>& prop) {
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
void fillDefault(TypedProperties<Tool>& prop) {
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
void fillDefault(TypedProperties<Bone>& prop) {
    PROP(Bone, basis); // A matrix - what to do with that?
    PROP(Bone, direction);
    PROP(Bone, length);
    PROP(Bone, type);
    PROP(Bone, width);

    BOX(Bone, center);
}

template <>
void fillDefault(TypedProperties<Hand>& prop) {
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
void fillDefault(TypedProperties<SwipeGesture>& prop) {
    PROP(SwipeGesture, direction);
    PROP(SwipeGesture, durationSeconds);
    PROP(SwipeGesture, id);
    PROP(SwipeGesture, position);
    PROP(SwipeGesture, speed);
    PROP(SwipeGesture, startPosition);
}

template <>
void fillDefault(TypedProperties<CircleGesture>& prop) {
    PROP(CircleGesture, center);
    PROP(CircleGesture, durationSeconds);
    PROP(CircleGesture, id);
    PROP(CircleGesture, normal);
    PROP(CircleGesture, progress);
    PROP(CircleGesture, radius);
}

template <>
void fillDefault(TypedProperties<ScreenTapGesture>& prop) {
    PROP(ScreenTapGesture, direction);
    PROP(ScreenTapGesture, durationSeconds);
    PROP(ScreenTapGesture, id);
    PROP(ScreenTapGesture, position);
    PROP(ScreenTapGesture, progress);
}

template <>
void fillDefault(TypedProperties<KeyTapGesture>& prop) {
    PROP(KeyTapGesture, direction);
    PROP(KeyTapGesture, durationSeconds);
    PROP(KeyTapGesture, id);
    PROP(KeyTapGesture, position);
    PROP(KeyTapGesture, progress);
}

#undef BOX
#undef PROP

template class TypedProperties<Finger>;
template class TypedProperties<Tool>;
template class TypedProperties<Bone>;
template class TypedProperties<Hand>;

template class TypedProperties<SwipeGesture>;
template class TypedProperties<ScreenTapGesture>;
template class TypedProperties<KeyTapGesture>;
template class TypedProperties<CircleGesture>;

}  // namespace leap
}  // namespace swirly
