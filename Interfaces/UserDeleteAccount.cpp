#include "UserDeleteAccount.h"

#define USER_DELETE_ACCOUNT_STR(VSLUES)         \
    "DELETE FROM AccountManagement_AccountList  \
    WHERE " + (VSLUES) + ";"

CUserDeleteAccount::CUserDeleteAccount(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserDeleteAccount::~CUserDeleteAccount()
{ }

void CUserDeleteAccount::Handle()
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
    sValues += "user_name=" + ONE_VALUE(sName) + " AND ";
    sValues += "company_name=" + ONE_VALUE(jData["company_name"].asString()) + " AND ";
    sValues += "job_name=" + ONE_VALUE(jData["job_name"].asString());

    string sQuery = USER_DELETE_ACCOUNT_STR(sValues);

    cout << "Queyr String : " << sQuery << endl;

    int ret = CMySQL_Client::GetInstance()->Delete(sQuery);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Delete Account Error"));
		return;
    }
    
    Json::Value jContant;
    jContant["data"] = "Delete Account Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}