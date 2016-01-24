#include "FileHeaderReader.h"

#include <fstream>

using namespace CKT;
using namespace std;

CFileHeaderReader::CFileHeaderReader()
{
}


CFileHeaderReader::~CFileHeaderReader()
{
}

CKT_RESULT CKT::CFileHeaderReader::read(const STRING headerFile, CGameMap::SMapHeader& out)
{
	fstream File = fstream();
	File.open(headerFile.c_str());

	if (!File.is_open())
	{
		CEngine::setErrorFile(headerFile.c_str());
		return CR_FILENOTFOUND;
	}

	streamsize sizeOut = sizeof(out);
	File.read((char*)&out, sizeOut);

	// check bytes read
	std::streamsize readed = File.gcount();
	File.close();

	if (readed != sizeOut)
	{
		CEngine::setErrorFile(headerFile.c_str());
		return CR_FILEFORMAT;
	}

	return CR_OK;
}
