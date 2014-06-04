#pragma once

#include "Base.h"

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

namespace swirly {
namespace leap {

t_symbol* cachedGensym(string const&);

}  // namespace leap
}  // namespace swirly
