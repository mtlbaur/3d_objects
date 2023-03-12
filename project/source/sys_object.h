#pragma once

#include "globals.h"

#include "utl_constants.h"
#include "utl_math_vec3.h"
#include "utl_math_vec4.h"

#include "sys_collider.h"

namespace D3::Sys {
    template <typename Mesh>
    struct Object {
        using Vec3 = Utl::Math::Vec3<float>;
        using Vec4 = Utl::Math::Vec4<float>;

        float radius;

        Vec3 pos;
        Vec3 posVel;
        Vec3 ang;
        Vec3 angVel;
        Vec4 color;

        Mesh mesh;

        Object()
            : radius(rng.F(cfg.object_radius[0], cfg.object_radius[1])),
              pos{rng.FN(cfg.object_pos[0][0] + radius, cfg.object_pos[1][0] - radius),
                  rng.FN(cfg.object_pos[0][1] + radius, cfg.object_pos[1][1] - radius),
                  rng.FN(cfg.object_pos[0][2] + radius, cfg.object_pos[1][2] - radius)},
              posVel{rng.FN(cfg.object_posVel[0][0], cfg.object_posVel[1][0]),
                     rng.FN(cfg.object_posVel[0][1], cfg.object_posVel[1][1]),
                     rng.FN(cfg.object_posVel[0][2], cfg.object_posVel[1][2])},
              ang{rng.FN(cfg.object_ang[0][0], cfg.object_ang[1][0]),
                  rng.FN(cfg.object_ang[0][1], cfg.object_ang[1][1]),
                  rng.FN(cfg.object_ang[0][2], cfg.object_ang[1][2])},
              angVel{rng.FN(cfg.object_angVel[0][0], cfg.object_angVel[1][0]),
                     rng.FN(cfg.object_angVel[0][1], cfg.object_angVel[1][1]),
                     rng.FN(cfg.object_angVel[0][2], cfg.object_angVel[1][2])},
              color{rng.F(cfg.object_color[0][0], cfg.object_color[1][0]),
                    rng.F(cfg.object_color[0][1], cfg.object_color[1][1]),
                    rng.F(cfg.object_color[0][2], cfg.object_color[1][2]),
                    rng.F(cfg.object_color[0][3], cfg.object_color[1][3])} {}

        void updatePos() { pos += posVel * state.frameTime; }
        void updateAng() {
            ang += angVel * state.frameTime;
            ang[0] = fmodf(ang[0], Utl::Constants::TWO_PI<float>);
            ang[1] = fmodf(ang[1], Utl::Constants::TWO_PI<float>);
            ang[2] = fmodf(ang[2], Utl::Constants::TWO_PI<float>);
        }
        void update() {
            updatePos();
            updateAng();
            Collider::Sphere::collide(pos, posVel, radius);
        }
    };
} // namespace D3::Sys