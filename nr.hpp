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

    // exception handling

#ifndef _USENRERRORCLASS_
#define throw(message) \
{printf("ERROR: %s\n      in file %s at line %d\n", message, __FILE__, __LINE__); throw(1); }
#else
struct NRerror{
    char *message;
    char *file;
    int line;
    NRerror(char *m, char *f, int l) : message(m), file(f), line(l) {}
};
#define throw(message) throw(NRerror(message, __FILE__, __LINE__));
void NRcatch(NRerror err){
    printf("ERROR: %s\n    in file %s at line %d\n",
           err.message, err.file, err.line);
    exit(1);
}
#endif
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

        inline int size() const;

        void print();

//        Vector &zeros(int);

        ~Vector();

    };

#endif  // ifdef _USESTDVECTOR_

    template<class T>
    class Matrix{
    private:
        int m_row;  // 行
        int m_column;  //列
        T **m_data;
    public:
        Matrix();
        Matrix(int, int);
        Matrix(int, int, const T&);
        Matrix(int, int, const T*);
        Matrix(const Matrix &);
        Matrix & operator=(const Matrix&);
        using value_type=T;
        inline T* operator[](const int);
        inline int rows() const;
        inline int columns() const;
        ~Matrix();
    };
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
#ifdef _CHECKBOUNDS_
if (i<0 || i>= this->m_size){
    throw("Vector subscript out of bounds");
}
#endif
    return this->m_data[i];
}

template<class T>
nr::Vector<T>::~Vector() {
    if (this->m_data != nullptr)
        delete[] this->m_data;
    this->m_data = nullptr;  // 防止野指针
}

template<class T>
void nr::Vector<T>::print() {
    int n = this->m_size;
    if (n > 0 && this->m_data != nullptr) {
        std::cout << "[" << this->m_data[0];
        for (int i = 1; i < n; i++)
            std::cout << " " << this->m_data[i];
        std::cout << "]" << std::endl;
    }
}

template<class T>
int nr::Vector<T>::size() const {
    return this->m_size;
}

//template<class T>
//nr::Vector<T> &nr::Vector<T>::zeros(const int n) {
//    T
//    Vector<T> zeros {n, z};
//}

template<class T>
nr::Matrix<T>::Matrix() : m_row(0), m_column(0), m_data(nullptr) {}

template<class T>
nr::Matrix<T>::Matrix(int m, int n) {
    this->m_row = m;
    this->m_column = n;
    if (m > 0 && n > 0) {
        this->m_data = new T *[m];
        for(int i=0;i<m;i++)
            this->m_data[i] = new T[n];
    }
    else
        this->m_data = nullptr;
}
template<class T>
nr::Matrix<T>::Matrix(int m, int n, const T &a){
    this->m_row = m;
    this->m_column = n;
    if(m>0 && n>0){
        this->m_data = new T*[m];
        for(int i=0; i<m;i++)
            this->m_data[i] = new T[n];
    }
    else
        this->m_data = nullptr;
    if(this->m_data != nullptr){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++)
                this->m_data[i][j] = a;
        }
    }
}
#endif //NUMERICAL_RECIPES_NR_HPP
