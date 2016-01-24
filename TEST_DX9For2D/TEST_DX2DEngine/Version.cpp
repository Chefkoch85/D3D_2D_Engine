#include "Version.h"

using namespace CKT;

CVersion::CVersion()
{
}


CKT::CVersion::CVersion(STRING version)
{
	int iPoint = version.find('.');
	STRING sTemp = version.substr(0, iPoint);
	m_byMajor = (BYTE)toInt(sTemp.c_str());

	sTemp = version.substr(iPoint + 1, version.length() - iPoint);
	m_byMinor = (BYTE)toInt(sTemp.c_str());
}

CKT::CVersion::CVersion(BYTE major, BYTE minor)
{
	m_byMajor = major;
	m_byMinor = minor;
}

CVersion::~CVersion()
{
}

CVersion & CKT::CVersion::operator=(const STRING& version)
{
	*this = CVersion(version);
	return *this;
}

bool CKT::operator==(const CVersion& l, const CVersion& r)
{
	return l.Major() == r.Major() && l.Minor() == r.Minor();
}

bool CKT::operator!=(const CVersion & l, const CVersion & r)
{
	return !(l == r);
}

bool CKT::operator<(const CVersion & l, const CVersion & r)
{
	return l.Major() < r.Major() || (l.Major() == r.Major() && l.Minor() < r.Minor());
}

bool CKT::operator<=(const CVersion & l, const CVersion & r)
{
	return l.Major() <= r.Major() || (l.Major() == r.Major() && l.Minor() <= r.Minor());
}

bool CKT::operator>(const CVersion & l, const CVersion & r)
{
	return l.Major() > r.Major() || (l.Major() == r.Major() && l.Minor() > r.Minor());
}

bool CKT::operator>=(const CVersion & l, const CVersion & r)
{
	return l.Major() >= r.Major() || (l.Major() == r.Major() && l.Minor() >= r.Minor());
}
