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
    class Representer {
      public:
        virtual void represent(
            Representation&, Data const&, Context const&) const = 0;
        virtual ~Representer() {}
    };

    typedef shared_ptr<Representer> RepPtr;

    template <typename Getter>
    class GetterRepresenter : public Representer {
      public:
        GetterRepresenter(Getter getter) : getter_(getter) {}
        void represent(Representation& rep, Data const& data, Context const&)
                const override {
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

    template <typename Method>
    void defaultProperty(string const& name, Method m) {
        properties_[name] = makeRepresenter(bind(m, placeholders::_1));
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
