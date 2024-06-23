#include <Windows.h>
#include "filesystem.h"

VOID CALLBACK FileSystemFileIOCompletionRoutine(
	__in  DWORD dwErrorCode,
	__in  DWORD dwNumberOfBytesTransfered,
	__in  LPOVERLAPPED lpOverlapped)
{
	printf("Error code:\t%x\n", dwErrorCode);
	printf("Number of bytes:\t%x\n", dwNumberOfBytesTransfered);
	// g_BytesTransferred = dwNumberOfBytesTransfered;
}

namespace unicore
{
	void FileSystem::OpenFile(const TCHAR* path)
	{
		// assert m_file is nullptr

		LPCTSTR lpFileName = path;
		DWORD dwDesiredAccess = GENERIC_READ;
		DWORD dwShareMode = FILE_SHARE_READ;
		LPSECURITY_ATTRIBUTES lpSecurityAttributes = nullptr;
		DWORD dwCreationDisposition = OPEN_EXISTING;
		DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
		HANDLE hTemplateFile = nullptr;

		m_File = CreateFile(lpFileName, 
			dwDesiredAccess, dwShareMode, 
			lpSecurityAttributes, dwCreationDisposition, 
			dwFlagsAndAttributes, hTemplateFile);

		m_Offset = 0;

		m_Size = ::GetFileSize(m_File, NULL);
	}

	void FileSystem::CloseFile()
	{
		CloseHandle(m_File);

		m_File = nullptr;
	}

	void FileSystem::ReadBytes(char* buffer, uint32_t count)
	{
		DWORD bytesRead = 0;

		if (!ReadFile(m_File, buffer, count, &bytesRead, NULL))
		{
			// assert
		}

		m_Offset += count;
	}

	void FileSystem::Seek(int offset)
	{
		SetFilePointer(m_File, offset, NULL, FILE_BEGIN);
		m_Offset = offset;
	}
}