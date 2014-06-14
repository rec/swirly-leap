#include <string.h>

#include "PropertiesToMax.h"

namespace swirly {
namespace leap {

static void removeQuotes(string& s) {
    if (s.size() > 1 and s.front() == '"' and s.back() == '"')
        s = s.substr(s.size() - 2);
}

int PropertyRepresenter::represent(
        string name, Representation const& rep) const {
    auto size = size_;
    atom_setsym(&atoms_[size++], cachedGensym(name));

    if (rep.size() > 1) {
        // It's either Vector or Matrix.
        for (auto i = 0; i < rep.size(); ++i)
            atom_setfloat(&atoms_[size++], atof(rep[i].c_str()));
        return size;
    }

    auto& first = rep[0];
    if (isdigit(first[0])) {
        // It's a number.
        if (first.find('.') != string::npos)
            atom_setfloat(&atoms_[size++], atof(first.c_str()));
        else
            atom_setlong(&atoms_[size++], atol(first.c_str()));
        return size;
    }

    if (handling_ == BoolHandling::AS_NUMBER) {
        if (name == "true") {
            atom_setlong(&atoms_[size++], 1);
            return size;
        }
        if (name == "false") {
            atom_setlong(&atoms_[size++], 0);
            return size;
        }
    }

    removeQuotes(name);
    atom_setsym(&atoms_[size++], cachedGensym(name));
    return size;
}


}  // namespace leap
}  // namespace swirly
