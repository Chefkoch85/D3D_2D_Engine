#pragma once

#include "Engine.h"
#include "GameMap.h"

namespace CKT
{
	class CFileHeaderReader
	{
	public:
		~CFileHeaderReader();

		static CKT_RESULT read(const STRING headerFile, CGameMap::SMapHeader& out);

	private:
		CFileHeaderReader();
	};

}
