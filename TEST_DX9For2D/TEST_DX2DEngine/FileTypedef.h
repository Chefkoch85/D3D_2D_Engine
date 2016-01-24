#pragma once

#include "Engine.h"
#include <map>

namespace CKT
{
	class CFileTypedef
	{
	public:
		typedef std::pair<STRING, STRING> ENTRY_PAIR;
		typedef std::pair<STRING, std::map<STRING, STRING> > CAPTION_PAIR;
		typedef std::map<STRING, STRING> ENTRY_MAP;
		//				CAPTION			  ENTRY	  VALUE
		typedef std::map<STRING, std::map<STRING, STRING>> CAPTION_MAP;
	};
}
