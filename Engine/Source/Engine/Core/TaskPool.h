#pragma once

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Engine/Core/Task.h"

class TaskPool {
public:
    TaskPool();
    TaskPool(int threadCount);
    ~TaskPool();

    template <typename T>
    Task<T> schedule(std::function<T()> const& f);

private:
    void initializeThreads(int threadCount);
    void threadLoop();

    boost::mutex mutex;
    boost::condition condition;

    std::list<std::function<void()>> functionQueue;
    std::vector<std::shared_ptr<boost::thread>> threads;

    bool destroying;
    int activeThreadCount;
};

#include "TaskPool.inl"