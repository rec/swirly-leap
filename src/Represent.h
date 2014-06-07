#pragma once

#include "Base.h"

#include "leap/Leap.h"
using namespace Leap;

namespace swirly {
namespace leap {

string to_string(Bone::Type);
string to_string(Pointable::Zone);
string to_string(bool);

typedef vector<string> Representation;

template <typename Data>
void represent(Representation& rep, Data d) {
    rep.push_back(to_string(d));
}

void represent(Representation&, Matrix);
void represent(Representation&, Vector);

}  // namespace leap
}  // namespace swirly
