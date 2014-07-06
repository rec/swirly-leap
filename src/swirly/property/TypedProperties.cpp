#include <leap/Leap.h>

#include <swirly/property/TypedProperties.h>

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

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
void addBox(TypedProperties<Data>& props, string const& name, Method m,
            Restrict restrict) {
    auto getter = bind(m, placeholders::_1);
    props.properties()[name] = makeBox<Data>(getter, restrict);
}

#define PROP(CLASS, NAME) \
    addGetter(*this, #NAME, &CLASS::NAME)

#define BOX(CLASS, NAME) \
    do {                                                            \
        addBox(*this, #NAME, &CLASS::NAME, Restrict::CLAMP);        \
        addBox(*this, #NAME "Free", &CLASS::NAME, Restrict::FREE);  \
        addGetter(*this, #NAME "Raw", &CLASS::NAME);                \
    } while (false)


}  // namespace

template <>
void TypedProperties<Finger>::fillDefault() {
    PROP(Pointable, direction);
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, timeVisible);
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);

    BOX(Pointable, stabilizedTipPosition);
    BOX(Pointable, tipPosition);
    BOX(Pointable, tipVelocity);
}

template <>
void TypedProperties<Tool>::fillDefault() {
    PROP(Pointable, direction);
    PROP(Pointable, isExtended);
    PROP(Pointable, length);
    PROP(Pointable, timeVisible);
    PROP(Pointable, touchDistance);
    PROP(Pointable, touchZone);
    PROP(Pointable, width);

    BOX(Pointable, stabilizedTipPosition);
    BOX(Pointable, tipPosition);
    BOX(Pointable, tipVelocity);
}

template <>
void TypedProperties<Bone>::fillDefault() {
    PROP(Bone, basis); // A matrix - what to do with that?
    PROP(Bone, direction);
    PROP(Bone, length);
    PROP(Bone, type);
    PROP(Bone, width);

    BOX(Bone, center);
}

template <>
void TypedProperties<Hand>::fillDefault() {
    PROP(Hand, basis);
    PROP(Hand, confidence);
    PROP(Hand, direction);
    PROP(Hand, grabStrength);
    PROP(Hand, palmNormal);
    PROP(Hand, palmWidth);
    PROP(Hand, pinchStrength);
    PROP(Hand, sphereRadius);
    PROP(Hand, timeVisible);

    BOX(Hand, palmPosition);
    BOX(Hand, palmVelocity);
    BOX(Hand, sphereCenter);
    BOX(Hand, stabilizedPalmPosition);
}

template <>
void TypedProperties<SwipeGesture>::fillDefault() {
    PROP(SwipeGesture, direction);
    PROP(SwipeGesture, durationSeconds);
    PROP(SwipeGesture, id);
    PROP(SwipeGesture, position);
    PROP(SwipeGesture, speed);
    PROP(SwipeGesture, startPosition);
}

template <>
void TypedProperties<CircleGesture>::fillDefault() {
    PROP(CircleGesture, center);
    PROP(CircleGesture, durationSeconds);
    PROP(CircleGesture, id);
    PROP(CircleGesture, normal);
    PROP(CircleGesture, progress);
    PROP(CircleGesture, radius);
}

template <>
void TypedProperties<ScreenTapGesture>::fillDefault() {
    PROP(ScreenTapGesture, direction);
    PROP(ScreenTapGesture, durationSeconds);
    PROP(ScreenTapGesture, id);
    PROP(ScreenTapGesture, position);
    PROP(ScreenTapGesture, progress);
}

template <>
void TypedProperties<KeyTapGesture>::fillDefault() {
    PROP(KeyTapGesture, direction);
    PROP(KeyTapGesture, durationSeconds);
    PROP(KeyTapGesture, id);
    PROP(KeyTapGesture, position);
    PROP(KeyTapGesture, progress);
}

}  // namespace leap
}  // namespace swirly

#undef PROP
