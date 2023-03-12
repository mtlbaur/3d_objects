3D objects:
- Objects that move/spin in 3D space.
- Basic ambient and diffuse lighting.
- A moveable camera:
    - `W`: forward.
    - `S`: back.
    - `A`: left.
    - `D`: right.
    - Mouse: look.
    - Scroll: zoom.
    - `R`: move the light source to the current camera position.
- Object properties randomly generated within ranges:
    - Sizes
    - Color.
    - Velocity.
    - Angular velocity.
    - Position.
- `Esc` opens a menu with:
    - Object adding and removal.
    - Adjustable:
        - Object property generation ranges.
        - FPS.
        - FOV.
        - Z near/far.
    - The values for these settings are automatically written/read on shutdown/start to `./data/system.cfg`.
- Custom vector, matrix, and quaternion classes are used in place of GLM's equivalent functionality.
    - The reason for this was to get a better conceptual understanding of those aspects of the program.

A demo can be found [here](https://youtu.be/ay0lFK7qOYA).

***

This project was created with:
- `C++20`
- `clang++ 14.0.6`
- `clang-format 14.0.6`
- `clang-tidy 14.0.6`
- `CMake 3.25.1`
- [Ninja 1.11.0](https://github.com/ninja-build/ninja)
- `gdb 12.1`
- `VSCode`
- `Blender 3.4.1.0`
- `Windows 10`

The project uses:
- [OpenGL 4.6](https://www.opengl.org/)
- [GLFW 3.3.2](https://www.glfw.org/)
- [Glad 2 in core configuration for OpenGL 4.6](https://github.com/Dav1dde/glad/tree/glad2)
    - This is the [OpenGL Loader Library](https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library)
- [GLM 0.9.9.8](https://github.com/g-truc/glm)
- [Dear ImGui 1.89.2](https://github.com/ocornut/imgui)
- [Boost 1.79.0](https://www.boost.org/)
    - Filesystem
    - Serialization
    - Unit Test Framework

Further credits:
- GLM:
    - Tests are built against it.
    - Reference point for own implementations.
- https://learnopengl.com/
    - Primary source of OpenGL-related information.
- https://www.euclideanspace.com/
    - Useful math formulas and explanations.

See [LICENSE.md](LICENSE.md) for information on the licenses relating to this project.

***

Notes:
- Folders:
    - `./project/source/` contains program source files.
    - `./test/source/` contains test source code used to verify parts of the program's functionality via Boost's Unit Test Framework.
- Files:
    - `./setup.ps1` is a script used to prepare debug/release/test builds (and hard reset those builds).
        - It must be executed from the project's root directory i.e. where it is located in this repository.
        - It will recursively, without warning, delete two folders called `bin` and `build` and subsequently regenerate those folders and subfolders.
            - Via Window's `robocopy` it copies Boost's filesystem, serialization, and unit test framework `.dll` files to into the corresponding folders.
            - It executes CMake, using the `CMakeLists.txt` file located in `./project/`, with Ninja as the target build system for input file generation.
        - The separate builds are subsequently compiled/executed via VSCode launch/tasks.json files (not included in this repository):
            1. Ninja is called on the appropriate folders.
            2. The resulting executable is run with gdb as the debugger.
    - `./project/source/*`:
        - Files are prefixed with one or none of `sys`, `utl`, and `gui` which stand for "System", "Utility", and "Graphical User Interface".
            - `sys` indicates a component that is directly connected to the design of the program.
            - `utl` is a general utility that could, theoretically, be used for some other project as well.
            - `gui` is directly related to either GUI itself (the main menu), or the main window on which everything is rendered.
            - The only files that aren't prefixed are `main.cpp`, `globals.h`, and `globals.cpp`.
                - `main.cpp` is the main driver of the program; everything ties back to here in some form.
                - `globals.h` and `globals.cpp` contain only global declarations and instantiations; there are three, all of them classes:
                    - `rng` used to generate random numbers.
                    - `state` contains a few variables concerning the state of the program.
                    - `cfg` contains variables that are controlled via user input.