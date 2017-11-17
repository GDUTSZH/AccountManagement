#include "UserChangeAccount.h"

#define USER_CHANGE_ACCOUNT_STR(SRC_VALUE, AIM_VALUE)   \
    "UPDATE AccountManagement_AccountList SET "         \
     + (AIM_VALUE) + " WHERE " + (SRC_VALUE) + ";"

CUserChangeAccount::CUserChangeAccount(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserChangeAccount::~CUserChangeAccount()
{ }

void CUserChangeAccount::Handle()
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

    string sAimValue;
    sAimValue += "company_name=" + ONE_VALUE(jData["company_name"].asString()) + ",";
    sAimValue += "job_name=" + ONE_VALUE(jData["job_name"].asString()) + ",";
    sAimValue += "post_url=" + ONE_VALUE(jData["post_url"].asString()) + ",";
    sAimValue += "job_type=" + ONE_VALUE(jData["job_type"].asString()) + ",";
    sAimValue += "account_name=" + ONE_VALUE(jData["account_name"].asString()) + ",";
    sAimValue += "account_password=" + ONE_VALUE(jData["account_password"].asString()) + ",";
    sAimValue += "note=" + ONE_VALUE(jData["note"].asString());

    string sSrcValue;
    sSrcValue += "user_name=" + ONE_VALUE(sName) + " AND ";
    sSrcValue += "company_name=" + ONE_VALUE(jData["company_name_old"].asString()) + " AND ";
    sSrcValue += "job_name=" + ONE_VALUE(jData["job_name_old"].asString());

    string sQuery = USER_CHANGE_ACCOUNT_STR(sSrcValue, sAimValue);

    cout << "Queyr String : " << sQuery << endl;

    int ret = CMySQL_Client::GetInstance()->Update(sQuery);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Change Account Error"));
		return;
    }
    
    Json::Value jContant;
    jContant["data"] = "Change Account Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}