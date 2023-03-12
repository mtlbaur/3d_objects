#pragma once

#include <chrono>
#include <random>

namespace D3::Utl {
    struct RNG {
        using UDU = std::uniform_int_distribution<unsigned>;
        using UDI = std::uniform_int_distribution<int>;
        using UDD = std::uniform_real_distribution<double>;
        using UDF = std::uniform_real_distribution<float>;

        std::mt19937_64 mt;

        RNG() { mt.seed(std::chrono::system_clock::now().time_since_epoch().count()); }

        unsigned U(unsigned l, unsigned u) { return UDU(l, u)(mt); }
        int      I(int l, int u) { return UDI(l, u)(mt); }
        float    F(float l, float u) { return UDF(l, u)(mt); }
        double   D(double l, double u) { return UDD(l, u)(mt); }
        int      IN(int l, int u) { return N(UDI(l, u)(mt)); }
        float    FN(float l, float u) { return N(UDF(l, u)(mt)); }
        double   DN(double l, double u) { return N(UDD(l, u)(mt)); }

        template <typename T>
        T N(T v) { return (UDI(0, 1)(mt) ? -v : v); }
    };
} // namespace D3::Utl