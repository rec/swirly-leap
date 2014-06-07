#include <string.h>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "BoolHandling.h"
#include "Gensym.h"
#include "Properties.h"

namespace swirly {
namespace leap {

template <typename Data, int MAX_ATOMS = 20>
void propertiesToMax(
        void* outlet,
        Data const& data,
        const Properties<Data>& properties,
        Representation const& prefix,
        BoolHandling boolHandling) {
    t_atom atoms[MAX_ATOMS];
    auto size = 0;
    for (auto i = 0; i < size; ++i)
        atom_setsym(&atoms[size++], cachedGensym(prefix[i]));

    t_symbol* symbol = cachedGensym(prefix[0]);
    for (auto p: properties.properties()) {
        auto const& name = p.first;
        auto const& representer = p.second;
        atom_setsym(&atoms[size++], cachedGensym(name));

        Representation rep;
        representer.represent(rep, data);
        if (rep.size() > 1) {  // must be Vector or Matrix.
            for (auto i = 0; i < rep.size(); ++i)
                atom_setfloat(&atoms[size++], atof(rep[i].c_str()));
        } else {
            if (isdigit(name[0])) {
                if (name.find('.') == string::npos)
                    atom_setfloat(&atoms[size++], atof(name.c_str()));
                else
                    atom_setlong(&atoms[size++], atol(name.c_str()));
            } else {
                if (boolHandling == BoolHandling::AS_NUMBER) {
                    if (name == "true") {
                        atom_setlong(&atoms[size++], 1);
                        continue;
                    } else if (name == "false") {
                        atom_setlong(&atoms[size++], 0);
                        continue;
                    }
                }
                if (name[0] == "" and name[name.size() - 1] == "")
                    name = name.substr(name.size() - 2);
                atom_setsym(&atoms[size++], cachedGensym(name));
            }
        }

        outlet_anything(outlet, symbol, size - 1, atoms + 1);
    }
}

}  // namespace leap
}  // namespace swirly
