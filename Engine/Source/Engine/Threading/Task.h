#pragma once

#include "Engine/StlCommon.h"

template <typename T = bool>
struct TaskData {
    TaskData();

    volatile bool done;
    volatile bool valid;
    T result;
};

template <typename T = bool>
class Task {
    friend class TaskPool;
public:
    typedef std::function<T()> Function;

    Task();

    T& getResult();

    void waitUntilDone();

    bool isDone();

private:
    std::shared_ptr<TaskData<T>> data;
};

#include "Task.inl"