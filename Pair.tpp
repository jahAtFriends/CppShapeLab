#ifndef PAIR_TPP
#define PAIR_TPP

#include "Pair.hpp"

template <typename S, typename T>
Pair<S,T>::Pair(const S& first, const T& second) 
    : m_first(first), m_second(second)
{
};

template <typename S, typename T>
const S& Pair<S, T>::first() const {
    return m_first;
}

template <typename S, typename T>
const T& Pair<S,T>::second() const {
    return m_second;
}

template <typename S, typename T>
Pair<S, T> Pair<S,T>::transpose() const {
    return Pair<T, S>{m_second, m_first};
}

#endif