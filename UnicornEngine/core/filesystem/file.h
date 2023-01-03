#pragma once

#include <fstream> //TODO: Don't use fstream
#include <stdio.h>

namespace uni
{
	template<typename DataT>
	class FileT
	{
	public:
		FileT(const char* path);
		const DataT* GetData() const;
	private:

		DataT* m_Data;
		size_t size;
	};

	using File = FileT<char>;

	template<typename DataT>
	FileT<DataT>::FileT(const char* path)
	{
		MY_PRINTF(L"%S\n", path);
	}

	template<typename DataT>
	const DataT* FileT<DataT>::GetData() const
	{

	}
}