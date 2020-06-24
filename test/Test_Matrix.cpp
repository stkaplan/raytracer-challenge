#include "catch.hpp"
#include "Matrix.h"
#include "common.h"

using namespace raytracer;

TEST_CASE("Can construct matrix")
{
    Matrix4 m = {{
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5},
    }};

    STATIC_REQUIRE(std::is_same_v<decltype(m), Matrix<double, 4, 4>>);

    REQUIRE(m.num_rows() == 4);
    REQUIRE(m.num_cols() == 4);

    REQUIRE(float_equals(m[0][0], 1));
    REQUIRE(float_equals(m[0][3], 4));
    REQUIRE(float_equals(m[1][0], 5.5));
    REQUIRE(float_equals(m[1][2], 7.5));
    REQUIRE(float_equals(m[2][2], 11));
    REQUIRE(float_equals(m[3][0], 13.5));
    REQUIRE(float_equals(m[3][2], 15.5));
}

TEST_CASE("Can use 2x2 matrix")
{
    Matrix<double, 2, 2> m = {{ {-3, 5}, {1, -2.5} }};
    REQUIRE(m.num_rows() == 2);
    REQUIRE(m.num_cols() == 2);

    REQUIRE(float_equals(m[0][0], -3));
    REQUIRE(float_equals(m[0][1], 5));
    REQUIRE(float_equals(m[1][0], 1));
    REQUIRE(float_equals(m[1][1], -2.5));
}

TEST_CASE("Can use 3x3 matrix")
{
    Matrix<double, 3, 3> m = {{ {-3, 5, 0}, {1, -2, -7}, {0, 1, 1} }};
    REQUIRE(m.num_rows() == 3);
    REQUIRE(m.num_cols() == 3);

    REQUIRE(float_equals(m[0][0], -3));
    REQUIRE(float_equals(m[1][1], -2));
    REQUIRE(float_equals(m[2][2], 1));
}

TEST_CASE("Can construct non-square matrix")
{
    Matrix<double, 2, 3> m = {{ {1, 2, 3}, {4, 5, 6} }};
    REQUIRE(m.num_rows() == 2);
    REQUIRE(m.num_cols() == 3);
}

TEST_CASE("Matrix equality works")
{
    Matrix<double, 3, 2> a = {{ {1, 1.5}, {2, 2.5}, {3, 3.5} }};
    Matrix<double, 3, 2> b = {{ {1, 1.5}, {2, 2.5}, {3, 3.5} }};
    REQUIRE(a == b);

    b[1][1] -= 1e-5;
    REQUIRE(a == b);

    b[1][1] -= 2e-4;
    REQUIRE(a != b);
}

TEST_CASE("Matrix multiplication works for square matrices")
{
    Matrix4 a = {{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2},
    }};
    Matrix4 b = {{
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8},
    }};
    Matrix4 result = {{
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42},
    }};

    REQUIRE(a * b == result);
}

TEST_CASE("Matrix multiplication works for compatible rectangles")
{
    Matrix<double, 3, 2> a = {{
        {1, 2},
        {5, 6},
        {7, 8},
    }};
    Matrix<double, 2, 1> b = {{
        {-2},
        {1},
    }};
    Matrix<double, 3, 1> result = {{
        {0},
        {-4},
        {-6},
    }};

    REQUIRE(a * b == result);
}

TEST_CASE("Matrix can be multiplied by Tuple")
{
    Matrix4 m = {{
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1},
    }};

    Tuple4 t = {{1, 2, 3, 1}};
    Tuple4 result = {{18, 24, 33, 1}};

    REQUIRE(m * t == result);
}

TEST_CASE("Can transpose matrix")
{
    Matrix<double, 3, 4> m1 = {{
        {0, 9, 3, 0},
        {9, 8, 0, 8},
        {1, 8, 5, 3},
    }};

    Matrix<double, 4, 3> m2 = {{
        {0, 9, 1},
        {9, 8, 8},
        {3, 0, 5},
        {0, 8, 3},
    }};

    REQUIRE(m1.transpose() == m2);

    Matrix4 I = make_identity<double, 4>();
    REQUIRE(I.transpose() == I);
}

TEST_CASE("Determinant works for 2x2 matrix")
{
    Matrix<double, 2, 2> m = {{
        {1, 5},
        {-3, 2},
    }};

    REQUIRE(m.determinant() == 17);
}

TEST_CASE("Submatrix works for 3x3 matrix")
{
    Matrix<double, 3, 3> m = {{
        {1, 5, 0},
        {-3, 2, 7},
        {0, 6, -3},
    }};

    Matrix<double, 2, 2> sub = {{
        {-3, 2},
        {0, 6},
    }};

    REQUIRE(m.submatrix(0, 2) == sub);
}

TEST_CASE("Submatrix works for 4x4 matrix")
{
    Matrix<double, 4, 4> m = {{
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1},
    }};

    Matrix<double, 3, 3> sub = {{
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1},
    }};

    REQUIRE(m.submatrix(2, 1) == sub);
}

TEST_CASE("Minor works for 3x3 matrix")
{
    Matrix<double, 3, 3> m = {{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    }};

    REQUIRE(m.minor(1, 0) == 25);
}

TEST_CASE("Cofactor works for 3x3 matrix")
{
    Matrix<double, 3, 3> m = {{
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5},
    }};

    REQUIRE(m.minor(0, 0) == -12);
    REQUIRE(m.minor(1, 0) == 25);
}

TEST_CASE("Determinant works for 3x3 matrix")
{
    Matrix<double, 3, 3> m = {{
        {1, 2, 6},
        {-5, 8, -4},
        {2, 6, 4},
    }};

    REQUIRE(m.cofactor(0, 0) == 56);
    REQUIRE(m.cofactor(0, 1) == 12);
    REQUIRE(m.cofactor(0, 2) == -46);
    REQUIRE(m.determinant() == -196);
}

TEST_CASE("Determinant works for 4x4 matrix")
{
    Matrix<double, 4, 4> m = {{
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9},
    }};

    REQUIRE(m.cofactor(0, 0) == 690);
    REQUIRE(m.cofactor(0, 1) == 447);
    REQUIRE(m.cofactor(0, 2) == 210);
    REQUIRE(m.cofactor(0, 3) == 51);
    REQUIRE(m.determinant() == -4071);
}

TEST_CASE("Non-invertible matrix does not have inverse")
{
    Matrix<double, 4, 4> m = {{
        {-4, 2, -2, -3},
        {9, 6, 2, 6},
        {0, -5, 1, -5},
        {0, 0, 0, 0},
    }};

    REQUIRE(m.inverse() == std::nullopt);
}

TEST_CASE("Invertible matrix has correct inverse")
{
    Matrix<double, 4, 4> m = {{
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4},
    }};

    Matrix<double, 4, 4> inverse = {{
        {0.21805, 0.45113, 0.24060, -0.04511},
        {-0.80824, -1.45677, -0.44361, 0.52068},
        {-0.07895, -0.22368, -0.05263, 0.19737},
        {-0.52256, -0.81391, -0.30075, 0.30639},
    }};

    REQUIRE(m.determinant() == 532);
    REQUIRE(m.cofactor(2, 3) == -160);
    REQUIRE(m.cofactor(3, 2) == 105);
    REQUIRE(m.inverse().value() == inverse);

    Matrix<double, 4, 4> m2 = {{
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4},
    }};

    Matrix<double, 4, 4> inverse2 = {{
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692, 0.12308, 0.02564, 0.03077},
        {0.35897, 0.35897, 0.43590, 0.92308},
        {-0.69231, -0.69231, -0.76923, -1.9230},
    }};

    REQUIRE(m2.inverse().value() == inverse2);

    Matrix<double, 4, 4> m3 = {{
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2},
    }};

    Matrix<double, 4, 4> inverse3 = {{
        {-0.04074, -0.07778, 0.14444, -0.22222},
        {-0.07778, 0.03333, 0.36667, -0.33333},
        {-0.02901, -0.14630, -0.10926, 0.12963},
        {0.17778, 0.06667, -0.26667, 0.33333},
    }};

    REQUIRE(m3.inverse().value() == inverse3);
}

TEST_CASE("Matrix times its inverse equals identity matrix")
{
    Matrix<double, 4, 4> a = {{
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1},
    }};

    Matrix<double, 4, 4> b = {{
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5},
    }};

    auto c = a * b;
    auto i = make_identity<double, 4>();

    REQUIRE(c * b.inverse().value() == a);
    REQUIRE(a * a.inverse().value() == i);
    REQUIRE(b * b.inverse().value() == i);
}
