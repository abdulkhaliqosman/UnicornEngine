
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
#include "core/gameobject/gameobject.h"

#include "core/math/math.h"
#include "core/memory/memory.h"

#include "core/serializer/serializer.h"
#include "core/filesystem/filesystem.h"


namespace ucc = unicore;
// {
//     using Vector4f = unicore::Vector4f;
//     using Vector2f = unicore::Vector2f;
//     using Vector4uc = unicore::Vector4uc;
//     using Matrix4x4f = unicore::Matrix4x4f;
//     using Quaternion4f = unicore::Quaternion4f;
//     using Transform = unicore::Transform;
//     template <typename T> using List = unicore::List<T>;
// 
//     using ISerializer = unicore::ISerializer;
// 
//     using NetworkServer = unicore::NetworkServer;
//     using NetworkClient = unicore::NetworkClient;
//     using NetworkThread = unicore::NetworkThread;
// 
//     using MemoryManager = unicore::MemoryManager;
//     using ThreadManager = unicore::ThreadManager;
//     using InputManager = unicore::InputManager;
// 
//     using GameObject = unicore::GameObject;
//     using FileSystem = unicore::FileSystem;
// }

