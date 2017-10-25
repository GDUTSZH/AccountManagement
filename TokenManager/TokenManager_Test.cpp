#include <iostream>
#include <string>
#include "TokenManager.h"
using namespace std;

int main()
{
    string sTime = "123456091203";
    string sData = "aidjoau9uas0d9u0jmeoqd98ua09";
    string sToken = CTokenManager::GetToken(sTime, sData);
    cout << "Token : " << sToken << endl;
    if(CTokenManager::VolidateToken(sTime, sData, sToken))
    {
        cout << "Token验证通过" <<endl; 
    }
    else
    {
        cout << "Token验证失败" <<endl; 
    }

    return 0;
}