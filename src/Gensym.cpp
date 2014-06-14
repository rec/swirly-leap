#include <unordered_map>
#include "Gensym.h"

namespace swirly {
namespace leap {

namespace {

void removeQuotes(string& s) {
    if (s.size() > 1 and s.front() == '"' and s.back() == '"')
        s = s.substr(1, s.size() - 2);
}

}

static unordered_map<string, t_symbol*> SYMBOLS;

t_symbol* cachedGensym(string name) {
    removeQuotes(name);
    auto i = SYMBOLS.find(name);
    if (i != SYMBOLS.end())
        return i->second;
    auto result = gensym(name.c_str());
    SYMBOLS[name] = result;
    return result;
}

}  // namespace leap
}  // namespace swirly
