#include <iostream>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace SoapySDR;

ostream& operator<< (ostream& os, const Range& range);

ostream& operator<< (ostream& os, const ArgInfo& argInfo);

template <typename T>
ostream& operator<< (ostream& os, const vector<T>& values) {
	os << "[";
	for (auto& item : values) {
		os << item;
		if (&item != &values.back()) {
			os << ",";
		}
	}
	os << "]";
	return os;
}

template <typename T, typename S>
ostream& operator<< (ostream& os, const map<T, S>& myMap) {
	os << "{";
	for (auto iterator = myMap.begin(); iterator != myMap.end(); iterator++) {
		os << iterator->first << "=" << iterator->second;
		if (next(iterator) != myMap.end()) {
			os << ",";
		}
	}
	os << "}";
	return os;
}

class Hertz {

private:
	double value;

public:
	Hertz (double v) : value(v) {}
	friend ostream& operator << (ostream&, Hertz);

};
