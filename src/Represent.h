#pragma include once

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

}  // namespace leap
}  // namespace swirly
