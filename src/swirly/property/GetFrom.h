#pragma once

#include <leap/Leap.h>

#include <swirly/base/Base.h>

using namespace Leap;

namespace swirly {
namespace leap {

inline FingerList  getList(Frame f, Finger)  { return f.fingers(); }
inline GestureList getList(Frame f, Gesture) { return f.gestures(); }
inline HandList    getList(Frame f, Hand)    { return f.hands(); }
inline ToolList    getList(Frame f, Tool)    { return f.tools(); }

}  // namespace leap
}  // namespace swirly
