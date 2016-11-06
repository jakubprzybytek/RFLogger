#include "stdUtils.hpp"

ostream& operator<< (ostream& os, const Kwargs& kwargs) {
    os << "[";
    for (Kwargs::const_iterator iterator = kwargs.begin(); iterator != kwargs.end(); iterator++) {
	os << iterator->first << "=" << iterator->second << ",";
    }
    os << "]";
    return os;
}
