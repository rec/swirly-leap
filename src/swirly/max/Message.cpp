#include <unordered_map>
#include <swirly/max/Message.h>
#include <swirly/max/Gensym.h>

namespace swirly {
namespace leap {

void setAtom(t_atom* atom, string const& name) {
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

Message makeMessage(Representation const& rep) {
    auto atomSize = rep.size() - 1;
    Message::Atoms atoms(atomSize);
    for (int i = 0; i < atomSize; ++i)
        setAtom(&atoms[i], rep[i + 1]);
    return {cachedGensym(rep[0]),  atoms};
}

}  // namespace leap
}  // namespace swirly
