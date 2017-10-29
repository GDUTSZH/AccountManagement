#ifndef _TOKEN_MANAGER_H_
#define _TOKEN_MANAGER_H_

#include <iostream>
#include <string>
#include "../MD5/MD5.h"

using namespace std;

class CTokenManager
{
public:
    static string GetToken(const string &sTime, const string &sData);
    static bool VolidateToken(const string &sTime, const string &sData, const string &sToken);
    
private:
    static const string m_sTOKEN_STR1;
    static const string m_sTOKEN_STR2;
};

#endif /*_TOKEN_MANAGER_H_*/
