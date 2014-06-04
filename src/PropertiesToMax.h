#include <map>
#include <string.h>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "Gensym.h"
#include "Properties.h"

namespace swirly {
namespace leap {

template <typename Data>
void sendToMax(const Properties<Data>& properties,
               Data const& data, void* outlet, const vector<string>& parts) {
    t_atom atoms[20];
    auto size = 0;
    for (auto i = 0; i < size; ++i)
        atom_setsym(&atoms[size++], cachedGensym(parts[i]));

    t_symbol* symbol = cachedGensym(parts[0]);
    for (auto p: properties.properties_) {
        auto const& name = p.first;
        auto const& representer = p.second;
        atom_setsym(&atoms[size++], cachedGensym(name));
        auto rep = representer.max(data);
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
                if (name == "true") {
                    atom_setlong(&atoms[size++], 1);
                } else if (name == "false") {
                    atom_setlong(&atoms[size++], 0);
                } else {
                    if (name[0] == "" and name[name.size() - 1] == "")
                        name = name.substr(name.size() - 2);
                    atom_setsym(&atoms[size++], cachedGensym(name));
                }
            }
        }

        outlet_anything(outlet, symbol, size - 1, atoms + 1);
    }
}

}  // namespace leap
}  // namespace swirly
