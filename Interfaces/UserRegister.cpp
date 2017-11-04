#include "UserRegister.h"

#define REGISTER_STR(VALUES)                                    \
        "insert into AccountManagement_User                     \
        (user_name,user_password,                               \
        user_question1,user_answer1,user_question2,user_answer2,\
        user_question3,user_answer3) values(" + (VALUES) + ");"     

#define ONE_VALUE(VALUE)  string("\'") + (VALUE) + string("\'") 

CUserRegister::CUserRegister(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserRegister::~CUserRegister()
{ }

void CUserRegister::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;
    
    if(!jData.isMember("name") || !jData.isMember("passwd") ||  \
        !jData.isMember("a1")  || !jData.isMember("q1")     ||  \
        !jData.isMember("a2")  || !jData.isMember("q2")     ||  \
        !jData.isMember("a3")  || !jData.isMember("q3"))
    {
        Send_Error(404, Error_Data_Param_Miss);
		return;
    }
    
    string sValues;
    sValues += ONE_VALUE(jData["name"].asString());
    sValues += "," + ONE_VALUE(jData["passwd"].asString());
    sValues += "," + ONE_VALUE(jData["q1"].asString());
    sValues += "," + ONE_VALUE(jData["a1"].asString());
    sValues += "," + ONE_VALUE(jData["q2"].asString());
    sValues += "," + ONE_VALUE(jData["a2"].asString());
    sValues += "," + ONE_VALUE(jData["q3"].asString());
    sValues += "," + ONE_VALUE(jData["a3"].asString());

    CMySQL_Client * pMySQL = CMySQL_Client::GetInstance();
    int ret = pMySQL->Insert(REGISTER_STR(sValues));
    if(ret <= 0)
    {
        Send_Fail(502, Error_Operation_Rrror(2, "MySQL Insert Error"));
		return;
    }

    Json::Value jContant;
    jContant["ticket"] = CTicketManager::GetInstance()->GetTicket(jData["name"].asString());
    jContant["data"] = "User Register Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}