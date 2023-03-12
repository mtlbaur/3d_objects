#pragma once

#include <boost/test/included/unit_test.hpp>

#include <glm/glm.hpp>

#include "utl_test.h"
#include "utl_math_mat3.h"

using namespace D3::Utl::Math;

BOOST_AUTO_TEST_SUITE(utl_math_mat3)

BOOST_AUTO_TEST_CASE(mult_mat3) {
    using A = Mat3<int>;
    using B = glm::imat3x3;

    A a1{
        {1,  2, 3},
        {-1, 4, 1},
        {-5, 3, 1}
    };
    A a2{
        {-3, 31, -14},
        {3,  2,  1  },
        {-8, -2, 1  }
    };
    A a3{
        {141, 91,  -22},
        {24,  21,  4  },
        {31,  -15, -37}
    };

    B b1 = copyMat3<A, B>(a1);
    B b2 = copyMat3<A, B>(a2);
    B b3 = copyMat3<A, B>(a3);

    A ar = a1 * a2 * a3;
    B br = b1 * b2 * b3;

    EQUAL_MAT3(ar, br);

    a1 *= a1 * a2 * a3;
    b1 *= b1 * b2 * b3;

    EQUAL_MAT3(a1, b1);
}

BOOST_AUTO_TEST_CASE(mult_vec3) {
    using AM = Mat3<int>;
    using AV = Vec3<int>;
    using BM = glm::imat3x3;
    using BV = glm::ivec3;

    AM am{
        {1,  2, 3},
        {-1, 4, 1},
        {-5, 3, 1}
    };
    AV av{4, 31, -5};

    BM bm = copyMat3<AM, BM>(am);
    BV bv = copyVec3<AV, BV>(av);

    AV ar = am * av;
    BV br = bm * bv;

    EQUAL_VEC3(ar, br);
}

BOOST_AUTO_TEST_CASE(determinant) {
    using A = Mat3<float>;
    using B = glm::fmat3x3;

    A a{
        {1,  2, 3 },
        {-1, 4, 1 },
        {7,  1, -2}
    };
    B b = copyMat3<A, B>(a);

    BOOST_TEST(a.determinant() == glm::determinant(b));
}

BOOST_AUTO_TEST_CASE(transpose) {
    using A = Mat3<float>;
    using B = glm::fmat3x3;

    A a{
        {1,  2, 3 },
        {-1, 4, 1 },
        {7,  1, -2}
    };
    B b = copyMat3<A, B>(a);

    EQUAL_MAT3(a.transpose(), glm::transpose(b));
}

BOOST_AUTO_TEST_CASE(inverse, *boost::unit_test::tolerance(TOLERANCE<float>)) {
    using A = Mat3<float>;
    using B = glm::fmat3x3;

    A a{
        {1,  2, 3 },
        {-1, 4, 1 },
        {7,  1, -2}
    };
    B b = copyMat3<A, B>(a);

    EQUAL_MAT3(a.inverse(), glm::inverse(b));
}

BOOST_AUTO_TEST_SUITE_END()