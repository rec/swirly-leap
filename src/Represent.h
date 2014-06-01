#pragma once

#include "Base.h"

namespace swirly {
namespace leap {

typedef vector<string> MaxData;
typedef string JsonData;

template <typename Data>
JsonData representJson(Data d) {
    return to_string(d);
}

template <typename Data>
MaxData representMax(Data d) {
    return MaxData{representJson(d)};
}

JsonData representJson(Bone::Type);
JsonData representJson(Matrix);
JsonData representJson(Pointable::Zone);
JsonData representJson(Vector);
JsonData representJson(bool);

MaxData representMax(Matrix);
MaxData representMax(Vector);

}  // namespace leap
}  // namespace swirly
