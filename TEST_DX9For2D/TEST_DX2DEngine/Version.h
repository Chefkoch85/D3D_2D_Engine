#pragma once

#include "Engine.h"

namespace CKT
{
	class CVersion
	{
	public:
		CVersion();
		CVersion(STRING version);
		CVersion(BYTE major, BYTE minor);
		~CVersion();

		BYTE Major() const { return m_byMajor; }
		BYTE Minor() const { return m_byMinor; }

		CVersion& operator=(const STRING& version);

	private:
		BYTE m_byMajor = 0, m_byMinor = 0;
	};

	bool operator==(const CVersion& l, const CVersion& r);
	bool operator!=(const CVersion& l, const CVersion& r);

	bool operator <(const CVersion& l, const CVersion& r);
	bool operator<=(const CVersion& l, const CVersion& r);

	bool operator >(const CVersion& l, const CVersion& r);
	bool operator>=(const CVersion& l, const CVersion& r);
}
