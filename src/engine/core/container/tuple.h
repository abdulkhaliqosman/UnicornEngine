#pragma once

#include <array>

namespace unicore
{
    // TODO make a real container
    template <typename T, size_t size> using Tuple = std::array<T, size>;
}
