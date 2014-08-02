#pragma once

#include <swirly/leap/FrameHandler.h>
#include <swirly/max/Max.h>
#include <swirly/max/Gensym.h>

namespace swirly {
namespace leap {

class MaxFrameHandler : public FrameHandler {
  public:
    using FrameHandler::FrameHandler;

    void callback(Representation const& rep) override {
        auto atomSize = rep.size() - 1;
        for (int i = 0; i < atomSize; ++i)
            setAtom(&atoms_[i], rep[i + 1]);
        outlet_anything(outlet_, cachedGensym(rep[0]), atomSize, atoms_);
    }

  private:
    static const int MAXIMUM_OUTPUT_SYMBOLS = 16;
    t_atom atoms_[MAXIMUM_OUTPUT_SYMBOLS];
};

}  // namespace leap
}  // namespace swirly
