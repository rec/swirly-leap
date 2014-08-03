#include <array>

#include <leap/Leap.h>

#include <swirly/leap/FrameHandler.h>

#include <swirly/leap/Config.h>
#include <swirly/leap/Getter.h>
#include <swirly/leap/LeapUtil.h>
#include <swirly/property/MasterRepresenter.h>

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

template <typename Part>
void framePart(Context const& context, FrameHandler& handler) {
    auto partMap = context.config_.representers().getPartMap<Part>();
    if (not partMap)
        return;

    auto const& partList = getPartList(context.frame_, Part());
    for (auto const& part: partList) {
        auto type = getType(part);
        if (not partMap->isOn(type))
            continue;

        auto name = partMap->name(type);
        for (auto const& r: partMap->partMap().representers()) {
            Representation rep{partName<Part>()};
            addRepresentation(part, rep);
            rep.push_back(name);
            r.second->represent(rep, part, context);
            handler.callback(rep);
        }
    }
}

} // namespace


void FrameHandler::onFrame(Frame const& frame) {
    if (!outlet_) {
        config_.logger_.err("No outlet!");
        return;
    }

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
