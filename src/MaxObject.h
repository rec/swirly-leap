#pragma once

#include "Logger.h"

namespace swirly {
namespace leap {

// This is the structure that Max will initialize.

struct LeapMotion;
class MaxObject;

struct MaxStruct {
    t_object object_;
    MaxObject *maxObject_;
};

// This is the C++ class contained in this structure.
class MaxObject : public Logger{
  public:
    MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv);
    ~MaxObject();

    void bang();
    void setRunning(bool isRunning);

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
