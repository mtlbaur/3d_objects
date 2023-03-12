#pragma once

#include <string>

#include "utl_print.h"

template <typename T>
inline constexpr T TOLERANCE = static_cast<T>(0.0000001);

#define EQUAL_VEC(a, b, size)             \
    [&]() {                               \
        for (auto i = 0; i < size; i++) { \
            BOOST_TEST(a[i] == b[i]);     \
        }                                 \
    }();
#define EQUAL_VEC2(a, b) EQUAL_VEC(a, b, 2)
#define EQUAL_VEC3(a, b) EQUAL_VEC(a, b, 3)
#define EQUAL_VEC4(a, b) EQUAL_VEC(a, b, 4)

#define EQUAL_MAT(a, b, imax, jmax)             \
    [&]() {                                     \
        for (int i = 0; i < imax; i++) {        \
            for (int j = 0; j < jmax; j++) {    \
                BOOST_TEST(a[i][j] == b[i][j]); \
            }                                   \
        }                                       \
    }();
#define EQUAL_MAT2(a, b) EQUAL_MAT(a, b, 2, 2)
#define EQUAL_MAT3(a, b) EQUAL_MAT(a, b, 3, 3)
#define EQUAL_MAT4(a, b) EQUAL_MAT(a, b, 4, 4)

#define EQUAL_QUAT(a, b)    \
    BOOST_TEST(a.x == b.x); \
    BOOST_TEST(a.y == b.y); \
    BOOST_TEST(a.z == b.z); \
    BOOST_TEST(a.w == b.w);

template <typename A, typename B>
B copyVec(A a, int size) {
    B b;

    for (int i = 0; i < size; i++) {
        b[i] = a[i];
    }

    return b;
}

template <typename A, typename B>
B copyVec2(A a) { return copyVec<A, B>(a, 2); }

template <typename A, typename B>
B copyVec3(A a) { return copyVec<A, B>(a, 3); }

template <typename A, typename B>
B copyVec4(A a) { return copyVec<A, B>(a, 4); }

template <typename A, typename B>
B copyMat(A a, int imax, int jmax) {
    B b;

    for (int i = 0; i < imax; i++) {
        for (int j = 0; j < jmax; j++) {
            b[i][j] = a[i][j];
        }
    }

    return b;
}

template <typename A, typename B>
B copyMat2(A a) { return copyMat<A, B>(a, 2, 2); }

template <typename A, typename B>
B copyMat3(A a) { return copyMat<A, B>(a, 3, 3); }

template <typename A, typename B>
B copyMat4(A a) { return copyMat<A, B>(a, 4, 4); }

template <typename A, typename B>
B copyQuat(A a) { return B(a.w, a.x, a.y, a.z); }

template <typename V>
void printVec(V v, int size) {
    std::string s("[");

    for (int i = 0; i < size - 1; i++) {
        s += std::to_string(v[i]) + ", ";
    }

    s += std::to_string(v[size - 1]) + "]";

    D3::Utl::println(s);
}

template <typename V>
void printVec2(V v) { printVec(v, 2); }

template <typename V>
void printVec3(V v) { printVec(v, 3); }

template <typename V>
void printVec4(V v) { printVec(v, 4); }

template <typename M>
void printMat(M m, int imax, int jmax) {
    for (int i = 0; i < imax; i++) {
        for (int j = 0; j < jmax; j++) {
            D3::Utl::print(m[i][j], ' ');
        }
        D3::Utl::println();
    }
    D3::Utl::println();
}

template <typename M>
void printMat3(M m) { printMat(m, 3, 3); }

template <typename M>
void printMat4(M m) { printMat(m, 4, 4); }

template <typename Q>
void printQuat(Q q) { D3::Utl::println('(', q.x, ", ", q.y, ", ", q.z, ", ", q.w, ')'); }