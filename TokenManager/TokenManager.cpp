#include "TokenManager.h"

CTokenManager * CTokenManager::m_pInstance = NULL;

CTokenManager::CTokenManager()
{}

CTokenManager * CTokenManager::GetInstance()
{
    if(NULL == m_pInstance)
        m_pInstance = new CTokenManager();
    return m_pInstance;
}

void CTokenManager::StartManager()
{
    CTokenManager::GetInstance()->m_CleanThread = std::thread(ThreadFunc);
    //CTokenManager::GetInstance()->m_CleanThread.join();
}

void CTokenManager::ThreadFunc()
{
    struct event_base *base = event_base_new();
    if (!base) 
    {
        std::cout << "Thread Error" << std::endl;
        return;
    }
    
    struct timeval timeout;
    struct event *ev = event_new(base, -1, EV_PERSIST, CleanToken, NULL);
    if (ev) 
    {
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        event_add(ev, &timeout);
    }
    event_base_dispatch(base);
}

string CTokenManager::GetToken(const string &sUserName)
{
    int nTime = (int)time(NULL);
    string sToken = m_sTOKEN_STR1 + sUserName + Int2String(nTime) + m_sTOKEN_STR2;
    //sToken = GetMD5(sToken);
    std::lock_guard<std::mutex> lg_Lock(m_mtxLock);
    m_mapToken[sToken] = nTime;
    return sToken;
}

string CTokenManager::SwapToken(const string &sToken,const string &sUserName)
{
    string sNewToken = GetToken(sUserName);
    int nTime = (int)time(NULL);
    std::lock_guard<std::mutex> lg_Lock(m_mtxLock);
    m_mapToken[sToken] = nTime - m_nLifeTime - 1;
    return sNewToken;
}

bool CTokenManager::VolidateToken(const string &sToken)
{
    std::lock_guard<std::mutex> lg_Lock(m_mtxLock);
    if(0 != m_mapToken.count(sToken))
    {
        int nTime = (int)time(NULL);
        if(abs(m_mapToken[sToken] - nTime) <= m_nLifeTime)
            return true;
    }
    return false;
}

void CTokenManager::CleanToken(evutil_socket_t fd, short event, void *arg)
{
    CTokenManager * pInstance = CTokenManager::GetInstance();
    int nTime = (int)time(NULL);
    std::lock_guard<std::mutex> lg_Lock(pInstance->m_mtxLock);
    std::map<string, int>::iterator it = pInstance->m_mapToken.begin();
    while(it != pInstance->m_mapToken.end())
    {
        if(abs(it->second - nTime) > pInstance->m_nLifeTime)
            it = pInstance->m_mapToken.erase(it);
        else
            ++it;
    }
}

string CTokenManager::Int2String(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}
