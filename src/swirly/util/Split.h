#pragma once

#include <swirly/base/Base.h>

namespace swirly {

typedef pair<string, vector<string>> StringValues;

vector<string> split(string const& s, char delim);
StringValues splitEquals(string const& s, char delim);

}
