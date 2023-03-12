#pragma once

namespace D3::Utl::Math {
    template <typename T>
    struct Vec3 {
#define T_ static_cast<T>

        T a[3];

        Vec3() : a{T_(0), T_(0), T_(0)} {}
        Vec3(T x, T y, T z) : a{x, y, z} {}
        Vec3(const Vec3& v) : a{v[0], v[1], v[2]} {}
        Vec3(Vec3&& v) noexcept { *this = v; }

        const T& operator[](int i) const { return a[i]; }
        T&       operator[](int i) { return a[i]; }

        Vec3& operator=(const Vec3& v) {
            a[0] = v[0];
            a[1] = v[1];
            a[2] = v[2];
            return *this;
        }
        Vec3& operator=(Vec3&& v) noexcept {
            *this = v;
            return *this;
        }
        bool operator==(const Vec3& v) {
            return {a[0] == v[0] &&
                    a[1] == v[1] &&
                    a[2] == v[2]};
        }
        Vec3 operator+(const Vec3& v) const {
            return {a[0] + v[0],
                    a[1] + v[1],
                    a[2] + v[2]};
        }
        Vec3& operator+=(const Vec3& v) {
            a[0] += v[0];
            a[1] += v[1];
            a[2] += v[2];
            return *this;
        }
        Vec3 operator-(const Vec3& v) const {
            return {a[0] - v[0],
                    a[1] - v[1],
                    a[2] - v[2]};
        }
        Vec3& operator-=(const Vec3& v) {
            a[0] -= v[0];
            a[1] -= v[1];
            a[2] -= v[2];
            return *this;
        }
        Vec3 operator*(const Vec3& v) {
            return {a[0] * v[0],
                    a[1] * v[1],
                    a[2] * v[2]};
        }
        Vec3& operator*=(const Vec3& v) {
            *this = *this * v;
            return *this;
        }
        Vec3 operator*(T s) const {
            return {a[0] * s,
                    a[1] * s,
                    a[2] * s};
        }
        Vec3& operator*=(T s) {
            a[0] *= s;
            a[1] *= s;
            a[2] *= s;
            return *this;
        }
        Vec3 operator/(T s) const {
            return {a[0] / s,
                    a[1] / s,
                    a[2] / s};
        }
        Vec3& operator/=(T s) {
            *this = *this / s;
            return *this;
        }
        T dot(const Vec3& v) const {
            return {a[0] * v[0] +
                    a[1] * v[1] +
                    a[2] * v[2]};
        }
        Vec3 cross(const Vec3<T>& v) const { // only defined in R3
            return {a[1] * v[2] - a[2] * v[1],
                    a[2] * v[0] - a[0] * v[2],
                    a[0] * v[1] - a[1] * v[0]};
        }
        Vec3& crossed(const Vec3<T>& v) {
            *this = cross(v);
            return *this;
        }
        T mag() const {
            return sqrt(a[0] * a[0] +
                        a[1] * a[1] +
                        a[2] * a[2]);
        }
        Vec3 normal() const {
            T m = mag();
            return {a[0] / m,
                    a[1] / m,
                    a[2] / m};
        }
        Vec3& normalized() {
            *this = normal();
            return *this;
        }
        template <class Archive>
        void serialize(Archive& archive, const unsigned version) {
            archive& a[0];
            archive& a[1];
            archive& a[2];
        }
#undef T_
    };

    template <typename T>
    Vec3<T> operator-(const Vec3<T>& v) {
        return v * static_cast<T>(-1);
    }
} // namespace D3::Utl::Math