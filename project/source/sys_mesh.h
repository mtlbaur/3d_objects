#pragma once

#include <glad/gl.h>

#include "utl_require.h"

namespace D3::Sys {
    struct Mesh {
        bool exists = false;

        unsigned v_a = 0;

        unsigned v_n_buffer   = 0;
        unsigned v_n_size     = 0;
        unsigned v_n_bytes    = 0;
        unsigned v_n_vertices = 0;

        void create(const std::vector<float>& v_n) {
            D3_UTL_REQUIRE(!exists);

            v_n_size     = v_n.size();
            v_n_bytes    = v_n_size * sizeof(float);
            v_n_vertices = v_n_size / 2u;

            glGenBuffers(1, &v_n_buffer);
            glGenVertexArrays(1, &v_a);

            glBindVertexArray(v_a);

            glBindBuffer(GL_ARRAY_BUFFER, v_n_buffer);
            glBufferData(GL_ARRAY_BUFFER, v_n_bytes, v_n.data(), GL_STATIC_DRAW);

            GLint bindingindex = 0;

            glBindVertexBuffer(bindingindex, v_n_buffer, 0, 6 * sizeof(float));

            glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexAttribBinding(0, bindingindex);
            glEnableVertexAttribArray(0);

            glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
            glVertexAttribBinding(1, bindingindex);
            glEnableVertexAttribArray(1);

            glBindVertexArray(0);

            exists = true;
        }

        void destroy() {
            D3_UTL_REQUIRE(exists);

            glDeleteVertexArrays(1, &v_a);
            glDeleteBuffers(1, &v_n_buffer);

            exists = false;
        }

        void draw() {
            glBindVertexArray(v_a);
            glDrawArrays(GL_TRIANGLES, 0, v_n_vertices);
        }

        static void deactivate() { glBindVertexArray(0); }
    };
} // namespace D3::Sys