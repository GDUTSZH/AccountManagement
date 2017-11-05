#include "UserAddAccount.h"

#define USER_ADD_ACCOUNT_STR(VSLUES)                \
    "Insert Into AccountManagement_AccountList      \
    (user_name,job_type,company_name,job_name,      \
    account_name,account_password,note,post_url)    \
    VALUES(" + (VSLUES) + ");"


CUserAddAccount::CUserAddAccount(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserAddAccount::~CUserAddAccount()
{ }

void CUserAddAccount::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;

    if(!jData.isMember("name") || !jData.isMember("entry")    \
        ||!jData.isMember("ticket"))
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

    string sName = jData["name"].asString();
    jData = jData["entry"];

    string sValues;
    sValues += ONE_VALUE(sName) + ",";
    sValues += ONE_VALUE(jData["job_type"].asString()) + ",";
    sValues += ONE_VALUE(jData["company_name"].asString()) + ",";
    sValues += ONE_VALUE(jData["job_name"].asString()) + ",";
    sValues += ONE_VALUE(jData["account_name"].asString()) + ",";
    sValues += ONE_VALUE(jData["account_password"].asString()) + ",";
    sValues += ONE_VALUE(jData["note"].asString()) + ",";
    sValues += ONE_VALUE(jData["post_url"].asString());

    string sQuery = USER_ADD_ACCOUNT_STR(sValues);

    cout << "添加语句 : " << sQuery <<endl;

    int ret = CMySQL_Client::GetInstance()->Insert(sQuery);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Add Account Error"));
		return;
    }
    
    Json::Value jContant;
    jContant["data"] = "Add Account Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}