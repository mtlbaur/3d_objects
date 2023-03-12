#pragma once

#include <boost/test/included/unit_test.hpp>

#include <glm/glm.hpp>

#include "utl_test.h"
#include <utl_math_vec4.h>

using namespace D3::Utl::Math;

BOOST_AUTO_TEST_SUITE(utl_math_vec4)

BOOST_AUTO_TEST_CASE(dot) {
    using A = Vec4<float>;
    using B = glm::fvec4;

    A a1{12.5, -4.1, 3.6, -8.6};
    A a2{-6, 12.1, 5, 4.14};

    B b1 = copyVec4<A, B>(a1);
    B b2 = copyVec4<A, B>(a2);

    BOOST_TEST(a1.dot(a2) == glm::dot(b1, b2));
}

BOOST_AUTO_TEST_CASE(magnitude) {
    using A = Vec4<float>;
    using B = glm::fvec4;

    A a{12.5, -4.1, 3.6, -8.6};
    B b = copyVec4<A, B>(a);

    BOOST_TEST(a.mag() == glm::length(b));
}

BOOST_AUTO_TEST_CASE(normal, *boost::unit_test::tolerance(TOLERANCE<float>)) {
    using A = Vec4<float>;
    using B = glm::fvec4;

    A a{12.5, -4.1, 3.6, -8.6};
    B b = copyVec4<A, B>(a);

    a.normalized();
    b = glm::normalize(b);

    EQUAL_VEC4(a, b);
}

BOOST_AUTO_TEST_SUITE_END()