#include "TicketManager.h"

CTicketManager * CTicketManager::m_pInstance = NULL;

CTicketManager::CTicketManager()
{
    srand((int)time(NULL));
}

CTicketManager * CTicketManager::GetInstance()
{
    if(NULL == m_pInstance)
        m_pInstance = new CTicketManager();
    return m_pInstance;
}

void CTicketManager::StartManager()
{
    CTicketManager::GetInstance()->m_CleanThread = std::thread(ThreadFunc);
    //CTicketManager::GetInstance()->m_CleanThread.join();
}

void CTicketManager::ThreadFunc()
{
    struct event_base *base = event_base_new();
    if (!base) 
    {
        std::cout << "Thread Error" << std::endl;
        return;
    }
    
    struct timeval timeout;
    struct event *ev = event_new(base, -1, EV_PERSIST, CleanTicket, NULL);
    if (ev) 
    {
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        event_add(ev, &timeout);
    }
    event_base_dispatch(base);
}

string CTicketManager::GetTicket(const string &sUserName)
{
    int nTime = (int)time(NULL);
    string sTicket = GetRandStr(32) + sUserName + Int2String(nTime) + GetRandStr(32);
    sTicket = GetMD5(sTicket);
    std::lock_guard<std::mutex> lg_Lock(m_mtxLock);
    m_mapTicket[sTicket] = nTime;
    return sTicket;
}

string CTicketManager::SwapTicket(string &sTicket,const string &sUserName)
{
    string sOldTicket = sTicket;
    sTicket = GetTicket(sUserName);
    int nTime = (int)time(NULL);
    std::lock_guard<std::mutex> lg_Lock(m_mtxLock);
    m_mapTicket[sOldTicket] = nTime - m_nLifeTime - 1;
    return sTicket;
}

bool CTicketManager::VolidateTicket(const string &sTicket)
{
    std::lock_guard<std::mutex> lg_Lock(m_mtxLock);
    if(0 != m_mapTicket.count(sTicket))
    {
        int nTime = (int)time(NULL);
        if(abs(m_mapTicket[sTicket] - nTime) <= m_nLifeTime)
            return true;
    }
    return false;
}

void CTicketManager::CleanTicket(evutil_socket_t fd, short event, void *arg)
{
    CTicketManager * pInstance = CTicketManager::GetInstance();
    int nTime = (int)time(NULL);
    std::lock_guard<std::mutex> lg_Lock(pInstance->m_mtxLock);
    std::map<string, int>::iterator it = pInstance->m_mapTicket.begin();
    while(it != pInstance->m_mapTicket.end())
    {
        if(abs(it->second - nTime) > pInstance->m_nLifeTime)
            it = pInstance->m_mapTicket.erase(it);
        else
            ++it;
    }
}

string CTicketManager::Int2String(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

string CTicketManager::GetRandStr(int nSize)
{
    string sRandStr;
    int nChar;
    for(int i=0;i<nSize;++i)
    {
        nChar = rand();
        switch(rand()%3)
        {
        case 0:
            nChar = nChar % 10 + '0'; break;
        case 1:
            nChar = nChar % 26 + 'A'; break;
        case 2:
            nChar = nChar % 26 + 'a'; break;
        }
        sRandStr += (char)nChar;
    }
    return sRandStr;
}