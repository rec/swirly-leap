#pragma once

#include "Base.h"

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
class MaxObject {
  public:
    MaxObject(MaxStruct *maxStruct, t_symbol *s, long argc, t_atom *argv);
    ~MaxObject();

    void bang();
    void run();
    void stop();

  private:
    void log(bool error, const char* format, const char* value);
    void log1(bool error, const char* value) { log(error, "%s", value); }

    MaxStruct *const maxStruct_;
    t_object* object_;

    Logger logger_;
    unique_ptr<LeapMotion> leap_;
    void* outlet_;
};

void registerMaxObject();

}  // namespace leap
}  // namespace swirly
