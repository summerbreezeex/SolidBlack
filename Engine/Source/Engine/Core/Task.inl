#pragma once

template <typename T>
TaskData<T>::TaskData() :
        done(false),
        valid(false) {
}

template <typename T>
Task<T>::Task() :
        data(new TaskData<T>()) {
}

template <typename T>
T& Task<T>::getResult() {
    assert(data->valid);
    while (!data->done) { }

    return data->result;
}

template <typename T>
void Task<T>::waitUntilDone() {
    while (!isDone()) { }
}

template <typename T>
bool Task<T>::isDone() {
    return !data->valid ? true : data->done;
}