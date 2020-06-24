#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "common.h"
#include "Tuple.h"

#include <array>
#include <optional>
#include <stdexcept>

// minor() is a pre-defined GCC macro we don't care about, so avoid clashing with it.
#undef minor

namespace raytracer {

template <typename T, size_t R, size_t C>
class Matrix {
public:
    using element_type = T;
    using row_type = std::array<T, C>;
    using matrix_type = std::array<row_type, R>;
private:
    matrix_type elements;

public:
    constexpr bool is_square() const {
        return R == C;
    }

    constexpr Matrix() { }
    constexpr Matrix(const T(&init)[R][C]) {
        int row_num = 0;
        for (auto& row : init) {
            std::copy(std::begin(row), std::end(row), elements[row_num++].begin());
        }
    }

    constexpr row_type& operator[](size_t i) { return elements[i]; }
    constexpr const row_type& operator[](size_t i) const { return elements[i]; }

    static constexpr size_t num_rows() { return R; }
    static constexpr size_t num_cols() { return C; }

    constexpr bool operator==(const Matrix& other) const {
        for (size_t i = 0; i < R; ++i) {
            if (!std::equal(elements[i].cbegin(), elements[i].cend(),
                            other.elements[i].cbegin(), other.elements[i].cend(),
                            float_equals<T, T>)) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        os << "Matrix(\n";
        for (size_t row = 0; row < R; ++row) {
            os << "\t";
            for (size_t col = 0; col < C; ++col) {
                os << m.elements[row][col];
                if (col != C-1) os << " | ";
            }
            os << "\n";
        }
        os << ")";
        return os;
    }

    template <size_t C2>
    constexpr auto operator*(const Matrix<T, C, C2>& other) const {
        Matrix<T, R, C2> result;
        for (size_t row = 0; row < R; ++row) {
            for (size_t col = 0; col < C2; ++col) {
                result[row][col] = 0;
                for (size_t k = 0; k < C; ++k) {
                    result[row][col] += elements[row][k] * other[k][col];
                }
            }
        }
        return result;
    }

    constexpr auto operator*(const Tuple<T, C>& other) const {
        Tuple<T, R> result;
        for (size_t row = 0; row < R; ++row) {
            result[row] = 0;
            for (size_t col = 0; col < C; ++col) {
                result[row] += elements[row][col] * other[col];
            }
        }
        return result;
    }

    constexpr auto transpose() const {
        Matrix<T, C, R> result;
        for (size_t row = 0; row < R; ++row) {
            for (size_t col = 0; col < C; ++col) {
                result[col][row] = elements[row][col];
            }
        }
        return result;
    }

    template <size_t R2 = R, size_t C2 = C, std::enable_if_t<R2 == C2>* = nullptr>
    constexpr auto determinant() const {
        if constexpr (R == 1) {
            return elements[0][0];
        } else if constexpr (R == 2) {
            return (elements[0][0] * elements[1][1]) - (elements[1][0] * elements[0][1]);
        } else {
            T result = 0.0;
            for (size_t col = 0; col < C; ++col) {
                result += elements[0][col] * cofactor(0, col);
            }
            return result;
        }
    }

    // Returns copy of matrix with specified row and column removed.
    template <size_t R2 = R, size_t C2 = C, std::enable_if_t<(R2 > 1) && (C2 > 1)>* = nullptr>
    constexpr auto submatrix(size_t target_row, size_t target_col) const {
        Matrix<T, R-1, C-1> result;
        size_t dst_row = 0;
        for (size_t src_row = 0; src_row < R; ++src_row) {
            if (src_row == target_row) continue;

            size_t dst_col = 0;
            for (size_t src_col = 0; src_col < C; ++src_col) {
                if (src_col == target_col) continue;

                result[dst_row][dst_col] = elements[src_row][src_col];
                ++dst_col;
            }

            ++dst_row;
        }
        return result;
    }

    constexpr auto minor(size_t row, size_t col) const {
        return submatrix(row, col).determinant();
    }

    constexpr auto cofactor(size_t row, size_t col) const {
        T sign = (row + col) % 2 ? -1 : 1;
        return sign * minor(row, col);
    }

    constexpr std::optional<Matrix<T, C, R>> inverse() const {
        auto det = determinant();
        if (det == 0) {
            return std::nullopt;
        } else {
            Matrix<T, C, R> result;
            for (size_t row = 0; row < R; ++row) {
                for (size_t col = 0; col < C; ++col) {
                    result[col][row] = cofactor(row, col) / det;
                }
            }
            return result;
        }
    }
};

using Matrix4 = Matrix<double, 4, 4>;

template <typename T, size_t N>
static constexpr Matrix<T, N, N> make_identity() {
    Matrix<T, N, N> m;
    for (size_t row = 0; row < N; ++row) {
        for (size_t col = 0; col < N; ++col) {
            m[row][col] = (row == col) ? 1 : 0;
        }
    }
    return m;
}

} // namespace raytracer

#endif // _MATRIX_H_
