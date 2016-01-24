#include "FileWriter.h"

#include <fstream>
#include <vector>

using namespace CKT;
using namespace std;

CFileWriter::CFileWriter() 
	:
	m_EntryList(_DUMMYLIST)
{
}


CFileWriter::~CFileWriter()
{
	release();
}

<<<<<<< HEAD
HRESULT CKT::CFileWriter::init(TCHAR * file, bool newFile)
=======
CKT_RESULT CKT::CFileWriter::init(TCHAR * file, bool newFile)
>>>>>>> origin/master
{
	fstream File;

	if (newFile)
	{
		File.open(file, ios::out);
		File.close();
	}

	File.open(file, ios::in);

	if (!File.is_open())
<<<<<<< HEAD
		return E_FAIL;

	File.close();
	m_sFilename = file;
	return S_OK;
}

HRESULT CKT::CFileWriter::init(TCHAR * file, CFileTypedef::CAPTION_MAP& entryList)
=======
		return CR_FILENOTFOUND;

	File.close();
	m_sFilename = file;
	return CR_OK;
}

CKT_RESULT CKT::CFileWriter::init(TCHAR * file, CFileTypedef::CAPTION_MAP& entryList)
>>>>>>> origin/master
{
	m_EntryList = entryList;
	return init(file, false);
}

<<<<<<< HEAD
HRESULT CKT::CFileWriter::init(TCHAR * file, CFileTypedef::CAPTION_MAP& entryList, bool newfile)
=======
CKT_RESULT CKT::CFileWriter::init(TCHAR * file, CFileTypedef::CAPTION_MAP& entryList, bool newfile)
>>>>>>> origin/master
{
	m_EntryList = entryList;
	return init(file, newfile);
}

void CKT::CFileWriter::release()
{
	for each (CFileTypedef::CAPTION_PAIR caption in m_EntryList)
	{
		caption.second.clear();
	}

	m_EntryList.clear();
}

<<<<<<< HEAD
HRESULT CKT::CFileWriter::write(STRING caption, STRING entry, STRING value)
=======
CKT_RESULT CKT::CFileWriter::write(STRING caption, STRING entry, STRING value)
>>>>>>> origin/master
{
	if (m_EntryList.find(caption) != m_EntryList.end())
	{
		if (m_EntryList[caption].find(entry) != m_EntryList[caption].end())
		{
			if (m_EntryList[caption][entry] == value)
<<<<<<< HEAD
				return S_OK;
=======
				return CR_OK;
>>>>>>> origin/master

			CFileTypedef::ENTRY_PAIR ep = CFileTypedef::ENTRY_PAIR(entry, value);

			if (m_NewEntryList.find(caption) == m_NewEntryList.end())
			{
				CFileTypedef::ENTRY_MAP em;
				em.insert(ep);
				CFileTypedef::CAPTION_PAIR cp = CFileTypedef::CAPTION_PAIR(caption, em);
				m_NewEntryList.insert(cp);
			}
			else
			{
				m_NewEntryList[caption].insert(ep);
			}

			m_EntryList[caption][entry] = value;

			m_iChangedEntrys++;
<<<<<<< HEAD
			return S_OK;
		}
	}

	return E_FAIL;
}

HRESULT CKT::CFileWriter::write(STRING caption, STRING entry, int value)
=======
			return CR_OK;
		}
	}

	return CR_INDEXNOTFOUNT;
}

CKT_RESULT CKT::CFileWriter::write(STRING caption, STRING entry, int value)
>>>>>>> origin/master
{
	return write(caption, entry, to_wstring(value));
}

<<<<<<< HEAD
HRESULT CKT::CFileWriter::write(STRING caption, STRING entry, float value)
=======
CKT_RESULT CKT::CFileWriter::write(STRING caption, STRING entry, float value)
>>>>>>> origin/master
{
	return write(caption, entry, to_wstring(value));
}

<<<<<<< HEAD
HRESULT CKT::CFileWriter::write(STRING caption, STRING entry, bool value)
=======
CKT_RESULT CKT::CFileWriter::write(STRING caption, STRING entry, bool value)
>>>>>>> origin/master
{
	return write(caption, entry, (STRING)(value ? L"TRUE" : L"FALSE"));
}

<<<<<<< HEAD
HRESULT CKT::CFileWriter::flush()
=======
CKT_RESULT CKT::CFileWriter::flush()
>>>>>>> origin/master
{
	vector<STRING> FileList = vector<STRING>();

	if (m_iChangedEntrys <= 0)
<<<<<<< HEAD
		return S_OK;
=======
		return CR_OK;
>>>>>>> origin/master

	wfstream File;
	File.open(m_sFilename, ios::in);

	if (!File.is_open())
<<<<<<< HEAD
		return E_FAIL;
=======
		return CR_FILENOTFOUND;
>>>>>>> origin/master

	while (!File.eof())
	{
		TCHAR caLine[256] = { 0 };
		File.getline(caLine, 256);
		STRING sLine = STRING(caLine);
		FileList.push_back(sLine);
	}

	File.close();

	for (int i = 0; i < FileList.size(); i++)
	{
		STRING sLine = FileList[i];

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
			sCaption = sLine.substr(1, sLine.length() - 2);

			for each(CFileTypedef::CAPTION_PAIR caption in m_NewEntryList)
			{
				if (m_iChangedEntrys <= 0)
					break;

				if (sCaption == caption.first)
				{
					bool bUnderCaption = true;

					while (bUnderCaption)
					{
						i++;
						sLine = FileList[i];

						if (sLine[0] == '[')
						{
							bUnderCaption = false;
							i--;
							continue;
						}
						else if (sLine.empty() || sLine[0] == '\n' || (sLine[0] == '/' && sLine[1] == '/'))
							continue;

						int iEqualPos = sLine.find_first_of('=');
						if (iEqualPos <= 0)
							continue;

						sEntry = sLine.substr(0, iEqualPos);

						for each (CFileTypedef::ENTRY_PAIR entry in caption.second)
						{
							if (sEntry == entry.first)
							{
								m_iChangedEntrys--;
								STRING str = entry.first + L"=\"" + entry.second + L"\"";
								FileList[i] = str;
								m_NewEntryList[caption.first].erase(entry.first);
								break;
							}
						}

						if (m_iChangedEntrys <= 0)
							break;
					}
				}
			}	// for each

			m_NewEntryList.erase(sCaption);
		}
	}

	File.open(m_sFilename, ios::out);

	if (!File.is_open())
<<<<<<< HEAD
		return E_FAIL;
=======
		return CR_FILENOTFOUND;
>>>>>>> origin/master

	for each (auto line in FileList)
	{
		line = line + L"\n";
		OutputDebugString(line.c_str());
		File.write(line.c_str(), line.length());
	}

	File.close();
<<<<<<< HEAD
	return S_OK;
=======
	return CR_OK;
>>>>>>> origin/master
}
