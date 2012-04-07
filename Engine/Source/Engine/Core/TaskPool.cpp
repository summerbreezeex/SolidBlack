#include "TaskPool.h"

TaskPool::TaskPool() :
        destroying(false),
        activeThreadCount(0) {
    initializeThreads(std::max((int)boost::thread::hardware_concurrency() - 1, 1));
}

TaskPool::TaskPool(int threadCount) :
        destroying(false),
        activeThreadCount(0) {
    initializeThreads(threadCount);
}

TaskPool::~TaskPool() {
    boost::mutex::scoped_lock lock(mutex);

    destroying = true;
    condition.notify_all();
    while (activeThreadCount) {
        condition.wait(lock);
    }
}

void TaskPool::initializeThreads(int threadCount) {
    for (int i = 0; i < threadCount; ++i) {
        threads.push_back(std::make_shared<boost::thread>([this] { this->threadLoop(); }));
    }
}

void TaskPool::threadLoop() {
    boost::mutex::scoped_lock lock(mutex);
    ++activeThreadCount;

    while (true) {
        while (functionQueue.size() == 0 && !destroying) {
            condition.wait(lock);
        }

        if (functionQueue.size() == 0 && destroying) {
            --activeThreadCount;
            condition.notify_all();
            return;
        }

        auto f = functionQueue.front();
        functionQueue.pop_front();

        lock.unlock();
        f();
        lock.lock();
    }
}