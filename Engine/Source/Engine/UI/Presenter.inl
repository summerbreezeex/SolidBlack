#pragma once

template <typename T>
Presenter<T>::Presenter() :
        view(nullptr) {
}

template <typename T>
T* Presenter<T>::getView() {
    return view;
}

template <typename T>
void Presenter<T>::setView(T* view) {
    this->view = view;
}