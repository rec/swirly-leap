#include "Properties.h"

#include "leap/Leap.h"

using namespace Leap;

namespace swirly {
namespace leap {

template <>
void Properties<Pointable>::fillDefault() {
    addProperty("direction", &Pointable::direction);
    addProperty("isExtended", &Pointable::isExtended);
    addProperty("length", &Pointable::length);
    addProperty("stabilizedTipPosition", &Pointable::stabilizedTipPosition);
    addProperty("timeVisible", &Pointable::timeVisible);
    addProperty("tipPosition", &Pointable::tipPosition);
    addProperty("tipVelocity", &Pointable::tipVelocity);
    addProperty("touchDistance", &Pointable::touchDistance);
    addProperty("touchZone", &Pointable::touchZone);
    addProperty("width", &Pointable::width);
}

template <>
void Properties<Bone>::fillDefault() {
    addProperty("basis", &Bone::basis);
    addProperty("center", &Bone::center);
    addProperty("direction", &Bone::direction);
    addProperty("length", &Bone::length);
    addProperty("type", &Bone::type);
    addProperty("width", &Bone::width);
}

template <>
void Properties<Hand>::fillDefault() {
    addProperty("basis", &Hand::basis);
    addProperty("confidence", &Hand::confidence);
    addProperty("direction", &Hand::direction);
    addProperty("grabStrength", &Hand::grabStrength);
    addProperty("palmNormal", &Hand::palmNormal);
    addProperty("palmPosition", &Hand::palmPosition);
    addProperty("palmVelocity", &Hand::palmVelocity);
    addProperty("palmWidth", &Hand::palmWidth);
    addProperty("pinchStrength", &Hand::pinchStrength);
    addProperty("sphereCenter", &Hand::sphereCenter);
    addProperty("sphereRadius", &Hand::sphereRadius);
    addProperty("stabilizedPalmPosition", &Hand::stabilizedPalmPosition);
    addProperty("timeVisible", &Hand::timeVisible);
}

template <>
void Properties<SwipeGesture>::fillDefault() {
    addProperty("direction", &SwipeGesture::direction);
    addProperty("durationSeconds", &SwipeGesture::durationSeconds);
    addProperty("id", &SwipeGesture::id);
    addProperty("position", &SwipeGesture::position);
    addProperty("speed", &SwipeGesture::speed);
    addProperty("startPosition", &SwipeGesture::startPosition);
}

template <>
void Properties<CircleGesture>::fillDefault() {
    addProperty("center", &CircleGesture::center);
    addProperty("durationSeconds", &CircleGesture::durationSeconds);
    addProperty("id", &CircleGesture::id);
    addProperty("normal", &CircleGesture::normal);
    addProperty("progress", &CircleGesture::progress);
    addProperty("radius", &CircleGesture::radius);
}

template <>
void Properties<ScreenTapGesture>::fillDefault() {
    addProperty("direction", &ScreenTapGesture::direction);
    addProperty("durationSeconds", &ScreenTapGesture::durationSeconds);
    addProperty("id", &ScreenTapGesture::id);
    addProperty("position", &ScreenTapGesture::position);
    addProperty("progress", &ScreenTapGesture::progress);
}

template <>
void Properties<KeyTapGesture>::fillDefault() {
    addProperty("direction", &KeyTapGesture::direction);
    addProperty("durationSeconds", &KeyTapGesture::durationSeconds);
    addProperty("id", &KeyTapGesture::id);
    addProperty("position", &KeyTapGesture::position);
    addProperty("progress", &KeyTapGesture::progress);
}

}  // namespace leap
}  // namespace swirly
