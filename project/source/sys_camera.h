#pragma once

#include <algorithm>

#include <GLFW/glfw3.h>

#include "globals.h"

#include "utl_constants.h"
#include "utl_math_vec3.h"

namespace D3::Sys {
    class Camera {
        using Vec3 = Utl::Math::Vec3<float>;

        bool forward = false;
        bool back    = false;
        bool left    = false;
        bool right   = false;

        float yaw   = Utl::Constants::HALF_PI<float>; // initially turn 90 degrees to the right to look at the origin
        float pitch = 0.0f;

        void yawUpdate(float xDiff) {
            yaw = fmodf(yaw + xDiff * cfg.camera_sensitivity[0], Utl::Constants::TWO_PI<float>);
        }

        void pitchUpdate(float yDiff) {
            pitch += yDiff * cfg.camera_sensitivity[1];

            if (pitch < -Utl::Constants::EIGHTY_NINE_DEGREES_IN_RADIANS<float>) {
                pitch = -Utl::Constants::EIGHTY_NINE_DEGREES_IN_RADIANS<float>;
            } else if (pitch > Utl::Constants::EIGHTY_NINE_DEGREES_IN_RADIANS<float>) {
                pitch = Utl::Constants::EIGHTY_NINE_DEGREES_IN_RADIANS<float>;
            }
        }

      public:
        Vec3 xAxis{1.0f, 0.0f, 0.0f};
        Vec3 yAxis{0.0f, 1.0f, 0.0f};
        Vec3 zAxis{0.0f, 0.0f, 1.0f};

        struct Cursor {
            float xPrev = state.screenX / 2.0f;
            float yPrev = state.screenY / 2.0f;
            float x     = xPrev;
            float y     = yPrev;
        } cursor;

        Vec3 pos{0.0f, 0.0f, -3.0f * cfg.space_base};
        Vec3 target{1.0f, 1.0f, 1.0f};

        void cursorUpdate(float x, float y) {
            cursor.x = x;
            cursor.y = y;
        }

        void moveUpdate(int key, bool moving) {
            switch (key) {
                case GLFW_KEY_W:
                    forward = moving;
                    break;
                case GLFW_KEY_S:
                    back = moving;
                    break;
                case GLFW_KEY_A:
                    left = moving;
                    break;
                case GLFW_KEY_D:
                    right = moving;
                    break;
            }
        }

        bool update(GLFWwindow* window) {
            bool adjusted = true;

            { // ANGLE
                adjusted |= cursor.x != cursor.xPrev || cursor.y != cursor.yPrev;

                if (adjusted) {
                    yawUpdate(cursor.x - cursor.xPrev);
                    pitchUpdate(cursor.yPrev - cursor.y);

                    cursor.xPrev = cursor.x;
                    cursor.yPrev = cursor.y;

                    target[0] = cosf(yaw) * cosf(pitch);
                    target[1] = sinf(pitch);
                    target[2] = sinf(yaw) * cosf(pitch);
                    target.normalized();
                }
            }
            { // POSITION
                if (!(forward && back)) {
                    if (forward) {
                        pos += target * (cfg.camera_speed[0] * state.frameTime);
                        adjusted |= true;
                    }
                    if (back) {
                        pos -= target * (cfg.camera_speed[1] * state.frameTime);
                        adjusted |= true;
                    }
                }
                if (!(left && right)) {
                    if (left) {
                        pos -= target.cross(yAxis).normal() * (cfg.camera_speed[2] * state.frameTime);
                        adjusted |= true;
                    }
                    if (right) {
                        pos += target.cross(yAxis).normal() * (cfg.camera_speed[3] * state.frameTime);
                        adjusted |= true;
                    }
                }
            }

            return adjusted;
        }
    };
} // namespace D3::Sys