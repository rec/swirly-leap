#pragma once

#include <swirly/max/Gensym.h>
#include <swirly/max/MessageBuffer.h>

namespace swirly {
namespace leap {

class DictBuffer : public MessageBuffer {
  public:
    DictBuffer() : dict_(dictionary_new()) {}
    ~DictBuffer() { object_free(dict_); }

    void clear() override
    {
        dictionary_clear(dict_);
    }

    void add(Representation const& rep) override
    {
        auto dict = dict_;
        for (int i = 0; i < rep.size() - 2; ++i) {
            t_dictionary* d = nullptr;
            auto key = cachedGensym(rep[i]);
            auto error = dictionary_getdictionary(dict, key, (t_object**) &d);
            if (error or !d) {
                d = dictionary_new();
                dictionary_appenddictionary(dict, key, (t_object*) d);
            }
            dict = d;
        }
        auto key = cachedGensym(rep[rep.size() - 1]);
        t_atom atom;
        setAtom(&atom, rep.back());

        dictionary_appendatom(dict, key, &atom);
    }

    void send(void* outlet) override
    {
        t_atom atom;
        setSymbol(&atom, "leap");
        // outlet_anything(outlet, dict_,
    }

    t_dictionary* dict_;
};

}  // namespace leap
}  // namespace swirly
