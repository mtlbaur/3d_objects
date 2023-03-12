#pragma once

#include <vector>

#include "globals.h"

#include "sys_camera.h"
#include "sys_transform.h"
#include "sys_shader.h"
#include "sys_import.h"
#include "sys_mesh.h"
#include "sys_object.h"

#include "utl_math_mat4.h"

namespace D3::Sys {
    struct Renderer {
        using Mat4 = Utl::Math::Mat4<float>;

        Mat4 view;
        Mat4 projection;

        Shader::Object            object_shader;
        std::vector<Object<Mesh>> object_batch;

        int count = 0;

        Renderer(const Camera& camera) {
            view       = Transform::view(camera.pos, camera.target, camera.yAxis);
            projection = Transform::projection(cfg.display_xFOV, state.screenX, state.screenY, cfg.display_zNear, cfg.display_zFar);

            object_shader.activate();

            object_shader.view(view);
            object_shader.projection(projection);
            object_shader.sourceLight(cfg.shader_object_sourceLight);
            object_shader.ambientLight(cfg.shader_object_ambientLight);
            object_shader.sourceLightPosition(cfg.shader_object_sourceLightPosition);

            Shader::deactivate();
        }

        Renderer(const Camera& camera, int n) : Renderer(camera) { addRandom(n); }

        ~Renderer() { clear(); }

        void render(const Camera& camera) {
            if (state.update.view)
                view = Transform::view(camera.pos, camera.target, camera.yAxis);
            if (state.update.projection)
                projection = Transform::projection(cfg.display_xFOV, state.screenX, state.screenY, cfg.display_zNear, cfg.display_zFar);

            if (count > 0) {
                object_shader.activate();

                if (state.update.view)
                    object_shader.view(view);
                if (state.update.projection)
                    object_shader.projection(projection);
                if (state.update.sourceLight)
                    object_shader.sourceLight(cfg.shader_object_sourceLight);
                if (state.update.ambientLight)
                    object_shader.ambientLight(cfg.shader_object_ambientLight);
                if (state.update.sourceLightPosition)
                    object_shader.sourceLightPosition(cfg.shader_object_sourceLightPosition);

                for (auto& o : object_batch) {
                    o.update();
                    object_shader.model(Transform::model(o.pos, o.ang));
                    object_shader.objectColor(o.color);
                    o.mesh.draw();
                }

                Mesh::deactivate();

                Shader::deactivate();
            }
        }

        void addRandom(int num) {
            if (num < 1) return;

            std::vector<float>    v;
            std::vector<float>    n;
            std::vector<unsigned> vi;
            std::vector<unsigned> ni;

            for (int i = 0; i < num; i++) {
                v.clear();
                n.clear();
                vi.clear();
                ni.clear();

                object_batch.emplace_back(Object<Mesh>());
                auto& object = object_batch.back();

                switch (rng.I(0, 5)) {
                    case 0:
                        Import::OBJ::load("resources/cube.obj", v, n, vi, ni);
                        break;
                    case 1:
                        Import::OBJ::load("resources/sphere.obj", v, n, vi, ni);
                        break;
                    case 2:
                        Import::OBJ::load("resources/icosphere.obj", v, n, vi, ni);
                        break;
                    case 3:
                        Import::OBJ::load("resources/cylinder.obj", v, n, vi, ni);
                        break;
                    case 4:
                        Import::OBJ::load("resources/cone.obj", v, n, vi, ni);
                        break;
                    case 5:
                        Import::OBJ::load("resources/torus.obj", v, n, vi, ni);
                        break;
                    default:
                        abort();
                }

                Import::scale(v, object.radius, object.radius, object.radius);

                object.mesh.create(Import::interleave(v, n, vi, ni));
            }

            recount();
        }

        void remRandom(int n) {
            while (object_batch.size() > 0 && n > 0) {
                object_batch.back().mesh.destroy();
                object_batch.pop_back();

                n -= 1;
            }

            recount();
        }

        void clear() {
            while (object_batch.size() > 0) {
                object_batch.back().mesh.destroy();
                object_batch.pop_back();
            }

            recount();
        }

        void regen() {
            int tempCount = count;

            clear();
            addRandom(tempCount);
        }

        void recount() { count = object_batch.size(); }
    };
} // namespace D3::Sys