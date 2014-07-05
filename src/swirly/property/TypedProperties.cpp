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

template <>
void TypedProperties<Finger>::fillDefault() {
    defaultProperty("direction", &Pointable::direction);
    defaultProperty("isExtended", &Pointable::isExtended);
    defaultProperty("length", &Pointable::length);
    defaultProperty("stabilizedTipPosition", &Pointable::stabilizedTipPosition);
    defaultProperty("timeVisible", &Pointable::timeVisible);
    defaultProperty("tipPosition", &Pointable::tipPosition);
    defaultProperty("tipVelocity", &Pointable::tipVelocity);
    defaultProperty("touchDistance", &Pointable::touchDistance);
    defaultProperty("touchZone", &Pointable::touchZone);
    defaultProperty("width", &Pointable::width);
}

template <>
void TypedProperties<Tool>::fillDefault() {
    defaultProperty("direction", &Pointable::direction);
    defaultProperty("isExtended", &Pointable::isExtended);
    defaultProperty("length", &Pointable::length);
    defaultProperty("stabilizedTipPosition", &Pointable::stabilizedTipPosition);
    defaultProperty("timeVisible", &Pointable::timeVisible);
    defaultProperty("tipPosition", &Pointable::tipPosition);
    defaultProperty("tipVelocity", &Pointable::tipVelocity);
    defaultProperty("touchDistance", &Pointable::touchDistance);
    defaultProperty("touchZone", &Pointable::touchZone);
    defaultProperty("width", &Pointable::width);
}

template <>
void TypedProperties<Bone>::fillDefault() {
    defaultProperty("basis", &Bone::basis);
    defaultProperty("center", &Bone::center);
    defaultProperty("direction", &Bone::direction);
    defaultProperty("length", &Bone::length);
    defaultProperty("type", &Bone::type);
    defaultProperty("width", &Bone::width);
}

template <>
void TypedProperties<Hand>::fillDefault() {
    defaultProperty("basis", &Hand::basis);
    defaultProperty("confidence", &Hand::confidence);
    defaultProperty("direction", &Hand::direction);
    defaultProperty("grabStrength", &Hand::grabStrength);
    defaultProperty("palmNormal", &Hand::palmNormal);
    defaultProperty("palmPosition", &Hand::palmPosition);
    defaultProperty("palmVelocity", &Hand::palmVelocity);
    defaultProperty("palmWidth", &Hand::palmWidth);
    defaultProperty("pinchStrength", &Hand::pinchStrength);
    defaultProperty("sphereCenter", &Hand::sphereCenter);
    defaultProperty("sphereRadius", &Hand::sphereRadius);
    defaultProperty("stabilizedPalmPosition", &Hand::stabilizedPalmPosition);
    defaultProperty("timeVisible", &Hand::timeVisible);
}

template <>
void TypedProperties<SwipeGesture>::fillDefault() {
    defaultProperty("direction", &SwipeGesture::direction);
    defaultProperty("durationSeconds", &SwipeGesture::durationSeconds);
    defaultProperty("id", &SwipeGesture::id);
    defaultProperty("position", &SwipeGesture::position);
    defaultProperty("speed", &SwipeGesture::speed);
    defaultProperty("startPosition", &SwipeGesture::startPosition);
}

template <>
void TypedProperties<CircleGesture>::fillDefault() {
    defaultProperty("center", &CircleGesture::center);
    defaultProperty("durationSeconds", &CircleGesture::durationSeconds);
    defaultProperty("id", &CircleGesture::id);
    defaultProperty("normal", &CircleGesture::normal);
    defaultProperty("progress", &CircleGesture::progress);
    defaultProperty("radius", &CircleGesture::radius);
}

template <>
void TypedProperties<ScreenTapGesture>::fillDefault() {
    defaultProperty("direction", &ScreenTapGesture::direction);
    defaultProperty("durationSeconds", &ScreenTapGesture::durationSeconds);
    defaultProperty("id", &ScreenTapGesture::id);
    defaultProperty("position", &ScreenTapGesture::position);
    defaultProperty("progress", &ScreenTapGesture::progress);
}

template <>
void TypedProperties<KeyTapGesture>::fillDefault() {
    defaultProperty("direction", &KeyTapGesture::direction);
    defaultProperty("durationSeconds", &KeyTapGesture::durationSeconds);
    defaultProperty("id", &KeyTapGesture::id);
    defaultProperty("position", &KeyTapGesture::position);
    defaultProperty("progress", &KeyTapGesture::progress);
}

}  // namespace leap
}  // namespace swirly
