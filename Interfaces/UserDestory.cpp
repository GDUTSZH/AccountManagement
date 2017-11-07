#include "UserDestory.h"

#define USER_DESTORY_STR(sName, sPasswd)                        \
        "DELETE FROM AccountManagement_User WHERE               \
        user_name=\'" + (sName) + "\' AND                       \
        user_password=\'" + (sPasswd) + "\';"

CUserDestory::CUserDestory(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserDestory::~CUserDestory()
{ }

void CUserDestory::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;
    
    if(!jData.isMember("name") || !jData.isMember("passwd") \
         || !jData.isMember("ticket"))
    {
        Send_Error(404, Error_Data_Param_Miss);
		return;
    }
    
    string sTicket = jData["ticket"].asString();
    if(!CTicketManager::GetInstance()->VolidateTicket(sTicket))
    {
        Send_Error(404, Error_Operation_Rrror(2, "Old Ticket Invalid"));
        return;
    }

    string sValues = USER_DESTORY_STR(jData["name"].asString(), jData["passwd"].asString());
    
    int ret = CMySQL_Client::GetInstance()->Delete(sValues);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "User Destory Failure"));
		return;
    }

    Json::Value jContant;
    jContant["data"] = "User Destory Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}