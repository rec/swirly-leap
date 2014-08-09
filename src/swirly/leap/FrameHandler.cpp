#include <array>

#include <leap/Leap.h>

#include <swirly/leap/FrameHandler.h>

#include <swirly/leap/Config.h>
#include <swirly/leap/Getter.h>
#include <swirly/leap/LeapUtil.h>
#include <swirly/represent/MasterRepresenter.h>

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

template <typename Part>
void addRepresentation(Part const& part, Representation& rep) {
}

void addRepresentation(Finger const& finger, Representation& rep) {
    auto handType = whichHand(finger.hand());
    rep.push_back(handType == NO_HAND ? "none" : HAND_NAME[handType]);
}

template <typename Part, typename Type>
char const* getName(SwitchArray const& partMap, Type type) {
    return partMap.isOn(type) ? partMap.name(type).c_str() : nullptr;
}

template <>
char const* getName<SwipeGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_SWIPE ? "" : nullptr;
}

template <>
char const* getName<CircleGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_CIRCLE ? "" : nullptr;
}

template <>
char const* getName<KeyTapGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_KEY_TAP ? "" : nullptr;
}

template <>
char const* getName<ScreenTapGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_SCREEN_TAP ? "" : nullptr;
}

template <typename Part, typename Type>
bool accept(SwitchArray const& partMap, Type type) {
    return partMap.isOn(type);
}

template <>
bool accept<SwipeGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_SWIPE;
}

template <>
bool accept<CircleGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_CIRCLE;
}

template <>
bool accept<KeyTapGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_KEY_TAP;
}

template <>
bool accept<ScreenTapGesture>(SwitchArray const&, Gesture::Type type) {
    return type == Gesture::TYPE_SCREEN_TAP;
}

template <typename P>
void doPrint(Context const& context, string const& s) {
}

template <>
void doPrint<SwipeGesture>(Context const& context, string const& s) {
    context.config_.logger_.log("swipe " + s);
}

template <>
void doPrint<CircleGesture>(Context const& context, string const& s) {
    context.config_.logger_.log("circle " + s);
}

template <>
void doPrint<ScreenTapGesture>(Context const& context, string const& s) {
    context.config_.logger_.log("screentap " + s);
}

template <>
void doPrint<KeyTapGesture>(Context const& context, string const& s) {
    context.config_.logger_.log("keytap " + s);
}

template <typename Part>
void framePart(Context const& context,
               Callback<Representation const&>& handler) {
    auto partMap = context.config_.representers().getPartMap<Part>();
    if (not partMap)
        return;

    auto const& partList = getPartList(context.frame_, Part());
    for (auto const& part: partList) {
        doPrint<Part>(context, "here");
        auto type = getType(part);
        if (auto name = getName<Part>(*partMap, type)) {
            doPrint<Part>(context, "YES!");
            for (auto const& r: partMap->partMap().representers()) {
                Representation rep{partName<Part>()};
                addRepresentation(part, rep);
                if (name[0])
                    rep.push_back(name);
                rep.push_back(r.first);
                r.second->represent(rep, part, context);
                handler.callback(rep);
            }
        }
    }
}

} // namespace


void FrameHandler::onFrame(Frame const& frame) {
    if (!outlet_) {
        config_.logger_.err("No outlet!");
        return;
    }

#if 1
    auto gestures = frame.gestures();
    if (gestures.count()) {
        config_.logger_.log("AHA! " + to_string(gestures.count()));
        for (auto gesture: gestures) {
            config_.logger_.log("Number: " + to_string(gesture.type()));
        }
    }
#endif

    Context context(frame, config_);

    callback({"framestart"});

    framePart<Finger>(context, *this);
    framePart<Hand>(context, *this);
    framePart<Tool>(context, *this);

    framePart<CircleGesture>(context, *this);
    framePart<KeyTapGesture>(context, *this);
    framePart<ScreenTapGesture>(context, *this);
    framePart<SwipeGesture>(context, *this);

    callback({"frameend"});
}

}  // namespace leap
}  // namespace swirly
