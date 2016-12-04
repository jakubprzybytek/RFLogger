#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

class Timer {

private:
	milliseconds interval;
	bool running = false;

	thread myThread;

	mutex& feedbackMutex; 
	condition_variable& feedback; 

	void theLoop();
	
public:
	Timer(const milliseconds interval, mutex& feedbackMutex, condition_variable& feedback)
		: interval(interval), feedbackMutex(feedbackMutex), feedback(feedback) {}

	void start();
	void stop();
};
