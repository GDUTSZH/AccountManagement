#include "UserGetData.h"

#define USER_GET_ACCOUNTS_STR(sName)                             \
        "SELECT * FROM AccountManagement_AccountList WHERE      \
        user_name=\'" + (sName) + "\';"

CUserGetData::CUserGetData(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserGetData::~CUserGetData()
{ }

void CUserGetData::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;
    
    if(!jData.isMember("name") || !jData.isMember("ticket"))
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

    string sValues = USER_GET_ACCOUNTS_STR(jData["name"].asString());

    Json::Value jAccounts = CMySQL_Client::GetInstance()->Select(sValues);
    if(jAccounts.size() <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Get User Accounts Failure"));
		return;
    }

    Json::Value jContant;
    jContant["data"] = "Get User Accounts Success";
    
    Json::Value jUserData;
    jUserData["account_list"] = jAccounts;

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;
    jRet["user_data"] = jUserData;

    Send(200, jRet.toStyledString());
}