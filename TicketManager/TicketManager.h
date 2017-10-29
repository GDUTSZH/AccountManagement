#ifndef _Ticket_MANAGER_H_
#define _Ticket_MANAGER_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <sstream>
#include <thread>
#include <mutex>
#include <event2/event.h>
#include "../MD5/MD5.h"

using namespace std;

class CTicketManager
{
private:
    CTicketManager();
    string Int2String(int n);
    
    static void ThreadFunc();
    static void CleanTicket(evutil_socket_t fd, short event, void *arg);
    
public:
    static CTicketManager * GetInstance();
    static void StartManager();
    
    string GetTicket(const string &sUserName);
    string SwapTicket(string &sTicket,const string &sUserName);
    bool VolidateTicket(const string &sTicket);
    string GetRandStr(int nSize);
    
private:
    static CTicketManager * m_pInstance;
    
    std::thread m_CleanThread;
    std::mutex m_mtxLock;
    std::map<string, int> m_mapTicket; //Ticket - time
    
    const int m_nLifeTime = 120;
    const string m_sTicket_STR1 = "012345678901234567890123456789ab";
    const string m_sTicket_STR2 = "012345678901234567890123456789ab";
};

#endif /*_Ticket_MANAGER_H_*/
