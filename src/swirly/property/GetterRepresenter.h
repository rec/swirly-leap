#pragma once

#include <swirly/property/Represent.h>

namespace swirly {
namespace leap {

template <typename Part, typename Getter>
class GetterRepresenter : public Representer<Part> {
  public:
    GetterRepresenter(Getter getter) : getter_(getter)  {}

    void represent(Representation& rep, Part const& part, Context const&)
            const override {
        leap::represent(rep, getter_(part));
    }

  private:
    Getter const getter_;
};

template <typename Part, typename Getter>
static shared_ptr<Representer<Part>> makeRepresenter(Getter getter) {
    return make_shared<GetterRepresenter<Part, Getter>>(getter);
}

template <typename Part, typename Method>
void addGetter(PartRepresenterMap<Part>& props, string const& name, Method m) {
    props.representers()[name] = makeRepresenter<Part>(bind(m, placeholders::_1));
}

}  // namespace leap
}  // namespace swirly
