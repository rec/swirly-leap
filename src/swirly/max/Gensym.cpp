#include <unordered_map>
#include <swirly/max/Gensym.h>

namespace swirly {
namespace leap {

namespace {

void removeQuotes(string& s) {
    if (s.size() > 1 and s.front() == '"' and s.back() == '"')
        s = s.substr(1, s.size() - 2);
}

unordered_map<string, t_symbol*> SYMBOLS;

}  // namespace


t_symbol* cachedGensym(string name) {
    removeQuotes(name);
    auto i = SYMBOLS.find(name);
    if (i != SYMBOLS.end())
        return i->second;
    auto result = gensym(name.c_str());
    SYMBOLS[name] = result;
    return result;
}

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

}  // namespace leap
}  // namespace swirly
