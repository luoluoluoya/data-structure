//
// Created by 张锐 on 2020/11/25.
//

#include "stack.h"

template<typename T>
void stack<T>::push(const T &e) { vector<T>::insert(vector<T>::size(), e); }

template<typename T>
T stack<T>::pop() { return vector<T>::remove(vector<T>::size() - 1); }

template<typename T>
T &stack<T>::top() { return *vector<T>::at(vector<T>::size() - 1); }
