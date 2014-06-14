#pragma once

#include "Base.h"

namespace swirly {

typedef pair<string, vector<string>> StringValues;

vector<string> split(string const& s, char delim);
StringValues splitEquals(string const& s, char delim);

}
