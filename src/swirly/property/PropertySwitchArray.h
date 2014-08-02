#pragma once

#include <swirly/leap/Getter.h>
#include <swirly/property/Switch.h>
#include <swirly/property/PartRepresenterMap.h>

namespace swirly {
namespace leap {

template <typename Part>
struct PropertySwitchArray : SwitchArray {
    using SwitchArray::SwitchArray;

    bool set(string const& name) override {
        return SwitchArray::set(name) or properties_.addRepresenter(name);
    }

    void dump(string const& name, Logger const& logger) const override {
        if (not properties_.empty()) {
            SwitchArray::dump(name, logger);
            properties_.dump(name, logger);
        }
    }

    bool empty() const override {
        return SwitchArray::empty() or properties_.empty();
    }

    void represent(Representation& rep) const override {
        SwitchArray::represent(rep);
        properties_.represent(rep);
    }

    PartRepresenterMap<Part> properties_;
};

struct PropertySwitchArrayMap : map<string, unique_ptr<SwitchArray>> {
    template <typename Part>
    void add(Representation const& rep) {
        (*this)[partName<Part>()].reset(new PropertySwitchArray<Part>(rep));
    }

    template <typename Part>
    PropertySwitchArray<Part>* get() const {
        auto i = find(partName<Part>());
        if (i != end())
            return dynamic_cast<PropertySwitchArray<Part>*>(i->second.get());

        return nullptr;
    }
};

}  // namespace leap
}  // namespace swirly
