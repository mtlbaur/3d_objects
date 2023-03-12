#pragma once

#include "utl_constants.h"
#include "utl_math_vec3.h"
#include "utl_math_vec4.h"

namespace D3::Utl::Math {
    template <typename T>
    class Mat4 {
#define T_ static_cast<T>

        using Vec3 = Vec3<T>;
        using Vec4 = Vec4<T>;

      public:
        Vec4 a[4];

        Mat4() = default;
        Mat4(const Vec4& x, const Vec4& y, const Vec4& z, const Vec4& w) : a{x, y, z, w} {}
        Mat4(const Mat4& m) : a{m[0], m[1], m[2], m[3]} {}
        Mat4(Mat4&& m) noexcept { *this = m; }

        const Vec4& operator[](int i) const { return a[i]; }
        Vec4&       operator[](int i) { return a[i]; }

        Mat4& operator=(const Mat4& m) {
            a[0] = m[0];
            a[1] = m[1];
            a[2] = m[2];
            a[3] = m[3];
            return *this;
        }
        Mat4& operator=(Mat4&& m) noexcept {
            *this = m;
            return *this;
        }
        bool operator==(const Mat4& v) {
            return {a[0][0] == v[0][0] && a[0][1] == v[0][1] && a[0][2] == v[0][2] && a[0][3] == v[0][3] &&
                    a[1][0] == v[1][0] && a[1][1] == v[1][1] && a[1][2] == v[1][2] && a[1][3] == v[1][3] &&
                    a[2][0] == v[2][0] && a[2][1] == v[2][1] && a[2][2] == v[2][2] && a[2][3] == v[2][3] &&
                    a[3][0] == v[3][0] && a[3][1] == v[3][1] && a[3][2] == v[3][2] && a[3][3] == v[3][3]};
        }
        Mat4 operator+(const Mat4& m) const {
            return {a[0] + m[0],
                    a[1] + m[1],
                    a[2] + m[2],
                    a[3] + m[3]};
        }
        Mat4& operator+=(const Mat4& m) {
            *this = *this + m;
            return *this;
        }
        Mat4 operator-(const Mat4& m) const {
            return {a[0] - m[0],
                    a[1] - m[1],
                    a[2] - m[2],
                    a[3] - m[3]};
        }
        Mat4& operator-=(const Mat4& m) {
            *this = *this - m;
            return *this;
        }
        Mat4 operator*(T s) const {
            return {a[0] * s,
                    a[1] * s,
                    a[2] * s,
                    a[3] * s};
        }
        Mat4& operator*=(T s) {
            *this = *this * s;
            return *this;
        }
        Mat4 operator*(const Mat4& m) const { // rows of 2nd --> cols of 1st
            return {
                {m[0][0] * a[0][0] + m[0][1] * a[1][0] + m[0][2] * a[2][0] + m[0][3] * a[3][0],
                 m[0][0] * a[0][1] + m[0][1] * a[1][1] + m[0][2] * a[2][1] + m[0][3] * a[3][1],
                 m[0][0] * a[0][2] + m[0][1] * a[1][2] + m[0][2] * a[2][2] + m[0][3] * a[3][2],
                 m[0][0] * a[0][3] + m[0][1] * a[1][3] + m[0][2] * a[2][3] + m[0][3] * a[3][3]},

                {m[1][0] * a[0][0] + m[1][1] * a[1][0] + m[1][2] * a[2][0] + m[1][3] * a[3][0],
                 m[1][0] * a[0][1] + m[1][1] * a[1][1] + m[1][2] * a[2][1] + m[1][3] * a[3][1],
                 m[1][0] * a[0][2] + m[1][1] * a[1][2] + m[1][2] * a[2][2] + m[1][3] * a[3][2],
                 m[1][0] * a[0][3] + m[1][1] * a[1][3] + m[1][2] * a[2][3] + m[1][3] * a[3][3]},

                {m[2][0] * a[0][0] + m[2][1] * a[1][0] + m[2][2] * a[2][0] + m[2][3] * a[3][0],
                 m[2][0] * a[0][1] + m[2][1] * a[1][1] + m[2][2] * a[2][1] + m[2][3] * a[3][1],
                 m[2][0] * a[0][2] + m[2][1] * a[1][2] + m[2][2] * a[2][2] + m[2][3] * a[3][2],
                 m[2][0] * a[0][3] + m[2][1] * a[1][3] + m[2][2] * a[2][3] + m[2][3] * a[3][3]},

                {m[3][0] * a[0][0] + m[3][1] * a[1][0] + m[3][2] * a[2][0] + m[3][3] * a[3][0],
                 m[3][0] * a[0][1] + m[3][1] * a[1][1] + m[3][2] * a[2][1] + m[3][3] * a[3][1],
                 m[3][0] * a[0][2] + m[3][1] * a[1][2] + m[3][2] * a[2][2] + m[3][3] * a[3][2],
                 m[3][0] * a[0][3] + m[3][1] * a[1][3] + m[3][2] * a[2][3] + m[3][3] * a[3][3]}
            };
        }
        Mat4& operator*=(const Mat4& m) {
            *this = *this * m;
            return *this;
        }
        Vec4 operator*(const Vec4& v) const { // rows of vector 2nd --> cols of matrix 1st
            return {v[0] * a[0][0] + v[1] * a[1][0] + v[2] * a[2][0] + v[3] * a[3][0],
                    v[0] * a[0][1] + v[1] * a[1][1] + v[2] * a[2][1] + v[3] * a[3][1],
                    v[0] * a[0][2] + v[1] * a[1][2] + v[2] * a[2][2] + v[3] * a[3][2],
                    v[0] * a[0][3] + v[1] * a[1][3] + v[2] * a[2][3] + v[3] * a[3][3]};
        }
        Mat4 transpose() {
            return {
                {a[0][0], a[1][0], a[2][0], a[3][0]},
                {a[0][1], a[1][1], a[2][1], a[3][1]},
                {a[0][2], a[1][2], a[2][2], a[3][2]},
                {a[0][3], a[1][3], a[2][3], a[3][3]}
            };
        }
        Mat4& transposed() {
            *this = transpose();
            return *this;
        }
        // source: https://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
        T determinant() {
            // clang-format off
            return a[3][0]*a[2][1]*a[1][2]*a[0][3] - a[2][0]*a[3][1]*a[1][2]*a[0][3] - a[3][0]*a[1][1]*a[2][2]*a[0][3] + a[1][0]*a[3][1]*a[2][2]*a[0][3]+
                   a[2][0]*a[1][1]*a[3][2]*a[0][3] - a[1][0]*a[2][1]*a[3][2]*a[0][3] - a[3][0]*a[2][1]*a[0][2]*a[1][3] + a[2][0]*a[3][1]*a[0][2]*a[1][3]+
                   a[3][0]*a[0][1]*a[2][2]*a[1][3] - a[0][0]*a[3][1]*a[2][2]*a[1][3] - a[2][0]*a[0][1]*a[3][2]*a[1][3] + a[0][0]*a[2][1]*a[3][2]*a[1][3]+
                   a[3][0]*a[1][1]*a[0][2]*a[2][3] - a[1][0]*a[3][1]*a[0][2]*a[2][3] - a[3][0]*a[0][1]*a[1][2]*a[2][3] + a[0][0]*a[3][1]*a[1][2]*a[2][3]+
                   a[1][0]*a[0][1]*a[3][2]*a[2][3] - a[0][0]*a[1][1]*a[3][2]*a[2][3] - a[2][0]*a[1][1]*a[0][2]*a[3][3] + a[1][0]*a[2][1]*a[0][2]*a[3][3]+
                   a[2][0]*a[0][1]*a[1][2]*a[3][3] - a[0][0]*a[2][1]*a[1][2]*a[3][3] - a[1][0]*a[0][1]*a[2][2]*a[3][3] + a[0][0]*a[1][1]*a[2][2]*a[3][3];
            // clang-format on
        }
        // source: https://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
        Mat4 inverse() {
            // clang-format off
            T scale = determinant();

            return Mat4{
                {(a[2][1]*a[3][2]*a[1][3] - a[3][1]*a[2][2]*a[1][3] + a[3][1]*a[1][2]*a[2][3] - a[1][1]*a[3][2]*a[2][3] - a[2][1]*a[1][2]*a[3][3] + a[1][1]*a[2][2]*a[3][3]) / scale,
                 (a[3][1]*a[2][2]*a[0][3] - a[2][1]*a[3][2]*a[0][3] - a[3][1]*a[0][2]*a[2][3] + a[0][1]*a[3][2]*a[2][3] + a[2][1]*a[0][2]*a[3][3] - a[0][1]*a[2][2]*a[3][3]) / scale,
                 (a[1][1]*a[3][2]*a[0][3] - a[3][1]*a[1][2]*a[0][3] + a[3][1]*a[0][2]*a[1][3] - a[0][1]*a[3][2]*a[1][3] - a[1][1]*a[0][2]*a[3][3] + a[0][1]*a[1][2]*a[3][3]) / scale,
                 (a[2][1]*a[1][2]*a[0][3] - a[1][1]*a[2][2]*a[0][3] - a[2][1]*a[0][2]*a[1][3] + a[0][1]*a[2][2]*a[1][3] + a[1][1]*a[0][2]*a[2][3] - a[0][1]*a[1][2]*a[2][3]) / scale},

                {(a[3][0]*a[2][2]*a[1][3] - a[2][0]*a[3][2]*a[1][3] - a[3][0]*a[1][2]*a[2][3] + a[1][0]*a[3][2]*a[2][3] + a[2][0]*a[1][2]*a[3][3] - a[1][0]*a[2][2]*a[3][3]) / scale,
                 (a[2][0]*a[3][2]*a[0][3] - a[3][0]*a[2][2]*a[0][3] + a[3][0]*a[0][2]*a[2][3] - a[0][0]*a[3][2]*a[2][3] - a[2][0]*a[0][2]*a[3][3] + a[0][0]*a[2][2]*a[3][3]) / scale,
                 (a[3][0]*a[1][2]*a[0][3] - a[1][0]*a[3][2]*a[0][3] - a[3][0]*a[0][2]*a[1][3] + a[0][0]*a[3][2]*a[1][3] + a[1][0]*a[0][2]*a[3][3] - a[0][0]*a[1][2]*a[3][3]) / scale,
                 (a[1][0]*a[2][2]*a[0][3] - a[2][0]*a[1][2]*a[0][3] + a[2][0]*a[0][2]*a[1][3] - a[0][0]*a[2][2]*a[1][3] - a[1][0]*a[0][2]*a[2][3] + a[0][0]*a[1][2]*a[2][3]) / scale},

                {(a[2][0]*a[3][1]*a[1][3] - a[3][0]*a[2][1]*a[1][3] + a[3][0]*a[1][1]*a[2][3] - a[1][0]*a[3][1]*a[2][3] - a[2][0]*a[1][1]*a[3][3] + a[1][0]*a[2][1]*a[3][3]) / scale,
                 (a[3][0]*a[2][1]*a[0][3] - a[2][0]*a[3][1]*a[0][3] - a[3][0]*a[0][1]*a[2][3] + a[0][0]*a[3][1]*a[2][3] + a[2][0]*a[0][1]*a[3][3] - a[0][0]*a[2][1]*a[3][3]) / scale,
                 (a[1][0]*a[3][1]*a[0][3] - a[3][0]*a[1][1]*a[0][3] + a[3][0]*a[0][1]*a[1][3] - a[0][0]*a[3][1]*a[1][3] - a[1][0]*a[0][1]*a[3][3] + a[0][0]*a[1][1]*a[3][3]) / scale,
                 (a[2][0]*a[1][1]*a[0][3] - a[1][0]*a[2][1]*a[0][3] - a[2][0]*a[0][1]*a[1][3] + a[0][0]*a[2][1]*a[1][3] + a[1][0]*a[0][1]*a[2][3] - a[0][0]*a[1][1]*a[2][3]) / scale},

                {(a[3][0]*a[2][1]*a[1][2] - a[2][0]*a[3][1]*a[1][2] - a[3][0]*a[1][1]*a[2][2] + a[1][0]*a[3][1]*a[2][2] + a[2][0]*a[1][1]*a[3][2] - a[1][0]*a[2][1]*a[3][2]) / scale,
                 (a[2][0]*a[3][1]*a[0][2] - a[3][0]*a[2][1]*a[0][2] + a[3][0]*a[0][1]*a[2][2] - a[0][0]*a[3][1]*a[2][2] - a[2][0]*a[0][1]*a[3][2] + a[0][0]*a[2][1]*a[3][2]) / scale,
                 (a[3][0]*a[1][1]*a[0][2] - a[1][0]*a[3][1]*a[0][2] - a[3][0]*a[0][1]*a[1][2] + a[0][0]*a[3][1]*a[1][2] + a[1][0]*a[0][1]*a[3][2] - a[0][0]*a[1][1]*a[3][2]) / scale,
                 (a[1][0]*a[2][1]*a[0][2] - a[2][0]*a[1][1]*a[0][2] + a[2][0]*a[0][1]*a[1][2] - a[0][0]*a[2][1]*a[1][2] - a[1][0]*a[0][1]*a[2][2] + a[0][0]*a[1][1]*a[2][2]) / scale}
            };
            // clang-format on
        }
        Mat4& inversed() {
            *this = inverse();
            return *this;
        }
        static Mat4 zero() {
            return {
                {T_(0), T_(0), T_(0), T_(0)},
                {T_(0), T_(0), T_(0), T_(0)},
                {T_(0), T_(0), T_(0), T_(0)},
                {T_(0), T_(0), T_(0), T_(0)}
            };
        }
        static Mat4 identity() {
            return {
                {T_(1), T_(0), T_(0), T_(0)},
                {T_(0), T_(1), T_(0), T_(0)},
                {T_(0), T_(0), T_(1), T_(0)},
                {T_(0), T_(0), T_(0), T_(1)}
            };
        }
        static Mat4 scale(T x, T y, T z) {
            return {
                {x,     T_(0), T_(0), T_(0)},
                {T_(0), y,     T_(0), T_(0)},
                {T_(0), T_(0), z,     T_(0)},
                {T_(0), T_(0), T_(0), T_(1)}
            };
        }
        static Mat4 scale(const Vec3& v) {
            return scale(v[0], v[1], v[2]);
        }
        static Mat4 translate(T x, T y, T z) { // column major
            return {
                {T_(1), T_(0), T_(0), T_(0)},
                {T_(0), T_(1), T_(0), T_(0)},
                {T_(0), T_(0), T_(1), T_(0)},
                {x,     y,     z,     T_(1)}
            };
        }
        static Mat4 translate(const Vec3& v) {
            return translate(v[0], v[1], v[2]);
        }
        static Mat4 rotate(const Vec3& x, const Vec3& y, const Vec3& z) { // column major
            return {
                {x[0],  y[0],  z[0],  T_(0)},
                {x[1],  y[1],  z[1],  T_(0)},
                {x[2],  y[2],  z[2],  T_(0)},
                {T_(0), T_(0), T_(0), T_(1)}
            };
        }
        static Mat4 look(const Vec3& pos, const Vec3& target, Vec3 up) {
            Vec3 back  = (-target).normal();
            Vec3 right = up.cross(back).normal();
            up         = back.cross(right);

            return rotate(right, up, back) * translate(-pos); // right-to-left
        }
        static Mat4 perspective(T xFOV, T width, T height, T zNear, T zFar) {
            const T xScalar = T_(1) / tan(xFOV * Constants::DEGREES_TO_RADIANS_FACTOR<T> / T_(2)); // cotangent(xFOV_half_angle_in_radians)
            const T yScalar = width / height * xScalar;                                            // adjust for aspect ratio

            return {
                {xScalar, T_(0),   T_(0),                                  T_(0) },
                {T_(0),   yScalar, T_(0),                                  T_(0) },
                {T_(0),   T_(0),   -(zFar + zNear) / (zFar - zNear),       T_(-1)},
                {T_(0),   T_(0),   T_(-2) * zFar * zNear / (zFar - zNear), T_(0) }
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