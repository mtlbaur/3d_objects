#pragma once

#include <iostream>

#include <glad/gl.h>

#include "utl_math_vec3.h"
#include "utl_math_vec4.h"
#include "utl_math_mat4.h"

namespace {
    void error(void (*fnc_iv)(GLuint, GLenum, GLint*), void (*fnc_log)(GLuint, GLsizei, GLsizei*, GLchar*), int comp, const std::string& msg) {
        int logLength;
        fnc_iv(comp, GL_INFO_LOG_LENGTH, &logLength);

        if (logLength < 1) logLength = 1;

        char log[logLength];
        fnc_log(comp, logLength, nullptr, log);

        std::cerr << "Shader: ERROR: " << msg << ":\n"
                  << log << '\n';

        abort();
    }
} // namespace

namespace D3::Sys::Shader {
    using Vec3 = Utl::Math::Vec3<float>;
    using Vec4 = Utl::Math::Vec4<float>;
    using Mat4 = Utl::Math::Mat4<float>;

    const char* name(int type) {
        switch (type) {
            case GL_VERTEX_SHADER:
                return "GL_VERTEX_SHADER";
            case GL_TESS_CONTROL_SHADER:
                return "GL_TESS_CONTROL_SHADER";
            case GL_TESS_EVALUATION_SHADER:
                return "GL_TESS_EVALUATION_SHADER";
            case GL_GEOMETRY_SHADER:
                return "GL_GEOMETRY_SHADER";
            case GL_FRAGMENT_SHADER:
                return "GL_FRAGMENT_SHADER";
            case GL_COMPUTE_SHADER:
                return "GL_COMPUTE_SHADER";
            default:
                return "INVALID_SHADER_TYPE";
        }
    }

    namespace Create {
        unsigned shader(const char* source, int type) {
            unsigned shader = glCreateShader(type);

            int compiled = 0;

            glShaderSource(shader, 1, &source, NULL);
            glCompileShader(shader);
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

            if (!compiled) error(glGetShaderiv, glGetShaderInfoLog, shader, std::string(name(type)) + "_COMPILE_FAILURE");

            return shader;
        }

        unsigned program(std::vector<unsigned>&& shaders) {
            unsigned program = glCreateProgram();

            int linked = 0;

            for (unsigned& shader : shaders) {
                glAttachShader(program, shader);
            }

            glLinkProgram(program);
            glGetProgramiv(program, GL_LINK_STATUS, &linked);

            if (!linked) error(glGetProgramiv, glGetProgramInfoLog, program, "PROGRAM_LINK_FAILURE");

            // since the shaders are now compiled and linked with the program, we don't need the originals anymore
            for (unsigned& shader : shaders) {
                glDeleteShader(shader);
            }

            return program;
        }
    } // namespace Create

    void deactivate() { glUseProgram(0); }

    struct Object {
        unsigned program = 0;

      public:
        Object() {
            static const char* vertex = R"(#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

layout (location = 2) uniform mat4 model;
layout (location = 3) uniform mat4 view;
layout (location = 4) uniform mat4 projection;

out vec3 vertex_position;
out vec3 vertex_normal;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0f);

    // rotate and translate the position via the model
    vertex_position = vec3(model * vec4(position, 1.0f));

    // apply normal transformation matrix to adjust the normal w.r.t. object rotation
    vertex_normal = normalize(mat3(transpose(inverse(model))) * normal);
};)";

            static const char* fragment = R"(#version 460 core
layout (location = 5) uniform vec4 object_color;
layout (location = 6) uniform vec4 source_light;
layout (location = 7) uniform vec4 ambient_light;

layout (location = 8) uniform vec3 light_position;

in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 fragment_color;

void main() {
    // calculate diffuse w.r.t. the angle at which light hits the fragment
    float diffuse = max(dot(vertex_normal, normalize(light_position - vertex_position)), 0.0f);

    fragment_color = (ambient_light + (source_light * diffuse)) * object_color;
};)";

            program = Create::program({Create::shader(vertex, GL_VERTEX_SHADER),
                                       Create::shader(fragment, GL_FRAGMENT_SHADER)});
        }

        ~Object() { glDeleteProgram(program); }

        void activate() { glUseProgram(program); }

        void model(const Mat4& model) { glUniformMatrix4fv(2, 1, GL_FALSE, &model[0][0]); }
        void view(const Mat4& view) { glUniformMatrix4fv(3, 1, GL_FALSE, &view[0][0]); }
        void projection(const Mat4& projection) { glUniformMatrix4fv(4, 1, GL_FALSE, &projection[0][0]); }
        void objectColor(const Vec4& color) { glUniform4fv(5, 1, &color[0]); }
        void sourceLight(const Vec4& color) { glUniform4fv(6, 1, &color[0]); }
        void ambientLight(const Vec4& color) { glUniform4fv(7, 1, &color[0]); }
        void sourceLightPosition(const Vec3& position) { glUniform3fv(8, 1, &position[0]); }
    };
} // namespace D3::Sys::Shader