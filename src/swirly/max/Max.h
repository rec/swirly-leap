#pragma once

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include <swirly/base/Base.h>

inline void print(string const& s) {
    post(s.c_str());
}
