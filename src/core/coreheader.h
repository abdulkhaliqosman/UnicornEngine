#include <Windows.h>

#include <cassert>
#include <functional>

#include "core/core.h"

#include "core/memory/manager/memorymanager.h"
#include "core/thread/manager/threadmanager.h"
#include "core/windows/windowmanager/windowmanager.h"

#include "core/container/list.h"
#include "core/container/tuple.h"

#include "core/math/math.h"
#include "core/memory/memory.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

namespace uc
{
    using Vector4f = unicore::Vector4f;
    using Matrix4f = unicore::Matrix4f;
    using Transform = unicore::Transform;
    template <typename T> using List = unicore::List<T>;
}

