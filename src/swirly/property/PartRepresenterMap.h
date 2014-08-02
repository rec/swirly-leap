#pragma once

#include <swirly/base/Logger.h>
#include <swirly/property/Context.h>
#include <swirly/property/Properties.h>
#include <swirly/property/Represent.h>

namespace swirly {
namespace leap {

/** A collection of properties attached to a specific Leap Frame part. */
template <typename Part>
class PartRepresenterMap : public Properties {
  public:
    typedef shared_ptr<Representer<Part>> RepPtr;
    typedef map<string, RepPtr> Map;

    Map& properties() { return properties_; }
    const Map& properties() const { return properties_; }

    bool addProperty(string const& name) override;
    void dump(string const& name, Logger const& logger) const;
    bool empty() const { return properties_.empty(); }
    void represent(Representation&) const;

  private:
    static const PartRepresenterMap<Part>& getDefault();

    Map properties_;
};

}  // namespace leap
}  // namespace swirly
