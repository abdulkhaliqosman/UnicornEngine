
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
#include "core/filesystem/filesystem.h"

#include "core/scene/scene.h"
#include "core/entity/entity.h"
#include "core/component/component.h"


namespace ucc = unicore;
