#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

class Locker {

private:
	mutex mtx;
	condition_variable conditionVariable;

public:
	void wait();
	void notify();
};

class Timer {

private:
	steady_clock::time_point future;
	milliseconds interval;

	bool running = false;

	thread myThread;
	Locker& locker; 

	void theLoop();

public:
	Timer(const milliseconds interval, Locker& locker) : interval(interval), locker(locker) {}

	void start();
	void stop();
};
