#pragma once

#include <memory>
#include "core/core/core.h"

namespace unicore
{
	template<typename T> using UniquePtr = std::unique_ptr<T>;
	template<typename T> using SharedPtr = std::shared_ptr<T>;
	static constexpr size_t KiB = 1024;
	static constexpr size_t MiB = 1024*1024;

	namespace memory
	{
		inline void* Allocate(Core& core, size_t size)
		{
			return new uint8_t[size]; //TODO: a real allocator
		}

		template<typename T>
		inline T* Construct(void* vptr, size_t count)
		{
			return new(vptr) T[count];
		}

		template<typename T>
		inline T* ConstructAndAllocate(Core& core, size_t count)
		{
			void* buffer = Allocate(core, sizeof(T) * count);
			return Construct<T>(buffer, count);
		}

		inline void Deallocate(Core& core, void* vptr)
		{
			delete[] static_cast<uint8_t*>(vptr); //TODO: a real allocator
		}

		template<typename T>
		inline void Destroy(T* tptr, size_t count)
		{
			for (size_t i = 0; i < count; ++i)
			{
				(tptr++)->~T();
			}
		}

		template<typename T>
		inline void DestroyAndDeallocate(Core& core, T* tptr, size_t count)
		{
			Destroy(tptr, count);
			Deallocate(core, tptr);
		}
	}
}

#define ucNewArray(core, type, count) unicore::memory::ConstructAndAllocate<type>(core, count)
#define ucNew(core, type) NewArray(core, type, 1)

#define ucDeleteArray(core, ptr, count) unicore::memory::DestroyAndDeallocate(core, ptr, count)
#define ucDelete(core, ptr) DeleteArray(core, ptr, 1)
