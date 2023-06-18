
#include <WinSock2.h>
#include <Windows.h>

#include <cassert>
#include <functional>

#include "core/network/client/networkclient.h"
#include "core/network/server/networkserver.h"
#include "core/network/thread/networkthread.h"

#include "core/memory/manager/memorymanager.h"
#include "core/thread/manager/threadmanager.h"
#include "core/input/inputmanager.h"

#include "core/container/list.h"
#include "core/container/tuple.h"

#include "core/math/math.h"
#include "core/memory/memory.h"

#include "core/serializer/serializer.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

namespace ucc
{
    using Vector4f = unicore::Vector4f;
    using Matrix4f = unicore::Matrix4f;
    using Transform = unicore::Transform;
    template <typename T> using List = unicore::List<T>;

    using ISerializer = unicore::ISerializer;

    using NetworkServer = unicore::NetworkServer;
    using NetworkClient = unicore::NetworkClient;
    using NetworkThread = unicore::NetworkThread;

    using MemoryManager = unicore::MemoryManager;
    using ThreadManager = unicore::ThreadManager;
    using InputManager = unicore::InputManager;
}

