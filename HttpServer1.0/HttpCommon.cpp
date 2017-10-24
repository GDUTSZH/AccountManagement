#include "HttpCommon.h"


CHttpCommon::CHttpCommon()
{
}


CHttpCommon::~CHttpCommon()
{
}

void CHttpCommon::SetContant(string sContant)
{
	m_sContant = sContant;
}

string CHttpCommon::GetContant()
{
	return m_sContant;
}
