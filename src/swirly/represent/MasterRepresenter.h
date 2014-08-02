#pragma once

#include <swirly/represent/SwitchedPartRepresenterMap.h>

namespace swirly {
namespace leap {

/** The MasterRepresenter */
class MasterRepresenter {
  public:
    MasterRepresenter(Logger const& logger, Leap::Controller& controller);

    template <typename Part>
    SwitchedPartRepresenterMap<Part>* getPartMap() const {
        auto i = map_.find(partName<Part>());
        if (i == map_.end())
            return nullptr;
        return dynamic_cast<SwitchedPartRepresenterMap<Part>*>(i->second.get());
    }

    void dump() const;
    void finish();
    void set(string const& s);

    /** Turn everything on.*/
    void setAll();

    typedef map<string, unique_ptr<SwitchArray>> Map;

  private:
    Logger const& logger_;
    Controller& controller_;
    Map map_;
};

}  // namespace leap
}  // namespace swirly
