#pragma once

#include "globals.h"

#include "utl_math_vec3.h"

namespace D3::Sys::Collider {
    namespace Sphere {
        using Vec3 = Utl::Math::Vec3<float>;

        void wallMin(float& pos, float& vel, float radius, float minPos) {
            if (pos - radius < minPos) {
                pos = std::max(minPos + radius, minPos + (minPos - (pos - radius)));
                vel = -vel;
            }
        }
        void wallMax(float& pos, float& vel, float radius, float maxPos) {
            if (pos + radius > maxPos) {
                pos = std::min(maxPos - radius, maxPos + (maxPos - (pos + radius)));
                vel = -vel;
            }
        }
        void collide(Vec3& pos, Vec3& posVel, float radius) {
            wallMin(pos[0], posVel[0], radius, cfg.space_bounds[0][0]);
            wallMin(pos[1], posVel[1], radius, cfg.space_bounds[0][1]);
            wallMin(pos[2], posVel[2], radius, cfg.space_bounds[0][2]);
            wallMax(pos[0], posVel[0], radius, cfg.space_bounds[1][0]);
            wallMax(pos[1], posVel[1], radius, cfg.space_bounds[1][1]);
            wallMax(pos[2], posVel[2], radius, cfg.space_bounds[1][2]);
        }
    } // namespace Sphere
} // namespace D3::Sys::Collider