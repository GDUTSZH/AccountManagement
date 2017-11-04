#include "UserGetQuestion.h"

#define USER_GET_QUESTION_STR(sName)                                                    \
        "SELECT * FROM                                                                  \
        (                                                                               \
                SELECT user_question1 AS QUESTIONS                                      \
                FROM AccountManagement_User WHERE                                       \
                user_name=\'"+(sName)+"\'                                               \
        UNION ALL                                                                       \
                SELECT user_question2 AS QUESTIONS                                      \
                FROM AccountManagement_User WHERE                                       \
                user_name=\'"+(sName)+"\'                                               \
        UNION ALL                                                                       \
                SELECT user_question3 AS QUESTIONS                                      \
                FROM AccountManagement_User WHERE                                       \
                user_name=\'"+(sName)+"\'                                               \
        ) TempList;"

CUserGetQuestion::CUserGetQuestion(PREQ pReq) : CHttpCommon(pReq)
{ }

CUserGetQuestion::~CUserGetQuestion()
{ }

void CUserGetQuestion::Handle()
{
    Json::Value jData;
    if(!ParseParam(jData))
        return;

    if(!jData.isMember("name"))
    {
        Send_Error(404, Error_Data_Param_Miss);
		return;
    }
    
    string sValues = USER_GET_QUESTION_STR(jData["name"].asString());

    Json::Value jRoot = CMySQL_Client::GetInstance()->Select(sValues);
    if(jRoot.isMember("error"))
    {
        Send_Fail(502, Error_Operation_Rrror(2, "User Login Failure"));
		return;
    }
    
    int ret = jRoot["array"].size();
    
    //问题个数小于
    if(ret < 3)
    {
        Json::Value jContant;
        jContant["data"] = "用户名不存在";
        
        Json::Value jRet;
        jRet["code"] = 2;
        jRet["contant"] = jContant;

        Send(504, jRet.toStyledString());
		return;
    }

    Json::Value jContant;
    jContant["question"] = jRoot["array"];
    jContant["data"] = "Get Password Success";

    Json::Value jRet;
    jRet["code"] = 1;
    jRet["contant"] = jContant;

    Send(200, jRet.toStyledString());
}