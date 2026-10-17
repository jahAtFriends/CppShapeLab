#ifndef PAIR_HPP
#define PAIR_HPP

template <typename S, typename T>
class Pair {
private:
    S m_first;
    T m_second;

public:
    // Constructor
    Pair(const S& first, const T& second);
    
    const S& first() const;
    const T& second() const;

    Pair<T, S> transpose() const;
};

#include "Pair.tpp"

#endif