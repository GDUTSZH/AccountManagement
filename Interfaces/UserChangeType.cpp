#include "UserChangeType.h"

#define USER_CHANGE_TYPE_STR(SRC_VALUE, AIM_VALUE)      \
    "UPDATE AccountManagement_Type SET "                \
     + (AIM_VALUE) + " WHERE " + (SRC_VALUE) + ";"

CUserChangeType::CUserChangeType(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserChangeType::~CUserChangeType()
{ }

void CUserChangeType::Handle()
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
    sAimValue += "job_type=" + ONE_VALUE(jData["job_type"].asString()) + ",";
    sAimValue += "note=" + ONE_VALUE(jData["note"].asString());

    string sSrcValue;
    sSrcValue += "user_name=" + ONE_VALUE(sName) + " AND ";
    sSrcValue += "job_type=" + ONE_VALUE(jData["job_type_old"].asString());

    string sQuery = USER_CHANGE_TYPE_STR(sSrcValue, sAimValue);

    cout << "Queyr String : " << sQuery << endl;

    int ret = CMySQL_Client::GetInstance()->Update(sQuery);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Change Type Error"));
		return;
    }
    
    Json::Value jContant;
    jContant["data"] = "Change Type Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}