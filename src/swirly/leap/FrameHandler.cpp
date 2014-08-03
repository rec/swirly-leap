#include <array>

#include <leap/Leap.h>

#include <swirly/leap/FrameHandler.h>

#include <swirly/leap/Config.h>
#include <swirly/leap/Getter.h>
#include <swirly/leap/LeapUtil.h>
#include <swirly/property/MasterRepresenter.h>
#include <swirly/property/PropertiesToMax.h>

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

string to_string(HandType t) { return HAND_NAME[t]; }

template <typename Data>
void addRepresentation(Data const& data, Representation& rep) {
}

template <>
void addRepresentation(Finger const& finger, Representation& rep) {
    auto handType = whichHand(finger.hand());
    rep.push_back(handType == NO_HAND ? "none" : HAND_NAME[handType]);
}

template <typename Part>
void onFrame(Context const& context, FrameHandler& handler) {
    auto representers = context.config_.representers().getPartMap<Part>();
    if (not representers)
        return;

    auto const& partList = getPartList(context.frame_, Part());
    for (auto const& part: partList) {
        auto type = getType(part);
        if (not representers->isOn(type))
            continue;

        auto name = representers->name(type);
        for (auto const& p: representers->representers().representers()) {
            Representation rep{partName<Part>()};
            addRepresentation(part, rep);
            rep.push_back(name);
            p.second->represent(rep, part, context);
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

#if 0
#else
    if (auto handRepresenters = config_.representers().getPartMap<Hand>()) {
        Representation rep{"hand", ""};
        auto const& hands = frame.hands();
        auto& representers = handRepresenters->representers();
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handRepresenters->isOn(handType)) {
                rep[1] = HAND_NAME[handType];
                propertiesToMax(outlet_, hand, representers, rep, context);
            }
        }
    }
#endif

    if (auto fingerRepresenters = config_.representers().getPartMap<Finger>()) {
        Representation rep{"finger", "", ""};
        auto const& fingers = frame.fingers();
        auto representers = fingerRepresenters->representers();
        for (auto const& finger: fingers) {
            auto fingerType = finger.type();
            if (fingerRepresenters->isOn(fingerType)) {
                auto handType = whichHand(finger.hand());
                if (handType != NO_HAND) {
                    rep[1] = HAND_NAME[handType];
                    rep[2] = fingerRepresenters->name(handType);
                    propertiesToMax(outlet_, finger, representers, rep, context);
                }
            }
        }
    }

    if (auto toolRepresenters = config_.representers().getPartMap<Tool>()) {
        Representation rep{"tool", "", ""};
        auto const& tools = frame.tools();
        auto representers = toolRepresenters->representers();
        auto toolCount = 0;
        for (auto const& tool: tools) {
            auto handType = whichHand(tool.hand());
            if (handType != NO_HAND) {
                rep[1] = HAND_NAME[handType];
                rep[2] = to_string(toolCount);
                propertiesToMax(outlet_, tool, representers, rep, context);
            }
            toolCount++;
        }
    }
}

}  // namespace leap
}  // namespace swirly
