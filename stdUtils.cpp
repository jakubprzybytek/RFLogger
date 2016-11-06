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

ostream& operator<< (ostream& os, const ArgInfo& argInfo) {
    os << "[key=" << argInfo.key;
    os << ",value=" << argInfo.value;
    os << ",name=" << argInfo.name;
    os << ",description=" << argInfo.description;
    os << ",units=" << argInfo.units;
    os << "]";
    return os;
}

ostream& operator<< (ostream& os, const ArgInfoList& argInfoList) {
    os << "(";
    for (ArgInfoList::const_iterator iterator = argInfoList.begin(); iterator != argInfoList.end(); iterator++) {
	os << *iterator << ",";
    }
    os << ")";
    return os;
}
