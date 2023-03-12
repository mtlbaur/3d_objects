#pragma once

#include <boost/test/included/unit_test.hpp>

#include <glm/glm.hpp>

#include "utl_test.h"
#include <utl_math_vec3.h>

using namespace D3::Utl::Math;

BOOST_AUTO_TEST_SUITE(utl_math_vec3)

BOOST_AUTO_TEST_CASE(dot) {
    using A = Vec3<float>;
    using B = glm::fvec3;

    A a1{12.5, -4.1, 3.6};
    A a2{-6, 12.1, 5};

    B b1 = copyVec3<A, B>(a1);
    B b2 = copyVec3<A, B>(a2);

    BOOST_TEST(a1.dot(a2) == glm::dot(b1, b2));
}

BOOST_AUTO_TEST_CASE(cross) {
    using A = Vec3<float>;
    using B = glm::fvec3;

    A a1{12.5, -4.1, 3.6};
    A a2{-6, 12.1, 5};

    B b1 = copyVec3<A, B>(a1);
    B b2 = copyVec3<A, B>(a2);

    a1.crossed(a2);
    b1 = glm::cross(b1, b2);

    EQUAL_VEC3(a1, b1);
}

BOOST_AUTO_TEST_CASE(magnitude) {
    using A = Vec3<float>;
    using B = glm::fvec3;

    A a{12.5, -4.1, 3.6};
    B b = copyVec3<A, B>(a);

    BOOST_TEST(a.mag() == glm::length(b));
}

BOOST_AUTO_TEST_CASE(normal, *boost::unit_test::tolerance(TOLERANCE<float>)) {
    using A = Vec3<float>;
    using B = glm::fvec3;

    A a{12.5, -4.1, 3.6};
    B b = copyVec3<A, B>(a);

    a.normalized();
    b = glm::normalize(b);

    EQUAL_VEC3(a, b);
}

BOOST_AUTO_TEST_SUITE_END()