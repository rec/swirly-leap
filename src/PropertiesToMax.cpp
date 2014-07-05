#include <string.h>

#include "PropertiesToMax.h"

namespace swirly {
namespace leap {

void set_atom(t_atom* atom, string const& name, BoolHandling handling) {
    auto ch = name[0];
    if (ch == '-' or isdigit(ch)) {
        // It's a number.
        if (name.find('.') != string::npos)
            atom_setfloat(atom, atof(name.c_str()));
        else
            atom_setlong(atom, atol(name.c_str()));
        return;
    }

    if (handling == BoolHandling::AS_NUMBER) {
        // Perhaps it's a bool?
        if (name == "true") {
            atom_setlong(atom, 1);
            return;
        }
        if (name == "false") {
            atom_setlong(atom, 0);
            return;
        }
    }

    // Definitely a symbol.
    setSymbol(atom, name);
}

int PropertyRepresenter::represent(
        string name, Representation const& rep) const {
    auto size = size_;
    setSymbol(&atoms_[size++], name);
    for (auto& r: rep)
        set_atom(&atoms_[size++], r, handling_);
    return size;
}

}  // namespace leap
}  // namespace swirly
