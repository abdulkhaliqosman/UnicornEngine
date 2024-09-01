#pragma once

#include <fstream> //TODO: Don't use fstream
#include <stdio.h>

namespace Unicorn
{
	using FilePtr = void*;

	class FileSystem
	{
	public:
		void OpenFile(const TCHAR* path);
		void CloseFile();

		void ReadBytes(char* buffer, uint32_t count);
		inline void ReadBytes(uint8_t* buffer, int count) { ReadBytes(reinterpret_cast<char*>(buffer), count); }
		inline void ReadUInt8(uint8_t& data) { ReadBytes(reinterpret_cast<char*>(&data), 1); }
		inline void ReadInt16(int16_t& data) { ReadBytes(reinterpret_cast<char*>(&data), 2); }
		inline void ReadInt32(int32_t& data) { ReadBytes(reinterpret_cast<char*>(&data), 4); }
		inline void ReadUInt32(uint32_t& data) { ReadBytes(reinterpret_cast<char*>(&data), 4); }
		inline void ReadFloat(float& data) { ReadBytes(reinterpret_cast<char*>(&data), 4); }
		inline void ReadUInt64(uint64_t& data) { ReadBytes(reinterpret_cast<char*>(&data), 8); }
		inline void ReadInt64(int64_t& data) { ReadBytes(reinterpret_cast<char*>(&data), 8); }
		inline void ReadDouble(double& data) { ReadBytes(reinterpret_cast<char*>(&data), 8); }

		void Seek(int offset);

		int GetOffset() const { return m_Offset; }
		int GetSize() const { return m_Size; }
	private:
		FilePtr m_File = nullptr;
		int m_Offset = 0;
		int m_Size = 0; // todo
	};
}
