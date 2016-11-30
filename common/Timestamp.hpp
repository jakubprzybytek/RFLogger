#include <sys/time.h>

using namespace std;

class Timestamp {

private:
	struct timeval tv;

public:
	static Timestamp NOW();

	Timestamp(timeval tv) : tv(tv) {}

	string formatTime();
};
