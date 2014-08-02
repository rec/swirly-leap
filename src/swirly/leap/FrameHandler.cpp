#include <array>

#include <leap/Leap.h>

#include <swirly/leap/FrameHandler.h>

#include <swirly/leap/Config.h>
#include <swirly/leap/Getter.h>
#include <swirly/leap/LeapUtil.h>
#include <swirly/property/PropertiesToMax.h>
#include <swirly/property/PropertySwitchArray.h>

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

template <typename Data, typename Callback>
void onFrame(Context const& context, Callback callback) {
    if (auto properties = context.config_.switches().get<Data>()) {
        auto const& dataList = getList(context.frame_, Data());
        for (auto const& data: dataList) {
            auto name = properties->enabledName(getType(data));
            if (not name.empty()) {
                for (auto const& p: properties->properties_.properties()) {
                    Representation rep{humanName<Data>()};
                    addRepresentation(data, rep);
                    rep.push_back(name);
                    p.second->represent(rep, data, context);
                    callback(rep);
                }
            }
        }
    }
}

void myCallback(Representation&) {}

void test(Context const& context) {
    onFrame<Tool>(context, &myCallback);
}

} // namespace


void FrameHandler::onFrame(Frame const& frame) {
    if (!outlet_) {
        config_.logger_.err("No outlet!");
        return;
    }

    Context context(frame, config_);
    if (auto handProperties = config_.switches().get<Hand>()) {
        Representation rep{"hand", ""};
        auto const& hands = frame.hands();
        auto& properties = handProperties->properties_;
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handProperties->isSet(handType)) {
                rep[1] = HAND_NAME[handType];
                propertiesToMax(outlet_, hand, properties, rep, context);
            }
        }
    }

    if (auto fingerProperties = config_.switches().get<Finger>()) {
        Representation rep{"finger", "", ""};
        auto const& fingers = frame.fingers();
        auto properties = fingerProperties->properties_;
        for (auto const& finger: fingers) {
            auto fingerType = finger.type();
            if (fingerProperties->isSet(fingerType)) {
                auto handType = whichHand(finger.hand());
                if (handType != NO_HAND) {
                    rep[1] = HAND_NAME[handType];
                    rep[2] = fingerProperties->name(handType);
                    propertiesToMax(outlet_, finger, properties, rep, context);
                }
            }
        }
    }

    if (auto toolProperties = config_.switches().get<Tool>()) {
        Representation rep{"tool", "", ""};
        auto const& tools = frame.tools();
        auto properties = toolProperties->properties_;
        auto toolCount = 0;
        for (auto const& tool: tools) {
            auto handType = whichHand(tool.hand());
            if (handType != NO_HAND) {
                rep[1] = HAND_NAME[handType];
                rep[2] = to_string(toolCount);
                propertiesToMax(outlet_, tool, properties, rep, context);
            }
            toolCount++;
        }
    }
}

}  // namespace leap
}  // namespace swirly
