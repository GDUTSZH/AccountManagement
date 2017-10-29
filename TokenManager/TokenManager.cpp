#include "TokenManager.h"

const string CTokenManager::m_sTOKEN_STR1 = "012345678901234567890123456789ab";
const string CTokenManager::m_sTOKEN_STR2 = "012345678901234567890123456789ab";

string CTokenManager::GetToken(const string &sTime, const string &sData)
{
    string sToken = m_sTOKEN_STR1 + sTime + sData + m_sTOKEN_STR2;
    sToken = GetMD5(sToken);
    return sToken;
}

bool CTokenManager::VolidateToken(const string &sTime, const string &sData, const string &sToken)
{
    if (sToken == GetToken(sTime, sData))
        return true;
    return false;
}