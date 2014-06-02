#pragma once

#include <memory>
#include <string>
#include <vector>

extern "C" {
#include "ext.h"
#include "ext_obex.h"
}

#include "leap/Leap.h"

using namespace std;
using namespace Leap;

namespace swirly {

enum HandType { LEFT_HAND, RIGHT_HAND, NO_HAND = -1 };

template <class T>
std::unique_ptr<T> make_unique(){
  return std::unique_ptr<T>(new T());
}

template <class T, class A0>
std::unique_ptr<T> make_unique(A0&& a0){
  return std::unique_ptr<T>(new T(std::forward<A0>(a0)));
}

}  // namespace swirly
