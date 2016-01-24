#include "Engine.h"

#include "FileReader.h"

using namespace CKT;

CFileReader CEngine::DUMMY_INIREADER;

const TCHAR* CEngine::WINDOW_CLASS_NAME = L"CKT_ENGINE";
<<<<<<< HEAD
=======

STRING CKT::ResultToString(CKT_RESULT result)
{
	if (CKT_RESULT_NAMES[result] == NULL)
		return L"UNKOWN";

	STRING temp = CKT_RESULT_NAMES[result];

	if (temp == L"")
		return L"UNKOWN";

	return temp;
}

STRING CEngine::m_sErrorFile = L"UNKOWN";

void CKT::CEngine::setErrorFile(STRING errorFile)
{
	m_sErrorFile = errorFile;
}

void CKT::CEngine::showErrorDialog(STRING errCaption, STRING errClass, CKT_RESULT result, STRING errDesc)
{
	STRING sMessage = L"ERROR - CALLER:\n" + errCaption + 
		L"\n\nERROR - CLASS:\n" + errClass + 
		L"\n\nERROR - CODE:\n" + ResultToString(result) + 
		L"\n\nERROR - DESCRIPTION:\n" + errDesc + 
		L"\n\nERROR - FILE:\n" + m_sErrorFile;

	MessageBox(NULL, sMessage.c_str(), L"ERROR!", MB_OK);
}

>>>>>>> origin/master
