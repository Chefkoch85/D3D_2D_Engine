#include "FileReader.h"

#include <fstream>

using namespace CKT;
using namespace std;

CFileReader::CFileReader()
{
}


CFileReader::~CFileReader()
{
	release();
}

<<<<<<< HEAD
HRESULT CFileReader::init(const TCHAR* file)
=======
CKT_RESULT CFileReader::init(const TCHAR* file)
>>>>>>> origin/master
{
	wfstream FileStream;
	FileStream.open(file, ios::in);

	if (!FileStream.is_open())
<<<<<<< HEAD
		return E_FAIL;

	FileStream.close();

	m_sFilename = wstring(file);
	return S_OK;
=======
	{
		CEngine::setErrorFile(file);
		return CR_FILENOTFOUND;
	}

	FileStream.close();

	m_sFilename = STRING(file);
	return CR_OK;
>>>>>>> origin/master
}

void CFileReader::release()
{
	for each (CFileTypedef::CAPTION_PAIR caption in m_EntryList)
	{
		caption.second.clear();
	}

	m_EntryList.clear();
}


<<<<<<< HEAD
HRESULT CFileReader::read()
=======
CKT_RESULT CFileReader::read()
>>>>>>> origin/master
{
	wfstream File;
	File.open(m_sFilename);
	
	if (!File.is_open())
<<<<<<< HEAD
		return E_FAIL;
=======
	{
		CEngine::setErrorFile(m_sFilename);
		return CR_FILENOTFOUND;
	}
>>>>>>> origin/master

	while (!File.eof())
	{
		TCHAR caLine[256] = { 0 };
		File.getline(caLine, 256);
		STRING sLine = STRING(caLine);
		if (sLine == L"" || (sLine[0] == '/' && sLine[1] == '/'))
			continue;

		if (sLine == L"[END]")
			break;

		// for debugging
#ifdef _DEBUG
		sLine += L"\n";
		OutputDebugString(sLine.c_str());
		sLine.pop_back();
#endif
		STRING sCaption = L"", sEntry = L"", sValue = L"";
		if (sLine[0] == '[' && sLine[sLine.length() - 1] == ']')
		{
			sCaption = sLine.substr(1,sLine.length() -2);
			CFileTypedef::ENTRY_MAP map;
			bool bUnderCaption = true;

			while (bUnderCaption)
			{
				// save last point befor read to restore if end of caption is reached
				streamoff iStremPosBeforRead = File.tellg();

				File.getline(caLine, 256);
				sLine = STRING(caLine);
				
				if (sLine[0] == '[')
				{
					bUnderCaption = false;
					// restore last point befor read to read the caption again
					File.seekg(iStremPosBeforRead, ios::beg);
					continue;
				}
				else if (File.eof())
<<<<<<< HEAD
					return E_FAIL;
=======
				{
					CEngine::setErrorFile(m_sFilename);
					return CR_FILEFORMAT;
				}
>>>>>>> origin/master
				else if (sLine.empty() || sLine[0] == '\n' || (sLine[0] == '/' && sLine[1] == '/'))
					continue;

				int iEqualPos = sLine.find_first_of('=');
				if (iEqualPos <= 0)
					continue;

				sEntry = sLine.substr(0, iEqualPos);
				
				sValue = sLine.substr(iEqualPos + 1, sLine.length() - (iEqualPos + 1));
				sValue = sValue.substr(1, sValue.length() - 2);
				map.insert(CFileTypedef::ENTRY_PAIR(sEntry, sValue));
			}

			m_EntryList.insert(CFileTypedef::CAPTION_PAIR(sCaption, map));
		}
	}

	File.close();
	m_bReadAndParseDone = true;
<<<<<<< HEAD
	return S_OK;
=======
	return CR_OK;
>>>>>>> origin/master
}


STRING CFileReader::getEntryAsString(STRING entry, STRING caption)
{
	return m_EntryList[caption][entry];
}
int CFileReader::getEntryAsInt(STRING entry, STRING caption)
{
	return stoi(m_EntryList[caption][entry]);
}
float CFileReader::getEntryAsFloat(STRING entry, STRING caption)
{
	return stof(m_EntryList[caption][entry]);
}
bool CFileReader::getEntryAsBool(STRING entry, STRING caption)
{
	if (m_EntryList[caption][entry].compare(L"TRUE") == 0)
		return true;

	return false;

}
