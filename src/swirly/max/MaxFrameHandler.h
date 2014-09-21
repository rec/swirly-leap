#pragma once

#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>
#include <swirly/max/Gensym.h>

extern "C" {
#include "ext_critical.h"
}

namespace swirly {
namespace leap {

class MaxFrameHandler : public FrameHandler {
  public:
    using FrameHandler::FrameHandler;

    void callback(Representation const& rep) override {
        auto atomSize = rep.size() - 1;
        for (int i = 0; i < atomSize; ++i)
            setAtom(&atoms_[i], rep[i + 1]);
        auto sym = cachedGensym(rep[0]);
        critical_enter(0);
        outlet_anything(outlet_, sym, atomSize, atoms_);
        critical_exit(0);
    }

  private:
    static const int MAXIMUM_OUTPUT_SYMBOLS = 16;
    t_atom atoms_[MAXIMUM_OUTPUT_SYMBOLS];
};

}  // namespace leap
}  // namespace swirly
