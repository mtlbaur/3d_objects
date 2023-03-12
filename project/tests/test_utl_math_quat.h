#pragma once

#include <boost/test/included/unit_test.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "utl_test.h"
#include "utl_math_quat.h"

using namespace D3::Utl::Math;

BOOST_AUTO_TEST_SUITE(utl_math_quat)

BOOST_AUTO_TEST_CASE(init) {
    using A = D3::Utl::Math::Quat<float>;
    using B = glm::fquat;

    A a{7.5, -5.2, -7.1, 4.5};
    B b = copyQuat<A, B>(a);

    EQUAL_QUAT(a, b);
}

BOOST_AUTO_TEST_CASE(mult_quat, *boost::unit_test::tolerance(0.01f)) {
    using A = D3::Utl::Math::Quat<float>;
    using B = glm::fquat;

    A a1{7.5, -5.2, -7.1, 4.5};
    A a2{6.1, 5.3, -9.2, -4.4};
    A a3{-6.6, -3.2, 2.5, 8.1};

    B b1 = copyQuat<A, B>(a1);
    B b2 = copyQuat<A, B>(a2);
    B b3 = copyQuat<A, B>(a3);

    A ar = a1 * a2 * a3;
    B br = b1 * b2 * b3;

    EQUAL_QUAT(ar, br);
}

BOOST_AUTO_TEST_CASE(magnitude) {
    using A = D3::Utl::Math::Quat<float>;
    using B = glm::fquat;

    A a{7.5, -5.2, -7.1, 4.5};
    B b = copyQuat<A, B>(a);

    BOOST_TEST(a.mag() == glm::length(b));
}

BOOST_AUTO_TEST_CASE(normal, *boost::unit_test::tolerance(0.000001f)) {
    using A = D3::Utl::Math::Quat<float>;
    using B = glm::fquat;

    A a{7.5, -5.2, -7.1, 4.5};
    B b = copyQuat<A, B>(a);

    a.normalized();
    b = glm::normalize(b);

    EQUAL_QUAT(a, b);
}

BOOST_AUTO_TEST_CASE(conjugate) {
    using A = D3::Utl::Math::Quat<float>;
    using B = glm::fquat;

    A a{7.5, -5.2, -7.1, 4.5};
    B b = copyQuat<A, B>(a);

    a.conjugated();
    b = glm::conjugate(b);

    EQUAL_QUAT(a, b);
}

BOOST_AUTO_TEST_CASE(euler_axis_angle) {
    using A      = D3::Utl::Math::Quat<float>;
    using B      = glm::fquat;
    using A_Vec3 = D3::Utl::Math::Vec3<float>;
    using B_Vec3 = glm::fvec3;

    float radians = 2.15f;

    A a = A::eulerAxisAngle({1.0f, 0.0f, 0.0f}, radians);
    B b = B({radians, 0.0f, 0.0f});

    EQUAL_QUAT(a, b);
}

BOOST_AUTO_TEST_CASE(euler_angles) {
    using A      = D3::Utl::Math::Quat<float>;
    using B      = glm::fquat;
    using A_Vec3 = D3::Utl::Math::Vec3<float>;
    using B_Vec3 = glm::fvec3;

    A_Vec3 a_ang{2.15, -4.6, 1.5};
    B_Vec3 b_ang = copyVec3<A_Vec3, B_Vec3>(a_ang);

    A a = A::eulerAngles(a_ang);
    B b = B(b_ang);

    EQUAL_QUAT(a, b);
}

BOOST_AUTO_TEST_CASE(euler_angles_vs_euler_axis_angle_mult, *boost::unit_test::tolerance(0.000001f)) {
    using A      = D3::Utl::Math::Quat<float>;
    using B      = glm::fquat;
    using A_Vec3 = D3::Utl::Math::Vec3<float>;
    using B_Vec3 = glm::fvec3;

    A_Vec3 a_ang{2.15, -4.6, 1.5};
    B_Vec3 b_ang = copyVec3<A_Vec3, B_Vec3>(a_ang);

    A a_euler_angles = A::eulerAngles(a_ang);
    B b_euler_angles = B(b_ang);

    A a_euler_axis_angle_mult = A::eulerAxisAngle({0.0f, 0.0f, 1.0f}, a_ang[2]) *
                                A::eulerAxisAngle({0.0f, 1.0f, 0.0f}, a_ang[1]) * A::eulerAxisAngle({1.0f, 0.0f, 0.0f}, a_ang[0]);
    B b_euler_axis_angle_mult = B({0.0f, 0.0f, b_ang[2]}) *
                                B({0.0f, b_ang[1], 0.0f}) *
                                B({b_ang[0], 0.0f, 0.0f});

    EQUAL_QUAT(a_euler_angles, a_euler_axis_angle_mult);
    EQUAL_QUAT(a_euler_angles, b_euler_axis_angle_mult);
    EQUAL_QUAT(b_euler_angles, a_euler_axis_angle_mult);
    EQUAL_QUAT(b_euler_angles, b_euler_axis_angle_mult);
}

BOOST_AUTO_TEST_CASE(rotation_matrix_quat) {
    using A      = D3::Utl::Math::Quat<float>;
    using B      = glm::fquat;
    using A_Mat4 = D3::Utl::Math::Mat4<float>;
    using B_Mat4 = glm::fmat4x4;

    A a{7.5, -5.2, -7.1, 4.5};
    B b = copyQuat<A, B>(a);

    A_Mat4 amr = A::rotationMatrix(a);
    B_Mat4 bmr = glm::mat4_cast(b);

    EQUAL_MAT4(amr, bmr);
}

BOOST_AUTO_TEST_CASE(rotation_matrix_vec) {
    using A      = D3::Utl::Math::Quat<float>;
    using B      = glm::fquat;
    using A_Vec3 = D3::Utl::Math::Vec3<float>;
    using B_Vec3 = glm::fvec3;
    using A_Mat4 = D3::Utl::Math::Mat4<float>;
    using B_Mat4 = glm::fmat4x4;

    A_Vec3 a{7.5, -5.2, -7.1};
    B_Vec3 b = copyVec3<A_Vec3, B_Vec3>(a);

    A_Mat4 amr = A::rotationMatrix(a);
    B_Mat4 bmr = glm::mat4_cast(B(b));

    EQUAL_MAT4(amr, bmr);
}

BOOST_AUTO_TEST_SUITE_END()