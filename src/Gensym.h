#pragma once

#include "Base.h"

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

namespace swirly {
namespace leap {

t_symbol* cachedGensym(string);

}  // namespace leap
}  // namespace swirly
