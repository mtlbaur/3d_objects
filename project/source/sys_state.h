#pragma once

#include "utl_math_vec3.h"

namespace D3::Sys {
    struct State {
        const float SCREEN_X = 1920.0;
        const float SCREEN_Y = 1080.0;

        float screenX = SCREEN_X * 0.75;
        float screenY = SCREEN_Y * 0.75;

        float frameTime = 0.0;

        struct Update {
            bool view                = false;
            bool projection          = false;
            bool sourceLight         = false;
            bool ambientLight        = false;
            bool sourceLightPosition = false;

            void set(bool val) {
                view                = val;
                projection          = val;
                sourceLight         = val;
                ambientLight        = val;
                sourceLightPosition = val;
            }
        } update;
    };
} // namespace D3::Sys