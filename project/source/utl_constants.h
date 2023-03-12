#pragma once

namespace D3::Utl::Constants {
    template <typename T> // https://www.wolframalpha.com/input?i=pi
    inline constexpr T PI = 3.1415926535897932384626433832795028841971693993751058209749445923;

    template <typename T>
    inline constexpr T QUARTER_PI = PI<double> / 4.0;

    template <typename T>
    inline constexpr T HALF_PI = PI<double> / 2.0;

    template <typename T>
    inline constexpr T TWO_THIRDS_PI = PI<double> * 2.0 / 3.0;

    template <typename T>
    inline constexpr T TWO_PI = PI<double> * 2.0;

    template <typename T> // https://www.wolframalpha.com/input?i=%282pi%29%2F360
    inline constexpr T DEGREES_TO_RADIANS_FACTOR = 0.017453292519943295769236907684886127134428718885417254560971914;

    template <typename T>
    inline constexpr T ONE_DEGREE_IN_RADIANS = 1.0 * DEGREES_TO_RADIANS_FACTOR<double>;

    template <typename T>
    inline constexpr T EIGHTY_NINE_DEGREES_IN_RADIANS = HALF_PI<double> - ONE_DEGREE_IN_RADIANS<double>;
} // namespace D3::Utl::Constants