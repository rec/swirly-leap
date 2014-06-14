#pragma once

#include "Switch.h"
#include "TypedProperties.h"

namespace swirly {
namespace leap {

template <typename Data>
struct PropertySwitchArray : SwitchArray {
    using SwitchArray::SwitchArray;

    bool set(string const& name) override {
        return SwitchArray::set(name) or properties_.addProperty(name);
    }

    void dump(string const& name, Logger const& logger) const override {
        if (not properties_.empty()) {
            SwitchArray::dump(name, logger);
            properties_.dump(name, logger);
        }
    }

    TypedProperties<Data> properties_;
};

struct PropertySwitchArrayMap : map<string, unique_ptr<SwitchArray>> {
    template <typename Data>
    void add(Representation const& rep) {
        (*this)[humanName<Data>()].reset(new PropertySwitchArray<Data>(rep));
    }

    template <typename Data>
    PropertySwitchArray<Data>* get() const {
        auto i = find(humanName<Data>());
        if (i != end())
            return dynamic_cast<PropertySwitchArray<Data>*>(i->second.get());

        return nullptr;
    }
};

}  // namespace leap
}  // namespace swirly
