#include "Represent.h"

using namespace Leap;

namespace swirly {
namespace leap {

JsonData representJson(bool f) {
    return f ? "true" : "false";
}

JsonData representJson(Pointable::Zone z) {
    switch (z) {
      case Pointable::ZONE_HOVERING: return "\"hovering\"";
      case Pointable::ZONE_TOUCHING: return "\"touching\"";
      default: return "\"none\"";
    }
}

JsonData representJson(Bone::Type t) {
    switch (t) {
      case Bone::TYPE_METACARPAL: return "\"metacarpal\"";
      case Bone::TYPE_PROXIMAL: return "\"proximal\"";
      case Bone::TYPE_INTERMEDIATE: return "\"intermediate\"";
      case Bone::TYPE_DISTAL: return "\"distal\"";
      default: return "\"BAD\"";
    }
}

JsonData representJson(Vector v) {
    return
        "[" +
        to_string(v.x) + ", " +
        to_string(v.y) + ", " +
        to_string(v.z) +
        "]";
}

MaxData representMax(Vector v) {
    return MaxData{
        to_string(v.x),
        to_string(v.y),
        to_string(v.z)
    };
}

JsonData representJson(Matrix m) {
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

MaxData representMax(Matrix m) {
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
