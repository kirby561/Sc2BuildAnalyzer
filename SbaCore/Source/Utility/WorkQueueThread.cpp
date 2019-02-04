#include "WorkQueueThread.h"

using std::thread;
using std::mutex;
using std::unique_lock;
using std::function;

void WorkQueueThread::AddWork(function<void()> work) {
	unique_lock<mutex> lock(_lock);
	_queue.push(work);
	_eventCondition.notify_all();
}

void WorkQueueThread::Start() {
	unique_lock<mutex> lock(_lock);

	if (_isStopped) {
		_thread = new thread([this]() { this->Run(); });

		// Wait for it to start
		while (_isStopped) {
			_eventCondition.wait(lock);
		}
	}
}

void WorkQueueThread::Stop() {
	unique_lock<mutex> lock(_lock);

	if (!_isStopped) {
		_shouldStop = true;
		
		while (!_isStopped) {
			_eventCondition.wait(lock);
		}

		_thread->join();
		delete _thread;
		_thread = nullptr;
	}
}

void WorkQueueThread::Run() {
	{ // Start the thread and notify
		unique_lock<mutex> lock(_lock);
		_isStopped = false;
		_shouldStop = false;
		_eventCondition.notify_all();
	}

	{ // Run the thread until asked to stop
		unique_lock<mutex> lock(_lock);
		while (!_shouldStop) {
			if (!_queue.empty()) {
				function<void()> nextItem = _queue.front();
				_queue.pop();
				nextItem();
			} else {
				_eventCondition.wait(lock);
			}
		}

		// We're stopping.  First drain the queue
		while (!_queue.empty()) {
			function<void()> nextItem = _queue.front();
			_queue.pop();
			nextItem();
		}

		// Stop
		_isStopped = true;
		_shouldStop = false;
		_eventCondition.notify_all();
	}
}
