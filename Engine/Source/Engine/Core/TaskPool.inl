#pragma once

template <typename T>
Task<T> TaskPool::schedule(std::function<T()> const& f) {
    boost::mutex::scoped_lock lock(mutex);

    Task<T> task;
    std::shared_ptr<TaskData<T>> data(task.data);
    data->valid = true;

    functionQueue.push_back([data, f] {
        data->result = f();
        data->done = true;
    });

    condition.notify_all();
    return task;
}