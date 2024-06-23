#pragma once

#include <unordered_map>

namespace unicore
{
    // TODO make a real container
    template <typename K, typename T> using Dict = std::unordered_map<K, T>;
}
