#include <string.h>

#include <swirly/max/Gensym.h>
#include <swirly/max/Max.h>
#include <swirly/property/PartRepresenterMap.h>

namespace swirly {
namespace leap {

class PropertyRepresenter {
  public:
    PropertyRepresenter(int size, t_atom* atoms) : size_(size), atoms_(atoms) {}
    int represent(string const& name, Representation const& rep) const;

  private:
    int size_;
    t_atom* atoms_;
};

void set_atom(t_atom* atom, string const& s);

template <typename Data, int MAX_ATOMS = 20>
void propertiesToMax(
        void* outlet,
        Data const& data,
        const PartRepresenterMap<Data>& properties,
        Representation const& prefix,
        Context const& context) {
    t_atom atoms[MAX_ATOMS];
    for (auto i = 0; i < prefix.size(); ++i)
        set_atom(&atoms[i], prefix[i]);

    t_symbol* symbol = cachedGensym(prefix[0]);
    PropertyRepresenter pr(prefix.size(), atoms);
    outlet_anything(outlet, cachedGensym("framestart"), 0, nullptr);

    for (auto p: properties.representers()) {
        Representation rep;
        auto const& representer = p.second;
        representer->represent(rep, data, context);
        auto size = pr.represent(p.first, rep);
        outlet_anything(outlet, symbol, size - 1, atoms + 1);
    }
    outlet_anything(outlet, cachedGensym("frameend"), 0, nullptr);
}

}  // namespace leap
}  // namespace swirly
