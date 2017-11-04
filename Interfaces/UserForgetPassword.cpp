#include "UserForgetPassword.h"

#define USER_FORGET_PASSWORD_STR(sName, sAnswer1,sAnswer2,sAnswer3)                     \
        "SELECT * FROM                                                                  \
        (                                                                               \
                SELECT user_question1 AS QUESTIONS,user_password AS USER_PASSOWRD       \
                FROM AccountManagement_User WHERE                                       \
                user_name=\'"+(sName)+"\' AND user_answer1=\'"+(sAnswer1)+"\'           \
        UNION ALL                                                                       \
                SELECT user_question2 AS QUESTIONS, user_password AS USER_PASSOWRD      \
                FROM AccountManagement_User WHERE                                       \
                user_name=\'"+(sName)+"\' AND user_answer2=\'"+(sAnswer2)+"\'           \
        UNION ALL                                                                       \
                SELECT user_question3 AS QUESTIONS, user_password AS USER_PASSOWRD      \
                FROM AccountManagement_User WHERE                                       \
                user_name=\'"+(sName)+"\' AND user_answer3=\'"+(sAnswer3)+"\'           \
        ) TempList;"

CUserForgetPassword::CUserForgetPassword(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserForgetPassword::~CUserForgetPassword()
{ }

void CUserForgetPassword::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;

    if(!jData.isMember("name") || !jData.isMember("a1")
        || !jData.isMember("a2") || !jData.isMember("a3"))
    {
        Send_Error(404, Error_Data_Param_Miss);
		return;
    }
    
    string sValues = USER_FORGET_PASSWORD_STR(jData["name"].asString(),     \
            jData["a1"].asString(), jData["a2"].asString(), jData["a3"].asString());

    Json::Value jRoot = CMySQL_Client::GetInstance()->Select(sValues);
    if(jRoot.isMember("error"))
    {
        Send_Fail(502, Error_Operation_Rrror(2, "User Login Failure"));
		return;
    }
    
    int ret = jRoot["array"].size();
    
    //正确的问题个数小于2
    if(ret < 2)
    {
        Json::Value jContant;
        jContant["data"] = "找回密码失败";
        
        Json::Value jRet;
        jRet["code"] = 2;
        jRet["contant"] = jContant;

        Send(504, jRet.toStyledString());
		return;
    }

    Json::Value jContant;
    jContant["passwd"] = jRoot["array"][1]["USER_PASSOWRD"].asString();
    jContant["data"] = "Get Password Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}