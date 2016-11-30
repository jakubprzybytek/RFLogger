#include <string>
#include <ctime>

#include "Timestamp.hpp"

char mbstr[100];

Timestamp Timestamp::NOW() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return Timestamp(tv);
}

string Timestamp::formatTime() {
	string result;

	int millisec = tv.tv_usec / 1000;
	strftime(mbstr, sizeof(mbstr), "%T", localtime(&tv.tv_sec));

	return string(mbstr) + "." + to_string(millisec);
}
