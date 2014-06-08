#pragma once

#include <string.h>

#include "Properties.h"
#include "Represent.h"

namespace swirly {
namespace leap {

template <typename Data>
const char* humanName();

template <typename Data>
class TypedProperties : public Properties {
  public:
    class Representer {
      public:
        virtual void represent(Representation&, Data const&) const = 0;
        virtual ~Representer() {}
    };

    typedef shared_ptr<Representer> RepPtr;

    template <typename Getter>
    class GetterRepresenter : public Representer {
      public:
        GetterRepresenter(Getter getter) : getter_(getter) {}
        void represent(Representation& rep, Data const& data) const override {
            leap::represent(rep, getter_(data));
        }

      private:
        Getter const getter_;
    };

    template <typename Getter>
    static RepPtr makeRepresenter(Getter getter) {
        return RepPtr(new GetterRepresenter<Getter>(getter));
    }

    typedef map<string, RepPtr> Map;

    Map& properties() { return properties_; }
    const Map& properties() const { return properties_; }

    bool addProperty(string const& name) override {
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

    template <typename Method>
    void defaultProperty(string const& name, Method m) {
        properties_[name] = makeRepresenter(bind(m, placeholders::_1));
    }

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
