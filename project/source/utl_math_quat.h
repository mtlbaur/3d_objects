#pragma once

#include "utl_math_vec3.h"
#include "utl_math_mat4.h"

namespace D3::Utl::Math {
    template <typename T>
    class Quat {
#define T_ static_cast<T>

        using Vec3 = Vec3<T>;
        using Mat4 = Mat4<T>;

      public:
        T w, x, y, z; // w + xi + yj + zk

        Quat() = default;
        Quat(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}
        Quat(const Quat& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
        Quat(Quat&& q) noexcept { *this = q; }

        Quat& operator=(const Quat& q) {
            w = q.w;
            x = q.x;
            y = q.y;
            z = q.z;
            return *this;
        }
        Quat& operator=(Quat&& q) noexcept {
            *this = q;
            return *this;
        }
        bool operator==(const Quat& q) {
            return w == q.w && x == w.x && y == w.y && z == q.z;
        }
        Quat operator+(const Quat& q) const {
            return {w + q.w, x + q.x, y + q.y, z + q.z};
        }
        Quat& operator+=(const Quat& q) {
            *this = *this + q;
            return *this;
        }
        Quat operator-(const Quat& q) const {
            return {w - q.w, x - q.x, y - q.y, z - q.z};
        }
        Quat& operator-=(const Quat& q) {
            *this = *this - q;
            return *this;
        }
        Quat operator*(T s) const {
            return {w * s, x * s, y * s, z * s};
        }
        Quat& operator*=(T s) {
            *this = *this * s;
            return *this;
        }
        // source: see GLM's implementation located in: glm/detail/type_quat.inl
        // source: https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
        Quat operator*(const Quat& q) const {
            return {w * q.w - x * q.x - y * q.y - z * q.z,
                    w * q.x + x * q.w + y * q.z - z * q.y,
                    w * q.y + y * q.w + z * q.x - x * q.z,
                    w * q.z + z * q.w + x * q.y - y * q.x};
        }
        Quat& operator*=(const Quat& q) {
            *this = *this * q;
            return *this;
        }
        T mag() const {
            return sqrt(w * w + x * x + y * y + z * z);
        }
        Quat normal() const {
            T m = mag();
            return {w / m, x / m, y / m, z / m};
        }
        Quat& normalized() {
            *this = normal();
            return *this;
        }
        Quat conjugate() const {
            return {w, -x, -y, -z};
        }
        Quat& conjugated() {
            *this = conjugate();
            return *this;
        }
        static Quat zero() {
            return {T_(0), T_(0), T_(0), T_(0)};
        }
        static Quat position(const Vec3& pos) {
            return {T_(0), pos[0], pos[1], pos[2]};
        }
        // source: https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
        static Quat eulerAxisAngle(const Vec3& axis, T radians) {
            return {T_(cos(radians / T_(2))),
                    axis[0] * T_(sin(radians / T_(2))),
                    axis[1] * T_(sin(radians / T_(2))),
                    axis[2] * T_(sin(radians / T_(2)))};
        }
        // source: see GLM's implementation located in: glm/detail/type_quat.inl
        // note: creating a rotation quaternion via this is much more efficient than using eulerAxisAngle(z, r) * eulerAxisAngle(y, r) * eulerAxisAngle(x, r)
        static Quat eulerAngles(const Vec3& ang) {
            const T cx = cosf(ang[0] / T_(2));
            const T cy = cosf(ang[1] / T_(2));
            const T cz = cosf(ang[2] / T_(2));
            const T sx = sinf(ang[0] / T_(2));
            const T sy = sinf(ang[1] / T_(2));
            const T sz = sinf(ang[2] / T_(2));

            return {cx * cy * cz + sx * sy * sz,
                    sx * cy * cz - cx * sy * sz,
                    cx * sy * cz + sx * cy * sz,
                    cx * cy * sz - sx * sy * cz};
        }
        // source: https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
        static Mat4 rotationMatrix(const Quat& rotationNormal) {
            const Quat& q = rotationNormal;
            return {
                {T_(1) - T_(2) * (q.y * q.y + q.z * q.z), T_(2) * (q.x * q.y + q.z * q.w),         T_(2) * (q.x * q.z - q.y * q.w),         T_(0)},
                {T_(2) * (q.x * q.y - q.z * q.w),         T_(1) - T_(2) * (q.x * q.x + q.z * q.z), T_(2) * (q.y * q.z + q.x * q.w),         T_(0)},
                {T_(2) * (q.x * q.z + q.y * q.w),         T_(2) * (q.y * q.z - q.x * q.w),         T_(1) - T_(2) * (q.x * q.x + q.y * q.y), T_(0)},
                {T_(0),                                   T_(0),                                   T_(0),                                   T_(1)}
            };
        }
        static Mat4 rotationMatrix(const Vec3& ang) {
            return rotationMatrix(eulerAngles(ang).normal());
        }
        template <class Archive>
        void serialize(Archive& archive, const unsigned version) {
            archive& w;
            archive& x;
            archive& y;
            archive& z;
        }
#undef T_
    };
} // namespace D3::Utl::Math