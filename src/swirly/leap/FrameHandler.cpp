#include <array>

#include <leap/Leap.h>

#include <swirly/leap/FrameHandler.h>
#include <swirly/leap/Config.h>
#include <swirly/leap/LeapUtil.h>
#include <swirly/property/PropertiesToMax.h>
#include <swirly/property/PropertySwitchArray.h>

using namespace Leap;

namespace swirly {
namespace leap {

namespace {

FingerList  getList(Frame f, Finger)  { return f.fingers(); }
GestureList getList(Frame f, Gesture) { return f.gestures(); }
HandList    getList(Frame f, Hand)    { return f.hands(); }
ToolList    getList(Frame f, Tool)    { return f.tools(); }

template <typename Data>
struct RepLength {
    static const int LENGTH;
};

template <typename Data> const int RepLength<Data>::LENGTH = 3;
template <>              const int RepLength<Hand>::LENGTH = 2;

template <typename Data, typename Callback>
void execute(Config const& config, Context const& context, Callback callback) {
    if (auto properties = config.switches().get<Data>()) {
        Representation rep;
        rep.resize(RepLength<Data>::LENGTH);
        rep[0] = humanName<Data>();

        auto const& list = getList(context.frame_, Data());
        for (auto const& item: list) {
            if (filter(item, context, rep))
                callback(rep);
        }
    }
}

} // namespace


void FrameHandler::onFrame(Frame const& frame) {
    Context context(frame);
    if (!outlet_) {
        config_.logger_.err("No outlet!");
        return;
    }
    if (auto handProperties = config_.switches().get<Hand>()) {
        Representation rep{"hand", ""};
        auto const& hands = frame.hands();
        auto& switches = handProperties->switches_;
        auto& properties = handProperties->properties_;
        for (auto const& hand: hands) {
            auto handType = whichHand(hand);
            if (handType != NO_HAND and switches[handType].second) {
                rep[1] = HAND_NAME[handType];
                propertiesToMax(outlet_, hand, properties, rep, context);
            }
        }
    }

    if (auto fingerProperties = config_.switches().get<Finger>()) {
        Representation rep{"finger", "", ""};
        auto const& fingers = frame.fingers();
        auto& switches = fingerProperties->switches_;
        auto properties = fingerProperties->properties_;
        for (auto const& finger: fingers) {
            auto fingerType = finger.type();
            auto sw = switches[fingerType];
            if (sw.second) {
                auto handType = whichHand(finger.hand());
                if (handType != NO_HAND) {
                    rep[1] = HAND_NAME[handType];
                    rep[2] = sw.first;
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
