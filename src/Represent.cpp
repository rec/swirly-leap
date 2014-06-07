#include "Represent.h"

using namespace Leap;

namespace swirly {
namespace leap {

string to_string(bool f) {
    return f ? "true" : "false";
}

string to_string(Pointable::Zone z) {
    switch (z) {
      case Pointable::ZONE_HOVERING: return "\"hovering\"";
      case Pointable::ZONE_TOUCHING: return "\"touching\"";
      default: return "\"none\"";
    }
}

string to_string(Bone::Type t) {
    switch (t) {
      case Bone::TYPE_METACARPAL: return "\"metacarpal\"";
      case Bone::TYPE_PROXIMAL: return "\"proximal\"";
      case Bone::TYPE_INTERMEDIATE: return "\"intermediate\"";
      case Bone::TYPE_DISTAL: return "\"distal\"";
      default: return "\"BAD\"";
    }
}

void represent(Representation& rep, Vector v) {
    represent(rep, v.x);
    represent(rep, v.y);
    represent(rep, v.z);
}

void represent(Representation& rep, Matrix m) {
    represent(rep, m.xBasis.x);
    represent(rep, m.xBasis.y);
    represent(rep, m.xBasis.z);
    represent(rep, m.yBasis.x);
    represent(rep, m.yBasis.y);
    represent(rep, m.yBasis.z);
    represent(rep, m.zBasis.x);
    represent(rep, m.zBasis.y);
    represent(rep, m.zBasis.z);
    represent(rep, m.origin.x);
    represent(rep, m.origin.y);
    represent(rep, m.origin.z);
}

}  // namespace leap
}  // namespace swirly
