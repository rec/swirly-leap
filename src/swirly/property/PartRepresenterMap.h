#pragma once

#include <swirly/base/Logger.h>
#include <swirly/property/Context.h>
#include <swirly/property/RepresenterMap.h>
#include <swirly/property/Represent.h>

namespace swirly {
namespace leap {

/** A collection of properties attached to a specific Leap Frame part. */
template <typename Part>
class PartRepresenterMap : public RepresenterMap {
  public:
    typedef shared_ptr<Representer<Part>> RepPtr;
    typedef map<string, RepPtr> Map;

    Map& representers() { return representers_; }
    const Map& representers() const { return representers_; }

    bool addRepresenter(string const& name) override;
    void dump(string const& name, Logger const& logger) const;
    bool empty() const { return representers_.empty(); }
    void describe(Representation&) const;
    void setAll();

  private:
    static const PartRepresenterMap<Part>& getDefault();

    Map representers_;
};

}  // namespace leap
}  // namespace swirly
