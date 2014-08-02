#pragma once

#include <leap/Leap.h>

#include <swirly/base/Base.h>

using namespace Leap;

namespace swirly {
namespace leap {

string to_string(Bone::Type);
string to_string(Pointable::Zone);
string to_string(bool);

template <typename T>
string to_string(T t) {
    return std::to_string(t);
}

template <typename Data>
void represent(Representation& rep, Data d) {
    rep.push_back(to_string(d));
}

void represent(Representation&, Matrix);
void represent(Representation&, Vector);

struct Context;

template <typename Part>
class Representer {
  public:
    virtual void represent(
            Representation&, Part const&, Context const&) const = 0;
    virtual ~Representer() {}
};

}  // namespace leap
}  // namespace swirly
