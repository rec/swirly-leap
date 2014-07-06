#pragma once

#include <swirly/property/Represent.h>

namespace swirly {
namespace leap {

template <typename Data, typename Getter>
class GetterRepresenter : public Representer<Data> {
  public:
    GetterRepresenter(Getter getter) : getter_(getter)  {}

    void represent(Representation& rep, Data const& data, Context const&)
            const override {
        leap::represent(rep, getter_(data));
    }

  private:
    Getter const getter_;
};

template <typename Data, typename Getter>
static shared_ptr<Representer<Data>> makeRepresenter(Getter getter) {
    return make_shared<GetterRepresenter<Data, Getter>>(getter);
}

template <typename Data, typename Method>
void addGetter(TypedProperties<Data>& props, string const& name, Method m) {
    props.properties()[name] = makeRepresenter<Data>(bind(m, placeholders::_1));
}

}  // namespace leap
}  // namespace swirly
