#include "UserLogin.h"

#define USER_LOGIN_STR(sName, sPasswd)                          \
        "SELECT * FROM AccountManagement_User WHERE             \
        user_name=\'" + (sName) + "\' AND                       \
        user_password=\'" + (sPasswd) + "\';"  

CUserLogin::CUserLogin(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserLogin::~CUserLogin()
{ }

void CUserLogin::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;
    
    if(!jData.isMember("name") || !jData.isMember("passwd"))
    {
        Send_Error(404, Base64Encode(Error_Data_Param_Miss));
		return;
    }
    
    string sValues = USER_LOGIN_STR(jData["name"].asString(), jData["passwd"].asString());

    int ret = CMySQL_Client::GetInstance()->Select(sValues).size();
    if(ret <= 0)
    {
        Send_Fail(502, Base64Encode(Error_Operation_Rrror(2, "User Login Failure")));
		return;
    }

    Send(200, Base64Encode(Execute_Successfully("User Login Success")));
}