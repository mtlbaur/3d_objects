#pragma once

#include "utl_constants.h"
#include "utl_math_vec3.h"

namespace D3::Utl::Math {
    template <typename T>
    class Mat3 {
#define T_ static_cast<T>

        using Vec3 = Vec3<T>;

      public:
        Vec3 a[3];

        Mat3() = default;
        Mat3(const Vec3& x, const Vec3& y, const Vec3& z) : a{x, y, z} {}
        Mat3(const Mat3& m) : a{m[0], m[1], m[2]} {}
        Mat3(Mat3&& m) noexcept { *this = m; }

        const Vec3& operator[](int i) const { return a[i]; }
        Vec3&       operator[](int i) { return a[i]; }

        Mat3& operator=(const Mat3& m) {
            a[0] = m[0];
            a[1] = m[1];
            a[2] = m[2];
            return *this;
        }
        Mat3& operator=(Mat3&& m) noexcept {
            *this = m;
            return *this;
        }
        bool operator==(const Mat3& v) {
            return {a[0][0] == v[0][0] && a[0][1] == v[0][1] && a[0][2] == v[0][2] &&
                    a[1][0] == v[1][0] && a[1][1] == v[1][1] && a[1][2] == v[1][2] &&
                    a[2][0] == v[2][0] && a[2][1] == v[2][1] && a[2][2] == v[2][2]};
        }
        Mat3 operator+(const Mat3& m) const {
            return {a[0] + m[0],
                    a[1] + m[1],
                    a[2] + m[2]};
        }
        Mat3& operator+=(const Mat3& m) {
            *this = *this + m;
            return *this;
        }
        Mat3 operator-(const Mat3& m) const {
            return {a[0] - m[0],
                    a[1] - m[1],
                    a[2] - m[2]};
        }
        Mat3& operator-=(const Mat3& m) {
            *this = *this - m;
            return *this;
        }
        Mat3 operator*(T s) const {
            return {a[0] * s,
                    a[1] * s,
                    a[2] * s};
        }
        Mat3& operator*=(T s) {
            *this = *this * s;
            return *this;
        }
        Mat3 operator*(const Mat3& m) const { // rows of 2nd --> cols of 1st
            return {
                {m[0][0] * a[0][0] + m[0][1] * a[1][0] + m[0][2] * a[2][0],
                 m[0][0] * a[0][1] + m[0][1] * a[1][1] + m[0][2] * a[2][1],
                 m[0][0] * a[0][2] + m[0][1] * a[1][2] + m[0][2] * a[2][2]},
                {m[1][0] * a[0][0] + m[1][1] * a[1][0] + m[1][2] * a[2][0],
                 m[1][0] * a[0][1] + m[1][1] * a[1][1] + m[1][2] * a[2][1],
                 m[1][0] * a[0][2] + m[1][1] * a[1][2] + m[1][2] * a[2][2]},
                {m[2][0] * a[0][0] + m[2][1] * a[1][0] + m[2][2] * a[2][0],
                 m[2][0] * a[0][1] + m[2][1] * a[1][1] + m[2][2] * a[2][1],
                 m[2][0] * a[0][2] + m[2][1] * a[1][2] + m[2][2] * a[2][2]}
            };
        }
        Mat3& operator*=(const Mat3& m) {
            *this = *this * m;
            return *this;
        }
        Vec3 operator*(const Vec3& v) const { // rows of vector 2nd --> cols of matrix 1st
            return {v[0] * a[0][0] + v[1] * a[1][0] + v[2] * a[2][0],
                    v[0] * a[0][1] + v[1] * a[1][1] + v[2] * a[2][1],
                    v[0] * a[0][2] + v[1] * a[1][2] + v[2] * a[2][2]};
        }
        Mat3 transpose() {
            return {
                {a[0][0], a[1][0], a[2][0]},
                {a[0][1], a[1][1], a[2][1]},
                {a[0][2], a[1][2], a[2][2]}
            };
        }
        Mat3& transposed() {
            *this = transpose();
            return *this;
        }
        // source: https://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/threeD/index.htm
        T determinant() {
            return a[0][0] * a[1][1] * a[2][2] + a[1][0] * a[2][1] * a[0][2] +
                   a[2][0] * a[0][1] * a[1][2] - a[0][0] * a[2][1] * a[1][2] -
                   a[1][0] * a[0][1] * a[2][2] - a[2][0] * a[1][1] * a[0][2];
        }
        // source: https://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/threeD/index.htm
        Mat3 inverse() {
            T scale = determinant();

            return {
                {(a[1][1] * a[2][2] - a[2][1] * a[1][2]) / scale,
                 (a[2][1] * a[0][2] - a[0][1] * a[2][2]) / scale,
                 (a[0][1] * a[1][2] - a[1][1] * a[0][2]) / scale},
                {(a[2][0] * a[1][2] - a[1][0] * a[2][2]) / scale,
                 (a[0][0] * a[2][2] - a[2][0] * a[0][2]) / scale,
                 (a[1][0] * a[0][2] - a[0][0] * a[1][2]) / scale},
                {(a[1][0] * a[2][1] - a[2][0] * a[1][1]) / scale,
                 (a[2][0] * a[0][1] - a[0][0] * a[2][1]) / scale,
                 (a[0][0] * a[1][1] - a[1][0] * a[0][1]) / scale}
            };
        }
        Mat3& inversed() {
            *this = inverse();
            return *this;
        }
        static Mat3 zero() {
            return {
                {T_(0), T_(0), T_(0)},
                {T_(0), T_(0), T_(0)},
                {T_(0), T_(0), T_(0)}
            };
        }
        static Mat3 identity() {
            return {
                {T_(1), T_(0), T_(0)},
                {T_(0), T_(1), T_(0)},
                {T_(0), T_(0), T_(1)}
            };
        }
        static Mat3 scale(T x, T y, T z) {
            return {
                {x,     T_(0), T_(0)},
                {T_(0), y,     T_(0)},
                {T_(0), T_(0), z    }
            };
        }
        static Mat3 scale(const Vec3& v) {
            return scale(v[0], v[1], v[2]);
        }
        static Mat3 rotate(const Vec3& x, const Vec3& y, const Vec3& z) { // column major
            return {
                {x[0], y[0], z[0]},
                {x[1], y[1], z[1]},
                {x[2], y[2], z[2]}
            };
        }
        template <class Archive>
        void serialize(Archive& archive, const unsigned version) {
            archive& a[0];
            archive& a[1];
            archive& a[2];
            archive& a[3];
        }
#undef T_
    };
} // namespace D3::Utl::Math