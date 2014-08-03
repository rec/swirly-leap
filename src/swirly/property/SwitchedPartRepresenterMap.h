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
        return SwitchArray::set(name) or partMap_.addRepresenter(name);
    }

    void dump(string const& name, Logger const& logger) const override {
        if (not partMap_.empty()) {
            SwitchArray::dump(name, logger);
            partMap_.dump(name, logger);
        }
    }

    bool empty() const override {
        return SwitchArray::empty() or partMap_.empty();
    }

    void describe(Representation& rep) const override {
        SwitchArray::describe(rep);
        partMap_.describe(rep);
    }

    void setAll() override {
        SwitchArray::setAll();
        partMap_.setAll();
    }


    PartRepresenterMap<Part>& partMap() { return partMap_; }

  private:
    PartRepresenterMap<Part> partMap_;
};

}  // namespace leap
}  // namespace swirly
