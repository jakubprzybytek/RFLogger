#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Timer {

private:
	milliseconds interval;
	thread myThread;
	bool running = false;

	void theLoop();
	
public:
	Timer(const milliseconds interval) : interval(interval) {}

	void start();
	void stop();
};
