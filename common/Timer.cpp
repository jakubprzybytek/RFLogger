#include "common/Timer.hpp"
#include "common/stdUtils.hpp"

void Locker::wait() {
	unique_lock<mutex> lock(mtx);
	conditionVariable.wait(lock);
}

void Locker::notify() {
	unique_lock<mutex> lock(mtx);
	conditionVariable.notify_one();
}

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
	future = steady_clock::now() + interval;
	while (running == true) {
		this_thread::sleep_until(future);
		locker.notify();
		future = future + interval;
	}
}
