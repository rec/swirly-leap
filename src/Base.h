#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace swirly {

enum HandType { LEFT_HAND, RIGHT_HAND, NO_HAND = -1 };
typedef vector<string> Representation;

template <class T>
std::unique_ptr<T> make_unique() {
  return std::unique_ptr<T>(new T());
}

template <class T, class A0>
std::unique_ptr<T> make_unique(A0&& a0) {
  return std::unique_ptr<T>(new T(std::forward<A0>(a0)));
}

}  // namespace swirly
