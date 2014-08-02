#pragma once

#include <swirly/represent/Represent.h>

namespace swirly {
namespace leap {

enum class Restrict { FREE, CLAMP };

template <typename Part, typename Getter>
class Boxer : public Representer<Part> {
  public:
    Boxer(Getter g, Restrict r) : getter_(g), clamp_(r == Restrict::CLAMP) {}

    void represent(Representation& rep, Part const& part,
                   Context const& context) const override {
        auto v = getter_(part);
        v = context.box_.normalizePoint(v, clamp_);
        leap::represent(rep, v);
    }

  private:
    Getter const getter_;
    bool const clamp_;
};

template <typename Part, typename Getter>
static shared_ptr<Representer<Part>> makeBox(Getter get, Restrict restrict) {
    return make_shared<Boxer<Part, Getter>>(get, restrict);
}

template <typename Part, typename Method>
void addBox(PartRepresenterMap<Part>& representers, string const& name,
            Method m, Restrict restrict) {
    auto getter = bind(m, placeholders::_1);
    representers.representers()[name] = makeBox<Part>(getter, restrict);
}

}  // namespace leap
}  // namespace swirly
