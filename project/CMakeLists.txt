cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_C_COMPILER_WORKS true)
set(CMAKE_CXX_COMPILER_WORKS true)
set(CMAKE_C_COMPILER "clang.exe")
set(CMAKE_CXX_COMPILER "clang++.exe")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(root_source "./source/")
set(root_tests "./tests/")
set(root_libraries "../../../libraries/")

set(root_imgui "${root_libraries}imgui-1.89.2/")
set(root_glad2 "${root_libraries}glad2_core/")
set(root_glfw "${root_libraries}glfw-3.3.2/")
set(root_glm "${root_libraries}glm-0.9.9.8/")
set(root_boost "${root_libraries}boost_1_79_0/")

message(${root_source})
message(${root_tests})
message(${root_libraries})

message(${root_imgui})
message(${root_glad2})
message(${root_glfw})
message(${root_glm})
message(${root_boost})

# this is supposed to prevent vscode from cutting off error messages in its problems window
add_compile_options("-fmessage-length=0")

if(PROGRAM_BUILD)
    message("BUILDING PROGRAM")
    project(objects)

    include_directories(
        ${root_source}
        ${root_tests}
        ${root_imgui}
        "${root_imgui}backends"
        "${root_glad2}include"
        "${root_glfw}include"
        "${root_glm}glm"
        ${root_boost}
    )

    find_library(library_glfw3
        NAMES
        "glfw3"
        PATHS
        "${root_glfw}build/src/"
    )
    find_library(library_boost_filesystem
        NAMES
        "boost_filesystem-mgw12-mt-x64-1_79"
        PATHS
        "${root_boost}stage/lib/"
    )
    find_library(library_boost_serialization
        NAMES
        "boost_serialization-mgw12-mt-x64-1_79"
        PATHS
        "${root_boost}stage/lib/"
    )

    message(${library_glfw3})
    message(${library_boost_filesystem})
    message(${library_boost_serialization})

    link_libraries(
        "gdi32"
        ${library_glfw3}
        ${library_boost_filesystem}
        ${library_boost_serialization}
    )

    set(sources
        "${root_source}main.cpp"
        "${root_source}globals.cpp"
        "${root_source}sys_cfg.cpp"

        "${root_imgui}imgui.cpp"
        "${root_imgui}imgui_demo.cpp"
        "${root_imgui}imgui_draw.cpp"
        "${root_imgui}imgui_tables.cpp"
        "${root_imgui}imgui_widgets.cpp"
        "${root_imgui}backends/imgui_impl_glfw.cpp"
        "${root_imgui}backends/imgui_impl_opengl3.cpp"

        "${root_glad2}src/gl.c"
    )

    add_executable(objects ${sources})
else()
    message("BUILDING TESTS")
    project(tests)

    include_directories(
        ${root_source}
        ${root_tests}
        ${root_boost}
        "${root_glm}glm"
    )

    find_library(library_boost_unit_test_framework
        NAMES
        "libboost_unit_test_framework-mgw12-mt-x64-1_79"
        PATHS
        "${root_boost}stage/lib/"
    )

    message(${library_boost_unit_test_framework})

    link_libraries(
        ${library_boost_unit_test_framework}
    )

    set(sources
        "${root_tests}tests.cpp"
    )

    add_executable(tests ${sources})
endif()