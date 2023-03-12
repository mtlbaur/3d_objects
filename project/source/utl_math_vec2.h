#pragma once

namespace D3::Utl::Math {
    template <typename T>
    struct Vec2 {
#define T_ static_cast<T>

        T a[2];

        Vec2() : a{T_(0), T_(0)} {}
        Vec2(T x, T y) : a{x, y} {}
        Vec2(const Vec2& v) : a{v[0], v[1]} {}
        Vec2(Vec2&& v) noexcept { *this = v; }

        const T& operator[](int i) const { return a[i]; }
        T&       operator[](int i) { return a[i]; }

        Vec2& operator=(const Vec2& v) {
            a[0] = v[0];
            a[1] = v[1];
            return *this;
        }
        Vec2& operator=(Vec2&& v) noexcept {
            *this = v;
            return *this;
        }
        bool operator==(const Vec2& v) {
            return {a[0] == v[0] &&
                    a[1] == v[1]};
        }
        Vec2 operator+(const Vec2& v) const {
            return {a[0] + v[0],
                    a[1] + v[1]};
        }
        Vec2& operator+=(const Vec2& v) {
            *this = *this + v;
            return *this;
        }
        Vec2 operator-(const Vec2& v) const {
            return {a[0] - v[0],
                    a[1] - v[1]};
        }
        Vec2& operator-=(const Vec2& v) {
            *this = *this - v;
            return *this;
        }
        Vec2 operator*(const Vec2& v) {
            return {a[0] * v[0],
                    a[1] * v[1]};
        }
        Vec2& operator*=(const Vec2& v) {
            *this = *this * v;
            return *this;
        }
        Vec2 operator*(T s) const {
            return {a[0] * s,
                    a[1] * s};
        }
        Vec2& operator*=(T s) {
            *this = *this * s;
            return *this;
        }
        Vec2 operator/(T s) const {
            return {a[0] / s,
                    a[1] / s};
        }
        Vec2& operator/=(T s) {
            *this = *this / s;
            return *this;
        }
        T dot(const Vec2& v) const {
            return {a[0] * v[0] +
                    a[1] * v[1]};
        }
        T mag() const {
            return sqrt(a[0] * a[0] +
                        a[1] * a[1]);
        }
        Vec2 normal() const {
            T m = mag();
            return {a[0] / m,
                    a[1] / m};
        }
        Vec2& normalized() {
            *this = normal();
            return *this;
        }
        template <class Archive>
        void serialize(Archive& archive, const unsigned version) {
            archive& a[0];
            archive& a[1];
        }
#undef T_
    };
} // namespace D3::Utl::Math