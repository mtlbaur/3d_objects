#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "globals.h"

#include "utl_require.h"

#include "sys_camera.h"

static const int GLFW_VER_MAJOR = 4;
static const int GLFW_VER_MINOR = 6;

static const int GLFW_MSAA_SAMPLES = 4;

static const char* GLSL_VER = "#version 130";

namespace D3::GUI {
    struct MainWindow {
        struct {
            GLFWwindow* window = nullptr;
        } glfw;

        struct {
            ImGuiContext* context = nullptr;
            ImGuiIO*      io      = nullptr;
        } imgui;

        void create(const char* TITLE, int xPos, int yPos, int xSize, int ySize) {
            if (glfw.window) return;
            {
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VER_MAJOR);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VER_MINOR);
                glfwWindowHint(GLFW_SAMPLES, GLFW_MSAA_SAMPLES); // NOTE: if you disable GLFW_DOUBLEBUFFER, this will no longer work

                glfw.window = glfwCreateWindow(xSize, ySize, TITLE, nullptr, nullptr);

                D3_UTL_REQUIRE(glfw.window);

                glfwSetWindowPos(glfw.window, xPos, yPos);
                glfwSetCursorPos(glfw.window, xSize / 2.0, ySize / 2.0);
                glfwMakeContextCurrent(glfw.window);

                D3_UTL_REQUIRE(gladLoadGL(glfwGetProcAddress));

                glEnable(GL_MULTISAMPLE);
                glEnable(GL_DEPTH_TEST);

                D3_UTL_REQUIRE(glfwRawMouseMotionSupported());

                glfwSetInputMode(glfw.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetInputMode(glfw.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
            }
            {
                IMGUI_CHECKVERSION();

                imgui.context = ImGui::CreateContext();

                ImGui::SetCurrentContext(imgui.context);
                ImGui::StyleColorsDark();

                imgui.io = &ImGui::GetIO();

                ImGui_ImplGlfw_InitForOpenGL(glfw.window, false);
                ImGui_ImplOpenGL3_Init(GLSL_VER);
            }
        }

        void destroy() {
            if (!glfw.window) return;
            {
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplGlfw_Shutdown();
                ImGui::DestroyContext();
            }
            {
                glfwDestroyWindow(glfw.window);
            }
        }

        void startFrame() {
            glfwPollEvents();

            glViewport(0, 0, state.screenX, state.screenY);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void startImGuiFrame() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void endImGuiFrame() {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        void endFrame() {
            glfwSwapBuffers(glfw.window);
        }

        void centerCursor() {
            glfwSetCursorPos(glfw.window, state.screenX / 2.0, state.screenY / 2.0);
        }

        void centerCursor(const D3::Sys::Camera& camera) {
            glfwSetCursorPos(glfw.window, camera.cursor.xPrev, camera.cursor.yPrev);
        }

        void cameraMode() {
            glfwSetInputMode(glfw.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetInputMode(glfw.window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }

        void menuMode() {
            centerCursor();
            glfwSetInputMode(glfw.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetInputMode(glfw.window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        }

        void switchMode(bool menuOpen, const D3::Sys::Camera& camera) {
            if (menuOpen) {
                menuMode();
            } else {
                centerCursor(camera);
                cameraMode();
            }
        }

        void close() { glfwSetWindowShouldClose(glfw.window, 1); }
    };
} // namespace D3::GUI