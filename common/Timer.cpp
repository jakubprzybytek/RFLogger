#include <iostream>

#include "common/Timer.hpp"
#include "common/stdUtils.hpp"

void Timer::start() {
    if (running != true) {
		cout << "Timer interval: " << interval << endl;
		running = true;
		myThread = thread(&Timer::theLoop, this);
	}
}

void Timer::stop() {
	cout << "Stopping" << endl;
    running = false;
    myThread.join();
}

void Timer::theLoop() {
	while (running == true) {
		this_thread::sleep_for(interval);
		
		{
			unique_lock<mutex> lock(feedbackMutex);
			feedback.notify_one();
			cout << "Bing!" << endl;
		}
	}
}
