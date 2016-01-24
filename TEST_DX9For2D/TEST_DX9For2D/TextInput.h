#pragma once

#include <vector>
#include <Windows.h>

class TextInputServer
{
	friend class TextInput;

protected:
	std::vector<TCHAR> m_Textlist;

public:

	TextInputServer(int size)
	{
	}

	void putChar(char c)
	{
		if (c == 8)
			m_Textlist.pop_back();

		m_Textlist.push_back(c);
	}
};

class TextInput
{
private:
	TextInputServer& m_TextServ;

public:
	TextInput(TextInputServer& serv) :
		m_TextServ(serv)
	{

	}
	~TextInput();



};

