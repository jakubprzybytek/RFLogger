#pragma once

#include <sys/time.h>

using namespace std;

class Timestamp {

private:

public:
	struct timeval tv;

	static Timestamp NOW();

	Timestamp() {}
	Timestamp(timeval tv) : tv(tv) {}

	string formatTime() const;
	long int secs() const;
};
