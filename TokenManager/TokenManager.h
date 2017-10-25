#ifndef _TOKEN_MANAGER_H_
#define _TOKEN_MANAGER_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <sstream>
#include <thread>
#include <mutex>
#include <event2/event.h>

using namespace std;

class CTokenManager
{
private:
    CTokenManager();
    string Int2String(int n);
    
    static void ThreadFunc();
    static void CleanToken(evutil_socket_t fd, short event, void *arg);
    
public:
    static CTokenManager * GetInstance();
    static void StartManager();
    
    string GetToken(const string &sUserName);
    string SwapToken(string &sToken,const string &sUserName);
    bool VolidateToken(const string &sToken);
    string GetRandStr(int nSize);
    
private:
    static CTokenManager * m_pInstance;
    
    std::thread m_CleanThread;
    std::mutex m_mtxLock;
    std::map<string, int> m_mapToken; //token - time
    
    const int m_nLifeTime = 120;
    const string m_sTOKEN_STR1 = "012345678901234567890123456789ab";
    const string m_sTOKEN_STR2 = "012345678901234567890123456789ab";
};

#endif /*_TOKEN_MANAGER_H_*/
