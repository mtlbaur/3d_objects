#include <iostream>
#include <chrono>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "globals.h"

#include "sys_camera.h"
#include "sys_renderer.h"

#include "gui_main_window.h"
#include "gui_menu_window.h"

static const std::string PATH_SYSTEM = "./data/";
static const std::string EXT_DEFAULT = ".cfg";

static D3::Sys::Camera camera;

static D3::GUI::MainWindow mainWindow;
static D3::GUI::MenuWindow menuWindow;

void glfwKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
void glfwWindowSizeCallback(GLFWwindow* glfwWindow, int x, int y);
void glfwCursorPosCallback(GLFWwindow* glfwWindow, double x, double y);
void glfwScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);

void execute();

int main() {
    glfwSetErrorCallback([](int error, const char* desc) {
        std::cerr << "GLFW error: " << error << ": " << desc << '\n';
        abort();
    });

    D3_UTL_REQUIRE(glfwInit());

    {
        cfg.load(PATH_SYSTEM, "system", EXT_DEFAULT);

        mainWindow.create("Objects",
                          static_cast<int>((state.SCREEN_X / 2.0f) - (state.screenX / 2.0f)),
                          static_cast<int>((state.SCREEN_Y / 2.0f) - (state.screenY / 2.0f)),
                          static_cast<int>(state.screenX),
                          static_cast<int>(state.screenY));

        // custom callbacks
        glfwSetKeyCallback(mainWindow.glfw.window, glfwKeyCallback);
        glfwSetWindowSizeCallback(mainWindow.glfw.window, glfwWindowSizeCallback);
        glfwSetCursorPosCallback(mainWindow.glfw.window, glfwCursorPosCallback);
        glfwSetScrollCallback(mainWindow.glfw.window, glfwScrollCallback);

        // forward all other events directly to available ImGui implementation callbacks
        glfwSetWindowFocusCallback(mainWindow.glfw.window, ImGui_ImplGlfw_WindowFocusCallback);
        glfwSetCursorEnterCallback(mainWindow.glfw.window, ImGui_ImplGlfw_CursorEnterCallback);
        glfwSetMouseButtonCallback(mainWindow.glfw.window, ImGui_ImplGlfw_MouseButtonCallback);
        glfwSetCharCallback(mainWindow.glfw.window, ImGui_ImplGlfw_CharCallback);

        execute();

        mainWindow.destroy();

        cfg.save(PATH_SYSTEM, "system", EXT_DEFAULT);
    }

    glfwTerminate();
}

void execute() {
    D3::Sys::Renderer renderer(camera, 1000);

    std::chrono::steady_clock::time_point updateTime  = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point currentTime = updateTime;
    std::chrono::duration<float>          deltaTime   = currentTime - updateTime; // seconds

    while (!glfwWindowShouldClose(mainWindow.glfw.window)) {
        currentTime = std::chrono::steady_clock::now();
        deltaTime   = currentTime - updateTime; // seconds

        // if delta time is greater than the target number of seconds per frame, start a new frame
        if (deltaTime.count() > 1.0f / cfg.display_targetFPS) {
            updateTime      = currentTime;
            state.frameTime = deltaTime.count();

            {
                mainWindow.startFrame();

                {
                    state.update.view |= camera.update(mainWindow.glfw.window);

                    renderer.render(camera);

                    state.update.set(false);
                }
                {
                    mainWindow.startImGuiFrame();

                    menuWindow.display(renderer, camera, mainWindow);

                    mainWindow.endImGuiFrame();
                }

                mainWindow.endFrame();
            }
        }
    }
}

void glfwKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
    if (mainWindow.imgui.io->WantCaptureKeyboard) {
        ImGui_ImplGlfw_KeyCallback(glfwWindow, key, scancode, action, mods);
    } else {
        if (action == GLFW_PRESS) {
            camera.moveUpdate(key, true);
            state.update.view = true;

            switch (key) {
                case GLFW_KEY_F:
                    if (glfwGetWindowAttrib(glfwWindow, GLFW_MAXIMIZED)) glfwRestoreWindow(glfwWindow);
                    else glfwMaximizeWindow(glfwWindow);
                    break;
                case GLFW_KEY_R:
                    cfg.shader_object_sourceLightPosition = camera.pos;
                    state.update.sourceLightPosition      = true;
                    break;
                case GLFW_KEY_ESCAPE:
                    menuWindow.enabled ^= true;
                    mainWindow.switchMode(menuWindow.enabled, camera);
                    break;
            }
        } else if (action == GLFW_RELEASE) {
            camera.moveUpdate(key, false);
            state.update.view = true;
        }
    }
}

void glfwWindowSizeCallback(GLFWwindow* glfwWindow, int x, int y) {
    state.screenX           = static_cast<float>(x);
    state.screenY           = static_cast<float>(y);
    state.update.projection = true;
}

void glfwCursorPosCallback(GLFWwindow* glfwWindow, double x, double y) {
    if (mainWindow.imgui.io->WantCaptureKeyboard || menuWindow.enabled) {
        ImGui_ImplGlfw_CursorPosCallback(glfwWindow, x, y);
    } else {
        camera.cursorUpdate(static_cast<float>(x), static_cast<float>(y));
        state.update.view = true;
    }
}

void glfwScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset) {
    if (mainWindow.imgui.io->WantCaptureMouse) {
        ImGui_ImplGlfw_ScrollCallback(glfwWindow, xoffset, yoffset);
    } else {
        cfg.display_xFOV -= 5.0f * static_cast<float>(yoffset);

        if (cfg.display_xFOV < 5.0f) {
            cfg.display_xFOV = 5.0f;
        } else if (cfg.display_xFOV > 175.0f) {
            cfg.display_xFOV = 175.0f;
        }

        state.update.projection = true;
    }
}