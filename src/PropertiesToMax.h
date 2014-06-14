#include <string.h>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "BoolHandling.h"
#include "Gensym.h"
#include "TypedProperties.h"

namespace swirly {
namespace leap {

class PropertyRepresenter {
  public:
    PropertyRepresenter(int size, t_atom* atoms, BoolHandling h)
            : size_(size), atoms_(atoms), handling_(h) {
    }

    int represent(string name, Representation const& rep) const;

  private:
    int size_;
    t_atom* atoms_;
    BoolHandling handling_;
};

void set_atom(t_atom* atom, string const& s, BoolHandling handling);

template <typename Data, int MAX_ATOMS = 20>
void propertiesToMax(
        void* outlet,
        Data const& data,
        const TypedProperties<Data>& properties,
        Representation const& prefix,
        BoolHandling handling = BoolHandling::AS_NUMBER) {
    t_atom atoms[MAX_ATOMS];
    for (auto i = 0; i < prefix.size(); ++i)
        set_atom(&atoms[i], prefix[i], handling);

    t_symbol* symbol = cachedGensym(prefix[0]);
    PropertyRepresenter pr(prefix.size(), atoms, handling);
    for (auto p: properties.properties()) {
        Representation rep;
        auto const& representer = p.second;
        representer->represent(rep, data);
        auto size = pr.represent(p.first, rep);
        outlet_anything(outlet, symbol, size - 1, atoms + 1);
    }
}

}  // namespace leap
}  // namespace swirly
