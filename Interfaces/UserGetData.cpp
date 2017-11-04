#include "UserGetData.h"

#define USER_GET_ACCOUNTS_STR(sName)                        \
        "SELECT * FROM AccountManagement_AccountList WHERE  \
        user_name=\'" + (sName) + "\';"
#define USER_GET_TYPES_STR(sName)                        \
        "SELECT * FROM AccountManagement_Type WHERE         \
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

    string sQueue = USER_GET_ACCOUNTS_STR(jData["name"].asString());
    Json::Value jQueue = CMySQL_Client::GetInstance()->Select(sQueue);
    if(jQueue.isMember("error"))
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Get User Accounts Failure"));
		return;
    }
    Json::Value jAccounts = jQueue["array"];

    sQueue = USER_GET_TYPES_STR(jData["name"].asString());
    jQueue = CMySQL_Client::GetInstance()->Select(sQueue);
    if(jQueue.isMember("error"))
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Get User Types Failure"));
		return;
    }
    Json::Value jTypes = jQueue["array"];

    //构造返回值
    Json::Value jContant;
    jContant["data"] = "Get User Accounts and Types Success";
    
    Json::Value jUserData;
    jUserData["account_list"] = jAccounts;
    jUserData["type_list"] = jTypes;

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;
    jRet["user_data"] = jUserData;

    //cout << "Data is : " << jUserData.toStyledString() <<endl;

    Send(200, jRet.toStyledString());
}