#pragma once

#include <swirly/leap/Getter.h>
#include <swirly/property/Switch.h>
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

class SwitchedPartRepresenterMapMap {
  public:
    template <typename Part>
    void add(Representation const& rep) {
        map_[partName<Part>()].reset(new SwitchedPartRepresenterMap<Part>(rep));
    }

    template <typename Part>
    SwitchedPartRepresenterMap<Part>* get() const {
        auto i = map_.find(partName<Part>());
        if (i == map_.end())
            return nullptr;
        return dynamic_cast<SwitchedPartRepresenterMap<Part>*>(i->second.get());
    }

    void dump(Logger const& logger) const {
        for (auto &i: map_)
            i.second->dump(i.first, logger);
    }

    void finish() {
        for (auto &i: map_)
            i.second->finish();
    }

    void set(string const& s, Logger const& logger) {
        auto const value = splitEquals(s, Config::VALUE_SEPARATOR);
        auto const& name = value.first;
        auto const& values = value.second;
        if (name.empty() or values.empty()) {
            logger.err("Don't understand argument " + s);
            return;
        }

        auto i = map_.find(name);
        if (i != map_.end()) {
            for (auto const& v: values) {
                if (!i->second->set(v))
                    logger.err("Don't understand switch value " + s);
            }
        } else {
            logger.err("Don't understand argument " + s);
        }
    }

  private:
    typedef map<string, unique_ptr<SwitchArray>> Map;
    Map map_;
};

}  // namespace leap
}  // namespace swirly
