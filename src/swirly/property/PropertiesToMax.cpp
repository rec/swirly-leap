#include <string.h>

#include <swirly/property/PropertiesToMax.h>

namespace swirly {
namespace leap {

void set_atom(t_atom* atom, string const& name) {
    auto ch = name[0];
    if (ch == '-' or isdigit(ch)) {
        // It's a number.
        if (name.find('.') != string::npos)
            atom_setfloat(atom, atof(name.c_str()));
        else
            atom_setlong(atom, atol(name.c_str()));
        return;
    }

    // Definitely a symbol.
    setSymbol(atom, name);
}

int PropertyRepresenter::represent(
    string const& name, Representation const& rep) const {
    auto size = size_;
    setSymbol(&atoms_[size++], name);
    for (auto& r: rep)
        set_atom(&atoms_[size++], r);
    return size;
}

#if 0
template <typename Data, int MAX_ATOMS = 20>
void propertiesToMax(
        void* outlet,
        Representation const& prefix,
        Context const& context) {
    t_atom atoms[MAX_ATOMS];
    for (auto i = 0; i < prefix.size(); ++i)
        set_atom(&atoms[i], prefix[i]);

    t_symbol* symbol = cachedGensym(prefix[0]);
    PropertyRepresenter pr(prefix.size(), atoms);
    outlet_anything(outlet, cachedGensym("framestart"), 0, nullptr);

    for (auto p: properties.properties()) {
        Representation rep;
        auto const& representer = p.second;
        representer->represent(rep, data, context);
        auto size = pr.represent(p.first, rep);
        outlet_anything(outlet, symbol, size - 1, atoms + 1);
    }
    outlet_anything(outlet, cachedGensym("frameend"), 0, nullptr);
}
#endif

}  // namespace leap
}  // namespace swirly
