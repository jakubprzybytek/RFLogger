#include "stdUtils.hpp"

ostream& operator<< (ostream& os, const vector<string>& values) {
    os << "[";
    for (vector<string>::const_iterator iterator = values.begin(); iterator != values.end(); iterator++) {
	os << *iterator << ",";
    }
    os << "]";
    return os;
}

ostream& operator<< (ostream& os, const Kwargs& kwargs) {
    os << "[";
    for (Kwargs::const_iterator iterator = kwargs.begin(); iterator != kwargs.end(); iterator++) {
	os << iterator->first << "=" << iterator->second << ",";
    }
    os << "]";
    return os;
}
