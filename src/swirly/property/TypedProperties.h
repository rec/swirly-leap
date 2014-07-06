#pragma once

#include <string.h>

#include <swirly/base/Logger.h>
#include <swirly/property/Context.h>
#include <swirly/property/Properties.h>
#include <swirly/property/Represent.h>

namespace swirly {
namespace leap {

template <typename Data>
const char* humanName();

template <typename Data>
class TypedProperties : public Properties {
  public:
    typedef shared_ptr<Representer<Data>> RepPtr;
    typedef map<string, RepPtr> Map;

    Map& properties() { return properties_; }
    const Map& properties() const { return properties_; }

    bool addProperty(string const& name) override {
        if (name == "*") {
            properties_ = getDefault().properties_;
        } else if (name == "-") {
            properties_.clear();
        } else {
            auto i = getDefault().properties_.find(name);
            if (i == getDefault().properties_.end())
                return false;
            properties_[name] = i->second;
        }

        return true;
    }

    void dump(string const& name, Logger const& logger) const {
        if (not empty()) {
            string result;
            for (auto& p: properties_) {
                if (not result.empty())
                    result += "+";
                result += p.first;
            }
            logger.log(name + "=" + result);
        }
    }

    bool empty() const { return properties_.empty(); }

  private:
    static TypedProperties<Data> makeDefault() {
        TypedProperties<Data> property;
        property.fillDefault();
        return property;
    }

    static const TypedProperties<Data>& getDefault() {
        static TypedProperties<Data> PROPERTY = makeDefault();
        return PROPERTY;
    }

    void fillDefault();

    Map properties_;
};

}  // namespace leap
}  // namespace swirly
