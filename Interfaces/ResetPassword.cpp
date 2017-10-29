#include "ResetPassword.h"

#define RESET_PASSWORD_STR(name,passwd,passwd2)         \
        "UPDATE AccountManagement_User SET              \
        user_password='"+passwd2+"' WHERE               \
        user_name='"+name+"' AND                        \
        user_password='"+passwd+"';"      

CResetPassword::CResetPassword(PREQ pReq) : CHttpCommon(pReq)
{ }

CResetPassword::~CResetPassword()
{ }

void CResetPassword::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;
    
    if(!jData.isMember("name") || !jData.isMember("passwd") ||    \
        !jData.isMember("passwd2") || !jData.isMember("ticket"))
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

    string sValues = RESET_PASSWORD_STR(jData["name"].asString(),   \
                    jData["passwd"].asString(),jData["passwd2"].asString());

    int ret = CMySQL_Client::GetInstance()->Update(sValues);
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "Reset Password Failure"));
		return;
    }

    Json::Value jContant;
    jContant["data"] = "Reset Password Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}