#pragma once

#include "SevenZip/SevenZipExtractor.h"
#include "SevenZip/SevenZipExtractorMemory.h"
#include "SevenZip/SevenZipLister.h"

#include <functional>
class SevenUnZip
{
public:
	static HRESULT UnZip(LPCTSTR lpsz7Zip, LPCTSTR lpszDir, std::function<VOID(ULONGLONG,ULONGLONG)> func)
	{
		SevenZip::SevenZipExtractor decompress;
		UnProgressCallback call(func);
		if ( !decompress.SetArchivePath(lpsz7Zip))
			return E_FAIL;

		return decompress.ExtractArchive(lpszDir, &call, NULL);
	}

public:
	class UnProgressCallback : public SevenZip::ProgressCallback
	{
	public:

		UnProgressCallback(std::function<VOID(ULONGLONG,ULONGLONG)> func)
		{
			m_CallBack = func;
			m_totalSize = 0;
		}

		virtual bool OnFileCount(unsigned int fileCount)
		{ 
			fileCount = fileCount;
			return true; 

		}

		virtual bool OnFileItems(std::vector<std::wstring>&itemNames, std::vector<unsigned __int64>&itemSizes)
		{
			for ( std::vector<unsigned __int64>::iterator it = itemSizes.begin() ; it != itemSizes.end() ; it++ )
				m_totalSize += *it;

			return true; 
		}

		virtual void OnRadio(unsigned __int64  inSize, unsigned __int64 outSize)
		{
			m_CallBack( m_totalSize, outSize);
		}

	private:
		unsigned __int64 m_totalSize;
		std::function<VOID(ULONGLONG,ULONGLONG)> m_CallBack;
	};
};