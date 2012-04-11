#pragma once

template <class T>
T* Actor::findComponentOfType() {
    return dynamic_cast<T*>(findComponentOfType(T::typeName));
}