#include <leap/Leap.h>

#include <swirly/property/TypedProperties.h>

using namespace Leap;

namespace swirly {
namespace leap {

template <> const char* humanName<Finger>()           { return "finger"; }
template <> const char* humanName<Hand>()             { return "hand"; }
template <> const char* humanName<Tool>()             { return "tool"; }
template <> const char* humanName<Bone>()             { return "bone"; }
template <> const char* humanName<SwipeGesture>()     { return "swipe"; }
template <> const char* humanName<CircleGesture>()    { return "circle"; }
template <> const char* humanName<KeyTapGesture>()    { return "keytap"; }
template <> const char* humanName<ScreenTapGesture>() { return "screentap"; }

#define PROP(CLASS, NAME) \
    defaultProperty(#NAME, &CLASS::NAME)

#ifdef READY

#define PROP_BOX(CLASS, NAME) \
    defaultProperty(#NAME "Raw", &CLASS::NAME); \
    defaultBoxProperty(#NAME, &CLASS::NAME)

#define PROP_BOX_NORMAL(CLASS, NAME) \
    defaultProperty(#NAME "Raw", &CLASS::NAME); \
    defaultNormalBoxProperty(#NAME, &CLASS::NAME)

#else

#define PROP_BOX(CLASS, NAME) \
    defaultProperty(#NAME, &CLASS::NAME)
#define PROP_BOX_NORMAL(CLASS, NAME) \
    defaultProperty(#NAME, &CLASS::NAME)

#endif

template <>
void TypedProperties<Finger>::fillDefault() {
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, timeVisible);
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);

    PROP_BOX(Pointable, stabilizedTipPosition);
    PROP_BOX(Pointable, tipPosition);
    PROP_BOX(Pointable, tipVelocity);

    PROP_BOX_NORMAL(Pointable, direction);
}

template <>
void TypedProperties<Tool>::fillDefault() {
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, timeVisible);
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);

    PROP_BOX(Pointable, stabilizedTipPosition);
    PROP_BOX(Pointable, tipPosition);
    PROP_BOX(Pointable, tipVelocity);

    PROP_BOX_NORMAL(Pointable, direction);
}

template <>
void TypedProperties<Bone>::fillDefault() {
    PROP(Bone, basis); // A matrix - what to do with that?
    PROP(Bone, length);
    PROP(Bone, type);
    PROP(Bone, width);

    PROP_BOX(Bone, center);

    PROP_BOX_NORMAL(Bone, direction);
}

template <>
void TypedProperties<Hand>::fillDefault() {
    PROP(Hand, basis);
    PROP(Hand, confidence);
    PROP(Hand, grabStrength);
    PROP(Hand, palmWidth);
    PROP(Hand, pinchStrength);
    PROP(Hand, sphereRadius);
    PROP(Hand, timeVisible);

    PROP_BOX(Hand, palmPosition);
    PROP_BOX(Hand, palmVelocity);
    PROP_BOX(Hand, sphereCenter);
    PROP_BOX(Hand, stabilizedPalmPosition);

    PROP_BOX_NORMAL(Hand, direction);
    PROP_BOX_NORMAL(Hand, palmNormal);
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
