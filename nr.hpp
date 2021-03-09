//
// Created by tang xiangong on 2021/3/9.
//

#ifndef NUMERICAL_RECIPES_NR_HPP
#define NUMERICAL_RECIPES_NR_HPP
// all the system #include's we'll ever need
#include <fstream>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fcntl.h>
#include <cstring>
#include <cctype>


// macro-like inline functions
namespace nr {
    template<class T>
    inline T sqr(T);

    template<class T>
    inline const T &max(const T &, const T &);

    inline float max(const double &, const float &);

    inline float max(const float &, const double &);

    template<class T>
    inline const T &min(const T &, const T &);

    inline float min(const float &, const double &);

    inline float min(const double &, const float &);

    template<class T>
    inline T &sign(const T &, const T &);

    inline float sign(const float &, const double &);

    inline float sign(const double &, const float &);

    template<class T>
    inline void swap(T &, T &);

#ifdef _USESTDVECTOR_
#define Vector vector
#else

    template<class T>
    class Vector {
    private:
        int m_size{};  // size of array.
        T *m_data;
    public:
        Vector();

        explicit Vector(int);

        Vector(int, const T &);

        Vector(int, const T *);

        Vector(const Vector &);

        Vector &operator=(const Vector &);

        inline T &operator[](int);

        ~Vector();

    };

#endif
}

template<class T>
T nr::sqr(const T a) { return a * a; }

template<class T>
const T &nr::max(const T &a, const T &b) {
    return b > a ? (b) : (a);
}

float nr::max(const double &a, const float &b) {
    return b > a ? (b) : float(a);
}

float nr::max(const float &a, const double &b) {
    return b > a ? float(b) : (a);
}

template<class T>
const T &nr::min(const T &a, const T &b) {
    return a < b ? (a) : (b);
}

float nr::min(const float &a, const double &b) {
    return a < b ? (a) : float(b);
}

float nr::min(const double &a, const float &b) {
    return a < b ? float(a) : (b);
}

template<class T>
T &nr::sign(const T &a, const T &b) {
    return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

float nr::sign(const double &a, const float &b) {
    return (float) (b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a));
}

float nr::sign(const float &a, const double &b) {
    return b >= 0 ? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}

template<class T>
void nr::swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
nr::Vector<T>::Vector() : m_size(0), m_data(nullptr) {}

template<class T>
nr::Vector<T>::Vector(int n) {
    this->m_size = n;
    if (n > 0)
        this->m_data = new T[n];
    else
        this->m_data = nullptr;
}

template<class T>
nr::Vector<T>::Vector(int n, const T &a) {
    this->m_size = n;
    if (n > 0) {
        this->m_data = new T[n];
        for (int i = 0; i < n; i++)
            this->m_data[i] = a;
    } else
        this->m_data = nullptr;
}

template<class T>
nr::Vector<T>::Vector(int n, const T *a) {
    this->m_size = n;
    if (n > 0) {
        this->m_data = new T[n];
        for (int i = 0; i < n; i++)
            this->m_data[i] = a[i];
    } else
        this->m_data = nullptr;
}

template<class T>
nr::Vector<T>::Vector(const Vector<T> &rhs) {
    this->m_size = rhs.m_size;
    if (rhs.m_size > 0) {
        this->m_data = new T[this->m_size];
        for (int i = 0; i < this->m_size; i++)
            this->m_data[i] = rhs.m_data[i];
    } else
        this->m_data = nullptr;
}

template<class T>
nr::Vector<T> &nr::Vector<T>::operator=(const Vector<T> &rhs) {
    if (this != &rhs) {
        if (this->m_size != rhs.m_size) {
            if (this->m_data != nullptr) delete[] this->m_data;
            this->m_size = rhs.m_size;
            this->m_data = this->m_size > 0 ? new T[this->m_size] : nullptr;
        }
        for (int i = 0; i < this->m_size; i++)
            this->m_data[i] = rhs[i];
    }
    return *this;
}

template<class T>
inline T &nr::Vector<T>::operator[](const int i) {
// TODO error: out of bounds
    return this->m_data[i];
}

template<class T>
nr::Vector<T>::~Vector() {
    if (this->m_data != nullptr)
        delete[] this->m_data;
    this->m_data = nullptr;  // 防止野指针
}

#endif //NUMERICAL_RECIPES_NR_HPP
