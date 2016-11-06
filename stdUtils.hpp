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

ostream& operator<< (ostream& os, const Kwargs& kwargs);
