#pragma once

#include "Engine/StlCommon.h"

template <typename T>
struct TaskData {
    TaskData();

    volatile bool done;
    volatile bool valid;
    T result;
};

template <typename T>
class Task {
    friend class TaskPool;
public:
    Task();

    T& getResult();

    void waitUntilDone();

    bool isDone();

private:
    std::shared_ptr<TaskData<T>> data;
};

#include "Task.inl"