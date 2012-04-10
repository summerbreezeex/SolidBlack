#pragma once

template <typename T>
Task<T> TaskPool::schedule(const typename Task<T>::Function& function) {
    return queueTask<T>([function](TaskData<T>* data) {
        data->result = function();
        data->done = true;
    });
}

template <typename T>
Task<T> TaskPool::queueTask(const std::function<void(TaskData<T>*)>& f) {
    boost::mutex::scoped_lock lock(mutex);

    Task<T> task;
    std::shared_ptr<TaskData<T>> data(task.data);
    data->valid = true;

    functionQueue.push_back([data, f] { f(data.get()); });

    condition.notify_all();
    return task;
}