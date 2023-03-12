#pragma once

namespace D3::Utl::Math {
    template <typename T>
    struct Vec4 {
#define T_ static_cast<T>

        T a[4];

        Vec4() : a{T_(0), T_(0), T_(0), T_(0)} {}
        Vec4(T x, T y, T z, T w) : a{x, y, z, w} {}
        Vec4(const Vec4& v) : a{v[0], v[1], v[2], v[3]} {}
        Vec4(Vec4&& v) noexcept { *this = v; }

        const T& operator[](int i) const { return a[i]; }
        T&       operator[](int i) { return a[i]; }

        Vec4& operator=(const Vec4& v) {
            a[0] = v[0];
            a[1] = v[1];
            a[2] = v[2];
            a[3] = v[3];
            return *this;
        }
        Vec4& operator=(Vec4&& v) noexcept {
            *this = v;
            return *this;
        }
        bool operator==(const Vec4& v) {
            return {a[0] == v[0] &&
                    a[1] == v[1] &&
                    a[2] == v[2] &&
                    a[3] == v[3]};
        }
        Vec4 operator+(const Vec4& v) const {
            return {a[0] + v[0],
                    a[1] + v[1],
                    a[2] + v[2],
                    a[3] + v[3]};
        }
        Vec4& operator+=(const Vec4& v) {
            a[0] += v[0];
            a[1] += v[1];
            a[2] += v[2];
            a[3] += v[3];
            return *this;
        }
        Vec4 operator-(const Vec4& v) const {
            return {a[0] - v[0],
                    a[1] - v[1],
                    a[2] - v[2],
                    a[3] - v[3]};
        }
        Vec4& operator-=(const Vec4& v) {
            a[0] -= v[0];
            a[1] -= v[1];
            a[2] -= v[2];
            a[3] -= v[3];
            return *this;
        }
        Vec4 operator*(const Vec4& v) {
            return {a[0] * v[0],
                    a[1] * v[1],
                    a[2] * v[2],
                    a[3] * v[3]};
        }
        Vec4& operator*=(const Vec4& v) {
            *this = *this * v;
            return *this;
        }
        Vec4 operator*(T s) const {
            return {a[0] * s,
                    a[1] * s,
                    a[2] * s,
                    a[3] * s};
        }
        Vec4& operator*=(T s) {
            a[0] *= s;
            a[1] *= s;
            a[2] *= s;
            a[3] *= s;
            return *this;
        }
        Vec4 operator/(T s) const {
            return {a[0] / s,
                    a[1] / s,
                    a[2] / s,
                    a[3] / s};
        }
        Vec4& operator/=(T s) {
            *this = *this / s;
            return *this;
        }
        T dot(const Vec4& v) const {
            return {a[0] * v[0] +
                    a[1] * v[1] +
                    a[2] * v[2] +
                    a[3] * v[3]};
        }
        T mag() const {
            return sqrt(a[0] * a[0] +
                        a[1] * a[1] +
                        a[2] * a[2] +
                        a[3] * a[3]);
        }
        Vec4 normal() const {
            T m = mag();
            return {a[0] / m,
                    a[1] / m,
                    a[2] / m,
                    a[3] / m};
        }
        Vec4& normalized() {
            *this = normal();
            return *this;
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