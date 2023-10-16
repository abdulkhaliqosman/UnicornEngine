#pragma once

#include <memory>

namespace unicore
{
	template<typename T> using UniquePtr = std::unique_ptr<T>;
	template<typename T> using SharedPtr = std::shared_ptr<T>;
	static constexpr size_t KiB = 1024;
	static constexpr size_t MiB = 1024*1024;

	namespace memory
	{
		inline void* Allocate(size_t size)
		{
			return new uint8_t[size]; //TODO: a real allocator
		}

		template<typename T>
		inline T* Construct(void* vptr, size_t count)
		{
			return new(vptr) T[count];
		}

		template<typename T>
		inline T* ConstructAndAllocate(size_t count)
		{
			void* buffer = Allocate(sizeof(T) * count);
			return Construct<T>(buffer, count);
		}

		inline void Deallocate(void* vptr)
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
		inline void DestroyAndDeallocate(T* tptr, size_t count)
		{
			Destroy(tptr, count);
			Deallocate(tptr);
		}
	}
}

#define ucNewArray(type, count) unicore::memory::ConstructAndAllocate<type>(count)
#define ucNew(type) ucNewArray(type, 1)

#define ucDeleteArray(ptr, count) unicore::memory::DestroyAndDeallocate(ptr, count); ptr = nullptr
#define ucDelete(ptr) ucDeleteArray(ptr, 1)
