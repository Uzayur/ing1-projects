#pragma once

template <typename T>
struct is_numerical
{
    static const bool value = false;
};

template <>
struct is_numerical<int>
{
    static const bool value = true;
};

template <>
struct is_numerical<char>
{
    static const bool value = true;
};

template <>
struct is_numerical<float>
{
    static const bool value = true;
};
