#include <string.h>

#include <swirly/max/Gensym.h>
#include <swirly/max/Max.h>
#include <swirly/property/TypedProperties.h>
#include <swirly/util/BoolHandling.h>

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
        Context const& context,
        BoolHandling handling = BoolHandling::AS_NUMBER) {
    t_atom atoms[MAX_ATOMS];
    for (auto i = 0; i < prefix.size(); ++i)
        set_atom(&atoms[i], prefix[i], handling);

    t_symbol* symbol = cachedGensym(prefix[0]);
    PropertyRepresenter pr(prefix.size(), atoms, handling);
    bool first = true;
    for (auto p: properties.properties()) {
        Representation rep;
        auto const& representer = p.second;
        representer->represent(rep, data, context);
        auto size = pr.represent(p.first, rep);
        if (first) {
            first = false;
            outlet_anything(outlet, cachedGensym("framestart"), 0, nullptr);
        }
        outlet_anything(outlet, symbol, size - 1, atoms + 1);
    }
    if (not first)
        outlet_anything(outlet, cachedGensym("frameend"), 0, nullptr);
}

}  // namespace leap
}  // namespace swirly
