#pragma once

#include "Base.h"

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

inline void print(string const& s) {
    post(s.c_str());
}
