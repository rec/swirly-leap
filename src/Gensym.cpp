#include <unordered_map>
#include "Base.h"

namespace swirly {
namespace leap {

static unordered_map<string, t_symbol*> SYMBOLS;

t_symbol* cachedGensym(string const& name) {
    auto i = SYMBOLS.find(name);
    if (i != SYMBOLS.end())
        return i->second;
    auto result = gensym(name.c_str());
    SYMBOLS[name] = result;
    return result;
}

}  // namespace leap
}  // namespace swirly
