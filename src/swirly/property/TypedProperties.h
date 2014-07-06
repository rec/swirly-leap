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

    bool addProperty(string const& name) override;
    void dump(string const& name, Logger const& logger) const;
    bool empty() const { return properties_.empty(); }

  private:
    static const TypedProperties<Data>& getDefault();

    Map properties_;
};

}  // namespace leap
}  // namespace swirly
