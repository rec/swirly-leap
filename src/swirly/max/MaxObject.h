#pragma once

#include <swirly/base/Logger.h>
#include <swirly/max/Max.h>

namespace swirly {
namespace leap {

// This is the structure that Max will initialize.

struct LeapMotion;
class MaxObject;

static const int MAX_PROPERTIES = 64;

struct MaxStruct {
    t_object object_;
    MaxObject *maxObject_;
    t_symbol hands_[MAX_PROPERTIES];
    long numHands_;
    void* clock_;
};

// This is the C++ class contained in this structure.
class MaxObject : public Logger{
  public:
    MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv);
    ~MaxObject();

    void bang();
    void setRunning(bool isRunning);
    LeapMotion& leap() { return *leap_; }
    void startClock();
    function <void()> clockCallback;

  private:
    void log(string const& message) const override;
    void err(string const& message) const override;

    MaxStruct *const maxStruct_;
    t_object* object_;

    unique_ptr<LeapMotion> leap_;
    void* outlet_;
};

void registerMaxObject();

}  // namespace leap
}  // namespace swirly
