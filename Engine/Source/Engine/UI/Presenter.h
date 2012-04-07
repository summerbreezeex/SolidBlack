#pragma once

template <typename T>
class Presenter {
public:
    Presenter();
    virtual ~Presenter() { }

    T* getView();
    void setView(T* view);

private:
    T* view;
};

#include "Presenter.inl"