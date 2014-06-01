#include "Properties.h"

#include "leap/Leap.h"

using namespace Leap;

namespace swirly {
namespace leap {

template <>
void Property<Pointable>::fillDefault() {
    property("direction", &Pointable::direction);
    property("isExtended", &Pointable::isExtended);
    property("length", &Pointable::length);
    property("stabilizedTipPosition",
             &Pointable::stabilizedTipPosition);
    property("timeVisible", &Pointable::timeVisible);
    property("tipPosition", &Pointable::tipPosition);
    property("tipVelocity", &Pointable::tipVelocity);
    property("touchDistance", &Pointable::touchDistance);
    property("touchZone", &Pointable::touchZone);
    property("width", &Pointable::width);
}

template <>
void Property<Bone>::fillDefault() {
    property("basis", &Bone::basis);
    property("center", &Bone::center);
    property("direction", &Bone::direction);
    property("length", &Bone::length);
    property("type", &Bone::type);
    property("width", &Bone::width);
}

template <>
void Property<Hand>::fillDefault() {
    property("basis", &Hand::basis);
    property("confidence", &Hand::confidence);
    property("direction", &Hand::direction);
    property("grabStrength", &Hand::grabStrength);
    property("palmNormal", &Hand::palmNormal);
    property("palmPosition", &Hand::palmPosition);
    property("palmVelocity", &Hand::palmVelocity);
    property("palmWidth", &Hand::palmWidth);
    property("pinchStrength", &Hand::pinchStrength);
    property("sphereCenter", &Hand::sphereCenter);
    property("sphereRadius", &Hand::sphereRadius);
    property("stabilizedPalmPosition", &Hand::stabilizedPalmPosition);
    property("timeVisible", &Hand::timeVisible);
}

template <>
void Property<SwipeGesture>::fillDefault() {
    property("direction", &SwipeGesture::direction);
    property("durationSeconds", &SwipeGesture::durationSeconds);
    property("id", &SwipeGesture::id);
    property("position", &SwipeGesture::position);
    property("speed", &SwipeGesture::speed);
    property("startPosition", &SwipeGesture::startPosition);
}

template <>
void Property<CircleGesture>::fillDefault() {
    property("center", &CircleGesture::center);
    property("durationSeconds", &CircleGesture::durationSeconds);
    property("id", &CircleGesture::id);
    property("normal", &CircleGesture::normal);
    property("progress", &CircleGesture::progress);
    property("radius", &CircleGesture::radius);
}

template <>
void Property<ScreenTapGesture>::fillDefault() {
    property("direction", &ScreenTapGesture::direction);
    property("durationSeconds", &ScreenTapGesture::durationSeconds);
    property("id", &ScreenTapGesture::id);
    property("position", &ScreenTapGesture::position);
    property("progress", &ScreenTapGesture::progress);
}

template <>
void Property<KeyTapGesture>::fillDefault() {
    property("direction", &KeyTapGesture::direction);
    property("durationSeconds", &KeyTapGesture::durationSeconds);
    property("id", &KeyTapGesture::id);
    property("position", &KeyTapGesture::position);
    property("progress", &KeyTapGesture::progress);
}

}  // namespace leap
}  // namespace swirly
