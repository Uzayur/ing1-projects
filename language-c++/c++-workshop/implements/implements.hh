#pragma once

template <typename T, typename U = T>
concept impl_basic_op = std::is_arithmetic_v<T> and std::is_arithmetic_v<U>;

template <typename T, typename U = T>
concept impl_modulo = requires(T a, U b)
{
    a % b;
};

template <typename T, typename U = T>
concept impl_bitwise_op =
    std::numeric_limits<T>::is_integer and std::numeric_limits<U>::is_integer;

template <typename T, typename U = T>
concept impl_arith_op =
    impl_basic_op<T, U> and impl_modulo<T, U> and impl_bitwise_op<T, U>;
