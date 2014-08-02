#pragma once

#include <swirly/property/Represent.h>

namespace swirly {
namespace leap {

enum class Restrict { FREE, CLAMP };

template <typename Data, typename Getter>
class Boxer : public Representer<Data> {
  public:
    Boxer(Getter g, Restrict r) : getter_(g), clamp_(r == Restrict::CLAMP) {}

    void represent(Representation& rep, Data const& data,
                   Context const& context) const override {
        auto v = getter_(data);
        v = context.box_.normalizePoint(v, clamp_);
        leap::represent(rep, v);
    }

  private:
    Getter const getter_;
    bool const clamp_;
};

template <typename Data, typename Getter>
static shared_ptr<Representer<Data>> makeBox(Getter get, Restrict restrict) {
    return make_shared<Boxer<Data, Getter>>(get, restrict);
}

template <typename Data, typename Method>
void addBox(PartRepresenterMap<Data>& props, string const& name, Method m,
            Restrict restrict) {
    auto getter = bind(m, placeholders::_1);
    props.properties()[name] = makeBox<Data>(getter, restrict);
}

}  // namespace leap
}  // namespace swirly
