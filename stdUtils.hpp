#include <iostream>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace SoapySDR;

ostream& operator<< (ostream& os, const vector<double>& values);

ostream& operator<< (ostream& os, const vector<string>& values);

ostream& operator<< (ostream& os, const Kwargs& kwargs);

ostream& operator<< (ostream& os, const Range& range);

ostream& operator<< (ostream& os, const RangeList& rangeList);

ostream& operator<< (ostream& os, const ArgInfoList& argInfoList);
