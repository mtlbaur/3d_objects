#pragma once

#include <glad/gl.h>

#include "utl_math_vec3.h"
#include "utl_math_mat4.h"
#include "utl_math_quat.h"

namespace D3::Sys::Transform {
    using Vec3 = Utl::Math::Vec3<float>;
    using Mat4 = Utl::Math::Mat4<float>;
    using Quat = Utl::Math::Quat<float>;

    Mat4 model(const Vec3& pos, const Vec3& ang) {
        return Mat4::translate(pos) * Quat::rotationMatrix(ang);
    }
    Mat4 view(const Vec3& pos, const Vec3& target, const Vec3& upNormal) {
        return Mat4::look(pos, target, upNormal);
    }
    Mat4 projection(float xFOV, float width, float height, float zNear, float zFar) {
        return Mat4::perspective(xFOV, width, height, zNear, zFar);
    }
} // namespace D3::Sys::Transform