#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

/**
 * A thread that maintains a queue of work to do and
 *    just runs through the queue in order.
 */
class WorkQueueThread {
public:
	WorkQueueThread() { Start(); }
	~WorkQueueThread() { Stop(); }

	void AddWork(std::function<void()> work);
	void Start();
	void Stop();

private:
	bool _isStopped = true;
	bool _shouldStop = false;

	std::mutex _lock;
	std::condition_variable _eventCondition;
	std::thread* _thread = nullptr;
	std::queue<std::function<void()>> _queue;

	void Run();
};
