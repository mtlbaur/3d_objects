#pragma once

#include <boost/test/included/unit_test.hpp>

#include <glm/glm.hpp>

#include "utl_test.h"
#include "utl_math_mat4.h"

using namespace D3::Utl::Math;

BOOST_AUTO_TEST_SUITE(utl_math_mat4)

BOOST_AUTO_TEST_CASE(mult_mat4) {
    using A = Mat4<int>;
    using B = glm::imat4x4;

    A a1{
        {1,  2, 3,  4 },
        {-1, 4, 1,  5 },
        {-5, 3, 1,  5 },
        {7,  1, -2, -8}
    };
    A a2{
        {-3, 31, -14, 15 },
        {3,  2,  1,   4  },
        {-8, -2, 1,   6  },
        {7,  1,  -6,  -16}
    };
    A a3{
        {141, 91,  -22, -47},
        {24,  21,  4,   -5 },
        {31,  -15, -37, -85},
        {-76, -16, 48,  131}
    };

    B b1 = copyMat4<A, B>(a1);
    B b2 = copyMat4<A, B>(a2);
    B b3 = copyMat4<A, B>(a3);

    A ar = a1 * a2 * a3;
    B br = b1 * b2 * b3;

    EQUAL_MAT4(ar, br);

    a1 *= a1 * a2 * a3;
    b1 *= b1 * b2 * b3;

    EQUAL_MAT4(a1, b1);
}

BOOST_AUTO_TEST_CASE(mult_vec4) {
    using AM = Mat4<int>;
    using AV = Vec4<int>;
    using BM = glm::imat4x4;
    using BV = glm::ivec4;

    AM am{
        {1,  2, 3,  4 },
        {-1, 4, 1,  5 },
        {-5, 3, 1,  5 },
        {7,  1, -2, -8}
    };
    AV av{4, 31, -5, -8};

    BM bm = copyMat4<AM, BM>(am);
    BV bv = copyVec4<AV, BV>(av);

    AV ar = am * av;
    BV br = bm * bv;

    EQUAL_VEC4(ar, br);
}

BOOST_AUTO_TEST_CASE(determinant) {
    using A = Mat4<float>;
    using B = glm::fmat4x4;

    A a{
        {1,  2, 3,  4 },
        {-1, 4, 1,  5 },
        {-5, 3, 1,  5 },
        {7,  1, -2, -8}
    };
    B b = copyMat4<A, B>(a);

    BOOST_TEST(a.determinant() == glm::determinant(b));
}

BOOST_AUTO_TEST_CASE(transpose) {
    using A = Mat4<float>;
    using B = glm::fmat4x4;

    A a{
        {1,  2, 3,  4 },
        {-1, 4, 1,  5 },
        {-5, 3, 1,  5 },
        {7,  1, -2, -8}
    };
    B b = copyMat4<A, B>(a);

    EQUAL_MAT4(a.transpose(), glm::transpose(b));
}

BOOST_AUTO_TEST_CASE(inverse, *boost::unit_test::tolerance(0.000001f)) {
    using A = Mat4<float>;
    using B = glm::fmat4x4;

    A a{
        {1,  2, 3,  4 },
        {-1, 4, 1,  5 },
        {-5, 3, 1,  5 },
        {7,  1, -2, -8}
    };
    B b = copyMat4<A, B>(a);

    EQUAL_MAT4(a.inverse(), glm::inverse(b));
}

BOOST_AUTO_TEST_SUITE_END()