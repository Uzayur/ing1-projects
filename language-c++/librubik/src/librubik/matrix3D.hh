#pragma once

#include <array>

#include "vector3D.hh"

namespace rubik
{
    template <typename T>
    class Matrix3D
    {
    public:
        Matrix3D(std::array<std::array<T, 3>, 3> matrix)
            : matrix_(matrix)
        {}

        T at(int i, int j)
        {
            return matrix_[i][j];
        }

        Vector3D<T> operator*(const Vector3D<T>& v) const
        {
            Vector3D<T> result = Vector3D<int>{ 0, 0, 0 };
            for (auto i = 0; i < 3; ++i)
            {
                for (auto j = 0; j < 3; ++j)
                {
                    auto value = 0;
                    if (j == 0)
                        value += matrix_[i][j] * v.x;
                    if (j == 1)
                        value += matrix_[i][j] * v.y;
                    if (j == 2)
                        value += matrix_[i][j] * v.z;

                    if (i == 0)
                        result.x += value;
                    else if (i == 1)
                        result.y += value;
                    else
                        result.z += value;
                }
            }
            return result;
        }

        void transpose()
        {
            for (auto i = 0; i < 3; ++i)
            {
                for (auto j = i + 1; j < 3; ++j)
                {
                    auto tmp = matrix_[i][j];
                    matrix_[i][j] = matrix_[j][i];
                    matrix_[j][i] = tmp;
                }
            }
        }

    private:
        std::array<std::array<T, 3>, 3> matrix_;
    };
} // namespace rubik
