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
	cout << Console::Green;
	if (long(hertz.value) % 100000 == 0) {
		os << hertz.value / 1000000 <<  Console::Bold << "MHz";
	} else if (long(hertz.value) % 1000 == 0) {
		os << hertz.value / 1000 << Console::Bold << "kHz";
	} else {
		os << hertz.value << Console::Bold << "Hz";
	}
	cout << Console::Reset;
	return os;
}

const string Console::Reset = "\033[0m";

const string Console::Bold = "\033[1m";

const string Console::Red = "\033[31m";
const string Console::Green = "\033[32m";
