#pragma once

#include <swirly/max/Max.h>

namespace swirly {
namespace leap {

void setAtom(t_atom* atom, string const& name);

struct Message {
    using Atoms = vector<t_atom>;

    t_symbol* symbol;
    Atoms atoms;

    void send(void* outlet) {
        outlet_anything(outlet, symbol, atoms.size(), &atoms[0]);
    }
};

using Messages = vector<Message>;

Message makeMessage(Representation&);

}  // namespace leap
}  // namespace swirly
