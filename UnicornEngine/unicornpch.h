#pragma once

#include <cassert>

#include "core/math/vector4f.h"

// define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define MY_PRINTF(...) {wchar_t cad[512]; swprintf_s(cad, __VA_ARGS__);  OutputDebugString(cad);}