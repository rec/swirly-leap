#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace swirly {

enum HandType { LEFT_HAND, RIGHT_HAND, NO_HAND = -1 };
typedef std::function<void(bool, const char*, const char*)> Logger;

}  // namespace swirly
