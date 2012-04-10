#pragma once

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Engine/Threading/Task.h"

typedef std::function<void()> Action;

class TaskPool {
public:
    TaskPool();
    TaskPool(int threadCount);
    ~TaskPool();

    Task<> schedule(const Action& action);

    template <typename T>
    Task<T> schedule(const typename Task<T>::Function& function);

private:
    template <typename T>
    Task<T> queueTask(const std::function<void(TaskData<T>*)>& f);

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