#pragma once

#include <leap/Leap.h>

#include <swirly/leap/LeapUtil.h>

using namespace Leap;

namespace swirly {
namespace leap {

inline HandList    getPartList(Frame f, Hand)    { return f.hands(); }
inline FingerList  getPartList(Frame f, Finger)  { return f.fingers(); }
inline GestureList getPartList(Frame f, Gesture) { return f.gestures(); }
inline ToolList    getPartList(Frame f, Tool)    { return f.tools(); }

inline HandType      getType(Hand hand)       { return whichHand(hand); }
inline int           getType(Tool tool)       { return 0; }
inline Finger::Type  getType(Finger finger)   { return finger.type(); }
inline Gesture::Type getType(Gesture gesture) { return gesture.type(); }

template <typename Part> const char* partName();

template<> inline const char* partName<Finger>()           { return "finger"; }
template<> inline const char* partName<Hand>()             { return "hand"; }
template<> inline const char* partName<Tool>()             { return "tool"; }
template<> inline const char* partName<Bone>()             { return "bone"; }
template<> inline const char* partName<SwipeGesture>()     { return "swipe"; }
template<> inline const char* partName<CircleGesture>()    { return "circle"; }
template<> inline const char* partName<KeyTapGesture>()    { return "keytap"; }
template<> inline const char* partName<ScreenTapGesture>() { return "screentap"; }

}  // leap
}  // swirly
