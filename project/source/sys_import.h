#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "utl_require.h"

namespace {
    template <typename T>
    void print(const char* prepend, std::vector<T>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (i % 3 == 0) std::cout << prepend;

            std::cout << vec[i] << ' ';

            if (i % 3 == 2) std::cout << '\n';
        }
    }

    template <typename T>
    std::vector<T>& operator+=(std::vector<T>& vec, T mod) {
        for (int i = 0; i < vec.size(); i++) {
            vec[i] += mod;
        }
        return vec;
    }

    template <typename T>
    std::vector<T>& operator-=(std::vector<T>& vec, T mod) {
        for (int i = 0; i < vec.size(); i++) {
            vec[i] -= mod;
        }
        return vec;
    }
} // namespace

namespace D3::Sys::Import {
    namespace OBJ {
        namespace {
            bool value(char c) { return c >= '0' && c <= '9' || c == '-' || c == '.'; }

            void nextValue(std::istringstream& iss) {
                for (char c = iss.peek(); !iss.eof(); c = iss.peek()) {
                    if (value(c)) break;
                    iss.ignore(1, c);
                }
            }

            void skipValue(std::istringstream& iss) {
                for (char c = iss.peek(); !iss.eof(); c = iss.peek()) {
                    if (!value(c)) break;
                    iss.ignore(1, c);
                }
            }

            template <typename T>
            void parse_V_N_VI(const std::string& line, std::vector<T>& vec) {
                std::istringstream iss(line);

                for (int i = 0; !iss.eof() && i < 3; i++) {
                    nextValue(iss);

                    T val;
                    iss >> val;

                    vec.emplace_back(val);
                }
            }

            template <typename T>
            void parse_VI_NI(const std::string& line, std::vector<T>& vi, std::vector<T>& ni) {
                std::istringstream iss(line);

                for (int i = 0; !iss.eof() && i < 3; i++) {
                    for (int j = 0; !iss.eof() && j < 3; j++) {
                        nextValue(iss);

                        T val;
                        iss >> val;
                        vi.emplace_back(val);

                        nextValue(iss);

                        iss >> val;
                        ni.emplace_back(val);
                    }
                }
            }
        } // namespace

        template <typename Float, typename Uint>
        void load(const char* filePath, std::vector<Float>& v, std::vector<Float>& n, std::vector<Uint>& vi, std::vector<Uint>& ni) {
            struct Data {
                std::vector<Float> v;
                std::vector<Float> n;
                std::vector<Uint>  vi;
                std::vector<Uint>  ni;
            };

            static std::unordered_map<const char*, Data> cache;

            if (cache.contains(filePath)) {
                const auto& c = cache[filePath];

                v  = c.v;
                n  = c.n;
                vi = c.vi;
                ni = c.ni;

                return;
            }

            std::ifstream in(filePath);

            for (std::string line; std::getline(in, line);) {
                if (line.starts_with("v ")) {
                    parse_V_N_VI(line, v);
                } else if (line.starts_with("vn ")) {
                    parse_V_N_VI(line, n);
                } else if (line.starts_with("f ")) {
                    parse_VI_NI(line, vi, ni);
                }
            }

            in.close();

            // change 1-based indexing to 0-based
            vi -= static_cast<Uint>(1);
            ni -= static_cast<Uint>(1);

            cache[filePath] = Data{v, n, vi, ni};
        }
    } // namespace OBJ

    template <typename Float>
    void scale(std::vector<Float>& v, Float x, Float y, Float z) {
        for (int i = 0; i < v.size();) {
            v[i++] *= x;
            v[i++] *= y;
            v[i++] *= z;
        }
    }

    template <typename Float, typename Uint>
    std::vector<Float> interleave(const std::vector<Float>& v, const std::vector<Float>& n, const std::vector<Uint>& vi, const std::vector<Uint>& ni) {
        D3_UTL_REQUIRE(vi.size() == ni.size());

        std::vector<Float> v_n;
        v_n.reserve((vi.size() + ni.size()) * 3);

        for (int i = 0; i < vi.size(); i++) {
            for (int j = 0; j < 3; j++) {
                v_n.emplace_back(v[vi[i] * 3 + j]);
            }
            for (int j = 0; j < 3; j++) {
                v_n.emplace_back(n[ni[i] * 3 + j]);
            }
        }

        return v_n;
    }
} // namespace D3::Sys::Import