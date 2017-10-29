#include "TicketUpdate.h"

CTicketUpdate::CTicketUpdate(PREQ pReq) : CHttpCommon(pReq)
{ }

CTicketUpdate::~CTicketUpdate()
{ }

void CTicketUpdate::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;
    
    if(!jData.isMember("name") || !jData.isMember("ticket"))
    {
        Send_Error(404, Error_Data_Param_Miss);
		return;
    }

    string sOldTicket = jData["ticket"].asString();
    if(!CTicketManager::GetInstance()->VolidateTicket(sOldTicket))
    {
        Send_Error(404, Error_Operation_Rrror(2, "Old Ticket Invalid"));
        return;
    }
    
    string sUserName = jData["name"].asString();
    string sNewTicket = CTicketManager::GetInstance()->SwapTicket(sOldTicket, sUserName);

    Json::Value jContant;
    jContant["ticket"] = sNewTicket;
    jContant["data"] = "Update Ticket Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}