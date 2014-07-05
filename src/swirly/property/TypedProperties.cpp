#include <leap/Leap.h>

#include <swirly/property/TypedProperties.h>

using namespace Leap;

namespace swirly {
namespace leap {

template <>
const char* humanName<Finger>() {
    return "finger";
}

template <>
const char* humanName<Hand>() {
    return "hand";
}

template <>
const char* humanName<Tool>() {
    return "tool";
}

template <>
const char* humanName<Bone>() {
    return "bone";
}

template <>
const char* humanName<SwipeGesture>() {
    return "swipe";
}

template <>
const char* humanName<CircleGesture>() {
    return "circle";
}

template <>
const char* humanName<KeyTapGesture>()
{
    return "keytap";
}

template <>
const char* humanName<ScreenTapGesture>()
{
    return "screentap";
}

#define PROP(CLASS, NAME) \
    defaultProperty(#NAME, &CLASS::NAME)

template <>
void TypedProperties<Finger>::fillDefault() {
    PROP(Pointable, direction); // norm
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, stabilizedTipPosition); // vec
    PROP(Pointable, timeVisible);
    PROP(Pointable, tipPosition); // vec
    PROP(Pointable, tipVelocity);  // vec
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);
}

template <>
void TypedProperties<Tool>::fillDefault() {
    PROP(Pointable, direction); // norm
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, stabilizedTipPosition); // vec
    PROP(Pointable, timeVisible);
    PROP(Pointable, tipPosition); // vec
    PROP(Pointable, tipVelocity);  // vec
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);
}

template <>
void TypedProperties<Bone>::fillDefault() {
    PROP(Bone, basis); // mat
    PROP(Bone, center);  // vec
    PROP(Bone, direction); // norm
    PROP(Bone, length);
    PROP(Bone, type);
    PROP(Bone, width);
}

template <>
void TypedProperties<Hand>::fillDefault() {
    PROP(Hand, basis);
    PROP(Hand, confidence);
    PROP(Hand, direction); // norm
    PROP(Hand, grabStrength);
    PROP(Hand, palmNormal); // norm
    PROP(Hand, palmPosition); // vec
    PROP(Hand, palmVelocity);  //vec
    PROP(Hand, palmWidth);
    PROP(Hand, pinchStrength);
    PROP(Hand, sphereCenter); // vec
    PROP(Hand, sphereRadius);
    PROP(Hand, stabilizedPalmPosition); // vec
    PROP(Hand, timeVisible);
}

template <>
void TypedProperties<SwipeGesture>::fillDefault() {
    PROP(SwipeGesture, direction);
    PROP(SwipeGesture, durationSeconds);
    PROP(SwipeGesture, id);
    PROP(SwipeGesture, position);
    PROP(SwipeGesture, speed);
    PROP(SwipeGesture, startPosition);
}

template <>
void TypedProperties<CircleGesture>::fillDefault() {
    PROP(CircleGesture, center);
    PROP(CircleGesture, durationSeconds);
    PROP(CircleGesture, id);
    PROP(CircleGesture, normal);
    PROP(CircleGesture, progress);
    PROP(CircleGesture, radius);
}

template <>
void TypedProperties<ScreenTapGesture>::fillDefault() {
    PROP(ScreenTapGesture, direction);
    PROP(ScreenTapGesture, durationSeconds);
    PROP(ScreenTapGesture, id);
    PROP(ScreenTapGesture, position);
    PROP(ScreenTapGesture, progress);
}

template <>
void TypedProperties<KeyTapGesture>::fillDefault() {
    PROP(KeyTapGesture, direction);
    PROP(KeyTapGesture, durationSeconds);
    PROP(KeyTapGesture, id);
    PROP(KeyTapGesture, position);
    PROP(KeyTapGesture, progress);
}

}  // namespace leap
}  // namespace swirly

#undef PROP
