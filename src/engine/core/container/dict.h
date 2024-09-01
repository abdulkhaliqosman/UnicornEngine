#pragma once

#include <unordered_map>

namespace Unicorn
{
    // TODO make a real container
    template <typename K, typename T> using Dict = std::unordered_map<K, T>;
}
