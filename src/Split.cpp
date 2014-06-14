#include <sstream>

#include "Split.h"

namespace swirly {

vector<string> split(string const& s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

StringValues splitEquals(string const& s, char delim) {
    StringValues result;
    auto pos = s.find('=');
    if (pos && pos != string::npos && pos != s.size() - 1) {
        result.first = s.substr(0, pos);
        result.second = split(s.substr(pos + 1), delim);
    }
    return result;
}

}
