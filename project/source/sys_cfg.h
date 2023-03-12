#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <cmath>

// https://www.boost.org/doc/libs/1_79_0/libs/filesystem/doc/tutorial.html
#include <boost/filesystem.hpp>

// https://www.boost.org/doc/libs/1_79_0/libs/serialization/doc/index.html
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "utl_constants.h"
#include "utl_math_vec2.h"
#include "utl_math_vec3.h"
#include "utl_math_vec4.h"

namespace D3::Sys {
    struct CFG {
        template <typename T>
        using Vec2 = Utl::Math::Vec2<T>;
        template <typename T>
        using Vec3 = Utl::Math::Vec3<T>;
        template <typename T>
        using Vec4 = Utl::Math::Vec4<T>;

        using Vec2F = Utl::Math::Vec2<float>;
        using Vec3F = Utl::Math::Vec3<float>;
        using Vec4F = Utl::Math::Vec4<float>;

        // CAMERA

        Vec4F camera_speed{100000.0f, 100000.0f, 100000.0f, 100000.0f};

        Vec3F camera_sensitivity{0.001f, 0.001f, 0.001f};

        // SPACE

        float space_base = 100000.0f;

        Vec2<Vec3F> space_bounds{
            {-space_base, -space_base, -space_base},
            {space_base,  space_base,  space_base }
        };

        // DISPLAY

        float display_targetFPS = 300.0;
        float display_xFOV      = 90.0f;

        float display_zNear_min = 0.0f;
        float display_zNear     = space_base / 1000.0f;

        float display_zFar_max = space_base * 10.0f;
        float display_zFar     = display_zFar_max;

        // OBJECT

        Vec2F object_radius{space_base / 1000.0f, space_base / 100.0f};

        Vec2<Vec3F> object_pos{
            {0.0f, 0.0f, 0.0f},
            space_bounds[1]
        };
        Vec2<Vec3F> object_posVel{space_bounds[1] / 1000.0f, space_bounds[1] / 10.0f};

        Vec2<Vec3F> object_ang{
            {0.0f,                          0.0f,                          0.0f                         },
            {Utl::Constants::TWO_PI<float>, Utl::Constants::TWO_PI<float>, Utl::Constants::TWO_PI<float>}
        };
        Vec2<Vec3F> object_angVel{
            {0.0f,                          0.0f,                          0.0f                         },
            {Utl::Constants::TWO_PI<float>, Utl::Constants::TWO_PI<float>, Utl::Constants::TWO_PI<float>}
        };

        Vec2<Vec4F> object_color{
            {0.0f, 0.0f, 0.0f, 1.0f},
            {1.0f, 1.0f, 1.0f, 1.0f}
        };

        // SHADER

        Vec4F shader_object_sourceLight{1.0f, 1.0f, 1.0f, 1.0f};
        Vec4F shader_object_ambientLight{0.1f, 0.1f, 0.1f, 0.1f};
        Vec3F shader_object_sourceLightPosition{0.0f, 0.0f, 0.0f};

        // METHODS

        void reset();
        void save(const std::string& path, const std::string& name, const std::string& extension);
        void load(const std::string& path, const std::string& name, const std::string& extension);

        template <class Archive>
        void serialize(Archive& archive, const unsigned version) {
            // CAMERA

            archive& camera_speed;
            archive& camera_sensitivity;

            // SPACE

            archive& space_base;
            archive& space_bounds;

            // DISPLAY

            archive& display_targetFPS;
            archive& display_xFOV;
            archive& display_zNear;
            archive& display_zFar;

            // OBJECT

            archive& object_radius;

            archive& object_pos;
            archive& object_posVel;

            archive& object_ang;
            archive& object_angVel;

            archive& object_color;
        }
    };
} // namespace D3::Sys