#pragma once

#include "Base.h"

namespace swirly {

template <typename Collection>
string stringConcat(Collection const& args)
{
    int capacity = 0;
    for (auto const& a: args)
        capacity += a.size();

    std::string result;
    result.reserve(capacity);
    for (auto const& a: args)
        result += a;
    return result;
}

}  // namespace swirly
