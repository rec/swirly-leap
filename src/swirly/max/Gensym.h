#pragma once

#include <swirly/max/Max.h>

namespace swirly {
namespace leap {

t_symbol* cachedGensym(string);

inline void setSymbol(t_atom* atom, string name) {
    atom_setsym(atom, cachedGensym(name));
}

inline const char* getSymbol(t_atom* atom) {
    return atom_getsym(atom)->s_name;
}

}  // namespace leap
}  // namespace swirly
