#pragma include once

#include "Represent.h"
#include "leap/Leap.h"

namespace swirly {
namespace leap {

template <> JsonData representJson(bool f) {
    return f ? "true" : "false";
}

template <> JsonData representJson(Leap::Vector v) {
    return
        "[" +
        to_string(v.x) + ", " +
        to_string(v.y) + ", " +
        to_string(v.z) +
        "]";
}

template <> MaxData representMax(Leap::Vector v) {
    return MaxData{
        to_string(v.x),
        to_string(v.y),
        to_string(v.z)
    };
}

template <> JsonData representJson(Leap::Matrix m) {
    return
        "[" +
        to_string(m.xBasis.x) + ", " +
        to_string(m.xBasis.y) + ", " +
        to_string(m.xBasis.z) + ", " +
        to_string(m.yBasis.x) + ", " +
        to_string(m.yBasis.y) + ", " +
        to_string(m.yBasis.z) + ", " +
        to_string(m.zBasis.x) + ", " +
        to_string(m.zBasis.y) + ", " +
        to_string(m.zBasis.z) + ", " +
        to_string(m.origin.x) + ", " +
        to_string(m.origin.y) + ", " +
        to_string(m.origin.z) +
        "]";
}

template <> MaxData representMax(Leap::Matrix m) {
    return MaxData{
        to_string(m.xBasis.x),
        to_string(m.xBasis.y),
        to_string(m.xBasis.z),
        to_string(m.yBasis.x),
        to_string(m.yBasis.y),
        to_string(m.yBasis.z),
        to_string(m.zBasis.x),
        to_string(m.zBasis.y),
        to_string(m.zBasis.z),
        to_string(m.origin.x),
        to_string(m.origin.y),
        to_string(m.origin.z)
    };
}

}  // namespace leap
}  // namespace swirly
