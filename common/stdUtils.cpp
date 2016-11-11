#include "stdUtils.hpp"

ostream& operator << (ostream& os, const Range& range) {
    os << "(" << range.minimum() << ";" << range.maximum() << ")";
    return os;
}

string typeNames[] = {"BOOL", "INT", "FLOAT", "STRING"};

ostream& operator << (ostream& os, const ArgInfo& argInfo) {
    os << "{key=" << argInfo.key;
    os << ",value=" << argInfo.value;
    os << ",name=" << argInfo.name;
    os << ",description=" << argInfo.description;
    os << ",units=" << argInfo.units;
    os << ",type=" << typeNames[argInfo.type];
    os << ",range=" << argInfo.range;
    os << ",options=" << argInfo.options;
    os << ",optionNames=" << argInfo.optionNames;
    os << "}";
    return os;
}

ostream& operator << (ostream& os, Hertz hertz) {
    if (long(hertz.value) % 100000 == 0) {
	os << hertz.value / 1000000 <<  "MHz";
    } else if (long(hertz.value) % 1000 == 0) {
	os << hertz.value / 1000 << "kHz";
    } else {
	os << hertz.value << "Hz";
    }
    return os;
}
