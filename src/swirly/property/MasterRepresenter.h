#pragma once

#include <swirly/property/SwitchedPartRepresenterMap.h>

namespace swirly {
namespace leap {

/** The MasterRepresenter */
class MasterRepresenter {
  public:
    MasterRepresenter();

    template <typename Part>
    SwitchedPartRepresenterMap<Part>* getPartMap() const {
        auto i = map_.find(partName<Part>());
        if (i == map_.end())
            return nullptr;
        return dynamic_cast<SwitchedPartRepresenterMap<Part>*>(i->second.get());
    }

    void dump(Logger const&) const;
    void finish();
    void set(string const& s, Logger const&);

    /** Turn everything on.*/
    void setAll();

    typedef map<string, unique_ptr<SwitchArray>> Map;

  private:
    Map map_;
};

}  // namespace leap
}  // namespace swirly
