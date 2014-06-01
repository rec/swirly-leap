#include <map>

#include "Represent.h"

namespace swirly {
namespace leap {

template <typename Data>
struct Property {
    void fillDefault();
    class Representer {
      public:
        virtual MaxData max(Data const&) const = 0;
        virtual JsonData json(Data const&) const = 0;
        virtual ~Representer() {}
    };

    typedef shared_ptr<Representer> RepPtr;

    template <typename Getter>
    class GetterRepresenter : public Representer {
      public:
        GetterRepresenter(Getter getter) : getter_(getter) {}
        MaxData max(Data const& data) const override {
            return representMax(getter_(data));
        }
        JsonData json(Data const& data) const override {
            return representJson(getter_(data));
        }

      private:
        Getter const getter_;
    };

    template <typename Getter>
    static RepPtr makeRepresenter(Getter getter) {
        return RepPtr(new GetterRepresenter<Getter>(getter));
    }

    typedef map<string, RepPtr> PropertyMap;

    PropertyMap properties_;

    template <typename Method>
    void property(string const &name, Method m) {
        properties_[name] = makeRepresenter(std::bind(m, placeholders::_1));
    }
};

}  // namespace leap
}  // namespace swirly
