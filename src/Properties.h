#include <map>
#include <string.h>

#include "Gensym.h"
#include "Represent.h"

namespace swirly {
namespace leap {

template <typename Data>
class Property {
  public:
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

    bool addProperty(string const& name) {
        auto i = getDefault().properties_.find(name);
        if (i != getDefault().properties_.end()) {
            properties_[name] = i->second;
            return true;
        }
        return false;
    }

    void addAllProperties() {
        properties_ = getDefault().properties_;
    }

    void sendToMax(Data const& data, void* outlet, const vector<string>& parts) {
        t_atom atoms[20];
        auto size = 0;
        for (auto i = 0; i < size; ++i)
            atom_setsym(&atoms[size++], cachedGensym(parts[i]));

        t_symbol* symbol = cachedGensym(parts[0]);
        for (auto p: properties_) {
            auto const& name = p.first;
            auto const& representer = p.second;
            atom_setsym(&atoms[size++], cachedGensym(name));
            auto rep = representer.max(data);
            if (rep.size() > 1) {  // must be Vector or Matrix.
                for (auto i = 0; i < rep.size(); ++i)
                    atom_setfloat(&atoms[size++], atof(rep[i].c_str()));
            } else {
                if (isdigit(name[0])) {
                    if (name.find('.') == string::npos)
                        atom_setfloat(&atoms[size++], atof(name.c_str()));
                    else
                        atom_setlong(&atoms[size++], atol(name.c_str()));
                } else {
                    if (name == "true") {
                        atom_setlong(&atoms[size++], 1);
                    } else if (name == "false") {
                        atom_setlong(&atoms[size++], 0);
                    } else {
                        if (name[0] == "" and name[name.size() - 1] == "")
                            name = name.substr(name.size() - 2);
                        atom_setsym(&atoms[size++], cachedGensym(name));
                    }
                }
            }

            outlet_anything(outlet, symbol, size - 1, atoms + 1);
        }
    }


  private:
    void fillDefault();

    static Property<Data> makeDefault() {
        Property<Data> property;
        property.fillDefault();
        return property;
    }

    static const Property<Data>& getDefault() {
        static Property<Data> PROPERTY = makeDefault();
        return PROPERTY;
    }

    template <typename Method>
    void property(string const &name, Method m) {
        properties_[name] = makeRepresenter(std::bind(m, placeholders::_1));
    }
};

}  // namespace leap
}  // namespace swirly
