#include <iostream>
#include <SoapySDR/Types.hpp>

using namespace std;
using namespace SoapySDR;

ostream& operator<< (ostream& os, const vector<string>& values);

ostream& operator<< (ostream& os, const Kwargs& kwargs);
