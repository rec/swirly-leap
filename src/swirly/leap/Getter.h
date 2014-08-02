#pragma once

#include <leap/Leap.h>

#include <swirly/leap/LeapUtil.h>

using namespace Leap;

namespace swirly {
namespace leap {

inline HandList    getList(Frame f, Hand)    { return f.hands(); }
inline FingerList  getList(Frame f, Finger)  { return f.fingers(); }
inline GestureList getList(Frame f, Gesture) { return f.gestures(); }
inline ToolList    getList(Frame f, Tool)    { return f.tools(); }

inline HandType      getType(Hand hand)       { return whichHand(hand); }
inline int           getType(Tool tool)       { return 0; }
inline Finger::Type  getType(Finger finger)   { return finger.type(); }
inline Gesture::Type getType(Gesture gesture) { return gesture.type(); }

template <typename Data>
const char* humanName();

template<> inline const char* humanName<Finger>()           { return "finger"; }
template<> inline const char* humanName<Hand>()             { return "hand"; }
template<> inline const char* humanName<Tool>()             { return "tool"; }
template<> inline const char* humanName<Bone>()             { return "bone"; }
template<> inline const char* humanName<SwipeGesture>()     { return "swipe"; }
template<> inline const char* humanName<CircleGesture>()    { return "circle"; }
template<> inline const char* humanName<KeyTapGesture>()    { return "keytap"; }
template<> inline const char* humanName<ScreenTapGesture>() { return "screentap"; }

}  // humanNamespace leap
}  // humanNamespace swirly
