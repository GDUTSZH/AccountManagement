#include "UserAddType.h"

#define USER_ADD_TYPE_STR(VSLUES)        \
    "Insert Into AccountManagement_Type     \
    (user_name,job_type,note)               \
    VALUES(" + (VSLUES) + ");"

CUserAddType::CUserAddType(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserAddType::~CUserAddType()
{ }

void CUserAddType::Handle()
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
    sValues += ONE_VALUE(jData["note"].asString());

    string sQuery = USER_ADD_TYPE_STR(sValues);

    cout << "添加语句 : " << sQuery <<endl;

    int ret = CMySQL_Client::GetInstance()->Insert(sQuery);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Add Type Error"));
		return;
    }
    
    Json::Value jContant;
    jContant["data"] = "Add Type Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}