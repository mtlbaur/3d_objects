#pragma once

#include <imgui.h>

#include "sys_cfg.h"
#include "sys_renderer.h"
#include "sys_camera.h"

#include "globals.h"

#include "gui_main_window.h"

namespace D3::GUI {
    struct MenuWindow {
        bool enabled = false;

        void display(Sys::Renderer& renderer, Sys::Camera& camera, MainWindow& mainWindow) {
            static const ImGuiWindowFlags WINDOW_FLAGS = ImGuiWindowFlags_AlwaysAutoResize;
            static bool                   enabledLast  = enabled;

            if (enabled) {
                if (enabledLast != enabled) {
                    enabledLast = enabled;
                    mainWindow.menuMode();
                }

                if (ImGui::Begin("Menu", &enabled, WINDOW_FLAGS)) {
                    static float                    FS   = 1.0f;
                    static const char               IF[] = "%d";
                    static const char               FF[] = "%.2f";
                    static const ImGuiSliderFlags   SF   = ImGuiSliderFlags_AlwaysClamp;
                    static const ImGuiTreeNodeFlags TNF  = 0;

                    if (ImGui::CollapsingHeader("Camera", TNF)) {
                        ImGui::Text("Speed");
                        ImGui::DragFloat("Forward", &cfg.camera_speed[0], cfg.space_base / 10000.0f, 1.0f, cfg.space_base, FF, SF);
                        ImGui::DragFloat("Back", &cfg.camera_speed[1], cfg.space_base / 10000.0f, 1.0f, cfg.space_base, FF, SF);
                        ImGui::DragFloat("Left", &cfg.camera_speed[2], cfg.space_base / 10000.0f, 1.0f, cfg.space_base, FF, SF);
                        ImGui::DragFloat("Right", &cfg.camera_speed[3], cfg.space_base / 10000.0f, 1.0f, cfg.space_base, FF, SF);

                        ImGui::Text("Sensitivity");
                        ImGui::DragFloat("X##CAMERA_SENSITIVITY", &cfg.camera_sensitivity[0], 0.000001, 0.00001f, 0.01f, "%.6f", SF);
                        ImGui::DragFloat("Y##CAMERA_SENSITIVITY", &cfg.camera_sensitivity[1], 0.000001, 0.00001f, 0.01f, "%.6f", SF);
                        ImGui::DragFloat("Z##CAMERA_SENSITIVITY", &cfg.camera_sensitivity[2], 0.000001, 0.00001f, 0.01f, "%.6f", SF);
                    }

                    if (ImGui::CollapsingHeader("Space", TNF)) {
                        static float s = cfg.space_base / 1000.0f;

                        ImGui::Text("Bounds");

                        if (ImGui::DragFloat("X##SPACE_BASE", &cfg.space_bounds[1][0], s, 0.0f, cfg.space_base, FF, SF)) {
                            cfg.space_bounds[0][0] = -cfg.space_bounds[1][0];
                        }
                        if (ImGui::DragFloat("Y##SPACE_BASE", &cfg.space_bounds[1][1], s, 0.0f, cfg.space_base, FF, SF)) {
                            cfg.space_bounds[0][1] = -cfg.space_bounds[1][1];
                        }
                        if (ImGui::DragFloat("Z##SPACE_BASE", &cfg.space_bounds[1][2], s, 0.0f, cfg.space_base, FF, SF)) {
                            cfg.space_bounds[0][2] = -cfg.space_bounds[1][2];
                        }
                    }

                    if (ImGui::CollapsingHeader("Display", TNF)) {
                        ImGui::DragFloat("FPS", &cfg.display_targetFPS, FS, 60.0f, 600.0f, FF, SF);

                        if (ImGui::DragFloat("X FOV", &cfg.display_xFOV, 1.0f, 5.0f, 175.0f, "%.1f", SF)) {
                            state.update.projection = true;
                        }
                        {
                            static float s = cfg.space_base / 100.0f;

                            if (ImGui::DragFloatRange2("Z Near/Far", &cfg.display_zNear, &cfg.display_zFar, s, cfg.display_zNear_min, cfg.display_zFar_max, FF, FF, SF)) {
                                state.update.projection = true;
                            }
                        }
                    }

                    if (ImGui::CollapsingHeader("Object", TNF)) {
                        {
                            static int count = 1000;

                            if (ImGui::Button("Clear")) { renderer.clear(); }

                            ImGui::SameLine();
                            if (ImGui::Button("Rem")) { renderer.remRandom(count); }

                            ImGui::SameLine();
                            ImGui::DragInt("##REM_ADD_DRAG_INT", &count, FS, 1, 10000, IF, SF);

                            ImGui::SameLine();
                            if (ImGui::Button("Add")) { renderer.addRandom(count); }

                            ImGui::SameLine();
                            if (ImGui::Button("Regen")) { renderer.regen(); }
                        }

                        ImGui::Separator();
                        ImGui::DragFloatRange2("Radius", &cfg.object_radius[0], &cfg.object_radius[1], cfg.space_base / 10000.0f, 1.0f, cfg.space_base, FF, FF, SF);

                        ImGui::Text("Color Range");
                        ImGui::ColorEdit4("Min", cfg.object_color[0].a);
                        ImGui::ColorEdit4("Max", cfg.object_color[1].a);

                        {
                            static float s = cfg.space_base / 1000.0f;

                            ImGui::Text("Position");
                            ImGui::DragFloatRange2("X##POS", &cfg.object_pos[0][0], &cfg.object_pos[1][0], s, 0.0f, cfg.space_base, FF, FF, SF);
                            ImGui::DragFloatRange2("Y##POS", &cfg.object_pos[0][1], &cfg.object_pos[1][1], s, 0.0f, cfg.space_base, FF, FF, SF);
                            ImGui::DragFloatRange2("Z##POS", &cfg.object_pos[0][2], &cfg.object_pos[1][2], s, 0.0f, cfg.space_base, FF, FF, SF);

                            ImGui::Text("Velocity");
                            ImGui::DragFloatRange2("X##POS_VEL", &cfg.object_posVel[0][0], &cfg.object_posVel[1][0], s, 0.0f, cfg.space_base, FF, FF, SF);
                            ImGui::DragFloatRange2("Y##POS_VEL", &cfg.object_posVel[0][1], &cfg.object_posVel[1][1], s, 0.0f, cfg.space_base, FF, FF, SF);
                            ImGui::DragFloatRange2("Z##POS_VEL", &cfg.object_posVel[0][2], &cfg.object_posVel[1][2], s, 0.0f, cfg.space_base, FF, FF, SF);
                        }
                        {
                            static float s = 0.01f;

                            ImGui::Text("Angle");
                            ImGui::DragFloatRange2("X##ANG", &cfg.object_ang[0][0], &cfg.object_ang[1][0], s, 0.0f, Utl::Constants::TWO_PI<float>, FF, FF, SF);
                            ImGui::DragFloatRange2("Y##ANG", &cfg.object_ang[0][1], &cfg.object_ang[1][1], s, 0.0f, Utl::Constants::TWO_PI<float>, FF, FF, SF);
                            ImGui::DragFloatRange2("Z##ANG", &cfg.object_ang[0][2], &cfg.object_ang[1][2], s, 0.0f, Utl::Constants::TWO_PI<float>, FF, FF, SF);

                            ImGui::Text("Angular Velocity");
                            ImGui::DragFloatRange2("X##ANG_VEL", &cfg.object_angVel[0][0], &cfg.object_angVel[1][0], s, 0.0f, 10.0f * Utl::Constants::TWO_PI<float>, FF, FF, SF);
                            ImGui::DragFloatRange2("Y##ANG_VEL", &cfg.object_angVel[0][1], &cfg.object_angVel[1][1], s, 0.0f, 10.0f * Utl::Constants::TWO_PI<float>, FF, FF, SF);
                            ImGui::DragFloatRange2("Z##ANG_VEL", &cfg.object_angVel[0][2], &cfg.object_angVel[1][2], s, 0.0f, 10.0f * Utl::Constants::TWO_PI<float>, FF, FF, SF);
                        }
                    }

                    if (ImGui::CollapsingHeader("Light", TNF)) {
                        if (ImGui::ColorEdit4("Source##LIGHT", cfg.shader_object_sourceLight.a)) {
                            state.update.sourceLight = true;
                        }
                        if (ImGui::ColorEdit4("Ambient##LIGHT", cfg.shader_object_ambientLight.a)) {
                            state.update.ambientLight = true;
                        }
                        if (ImGui::Button("Reset Source Position##LIGHT")) {
                            cfg.shader_object_sourceLightPosition = {0.0f, 0.0f, 0.0f};
                            state.update.sourceLightPosition      = true;
                        }

                        ImGui::SameLine();
                        ImGui::Text("(%.0f, %.0f, %.0f)",
                                    cfg.shader_object_sourceLightPosition[0],
                                    cfg.shader_object_sourceLightPosition[1],
                                    cfg.shader_object_sourceLightPosition[2]);
                    }

                    if (ImGui::CollapsingHeader("Stats", TNF)) {
                        static const ImGuiTableFlags TABLE_FLAGS = ImGuiTableFlags_Borders |
                                                                   ImGuiTableFlags_SizingFixedFit |
                                                                   ImGuiTableFlags_NoHostExtendX;

                        if (ImGui::BeginTable("##STATS_TABLE", 2, TABLE_FLAGS)) {
                            ImGui::TableNextColumn();
                            ImGui::Text("Count: %u", static_cast<unsigned>(renderer.count));

                            ImGui::TableNextColumn();
                            ImGui::Text("FPS: %.2f", 1.0f / state.frameTime);
                        }

                        ImGui::EndTable();
                    }

                    ImGui::Separator();
                    if (ImGui::Button("Exit")) { mainWindow.close(); }

                    ImGui::SameLine();
                    if (ImGui::Button("Reset")) {
                        cfg.reset();
                        state.update.set(true);
                    }
                }

                ImGui::End();
            } else {
                if (enabledLast != enabled) {
                    enabledLast = enabled;
                    mainWindow.centerCursor(camera);
                    mainWindow.cameraMode();
                }
            }
        }
    };
} // namespace D3::GUI