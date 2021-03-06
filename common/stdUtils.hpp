#include <iostream>
#include <chrono>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace std::chrono;
using namespace SoapySDR;

milliseconds sToDuration(const string& input);

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

ostream& operator << (ostream& os, const milliseconds&);

class Hertz {

private:
	double value;

public:
	Hertz (double v) : value(v) {}
	friend ostream& operator << (ostream&, const Hertz&);
};

class Console {
public:
	static const string Reset;

	static const string Bold;

	static const string Red;
	static const string Green;
	static const string Yellow;
	static const string Blue;
	static const string Magenta;
	static const string Cyan;
	static const string White;
};
