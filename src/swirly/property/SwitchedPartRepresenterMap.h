#pragma once

#include <swirly/leap/Getter.h>
#include <swirly/property/SwitchArray.h>
#include <swirly/property/PartRepresenterMap.h>
#include <swirly/util/Split.h>

namespace swirly {
namespace leap {

template <typename Part>
struct SwitchedPartRepresenterMap : SwitchArray {
    using SwitchArray::SwitchArray;

    bool set(string const& name) override {
        return SwitchArray::set(name) or representers_.addRepresenter(name);
    }

    void dump(string const& name, Logger const& logger) const override {
        if (not representers_.empty()) {
            SwitchArray::dump(name, logger);
            representers_.dump(name, logger);
        }
    }

    bool empty() const override {
        return SwitchArray::empty() or representers_.empty();
    }

    void represent(Representation& rep) const override {
        SwitchArray::represent(rep);
        representers_.represent(rep);
    }

    PartRepresenterMap<Part>& representers() { return representers_; }

  private:
    PartRepresenterMap<Part> representers_;
};

}  // namespace leap
}  // namespace swirly
