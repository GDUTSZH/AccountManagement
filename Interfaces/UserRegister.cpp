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
	Json::Value jRoot;
	if(!ParseParam(jRoot))
	{
		Send_Error(404, Base64Encode(jRoot.toStyledString()));
		return;
    }

    string sData = Base64Decode(jRoot["data"].asString());
    //cout << sData << endl;
    Json::Value jData;
    Json::Reader jReader;
    if(!jReader.parse(sData, jData))
    {
        Send_Error(404, Base64Encode(Error_Data_Format_Wrong));
		return;
    }

    //cout << jData << endl;
    if(!jData.isMember("name") || !jData.isMember("passwd") ||  \
        !jData.isMember("a1")  || !jData.isMember("q1")     ||  \
        !jData.isMember("a2")  || !jData.isMember("q2")     ||  \
        !jData.isMember("a3")  || !jData.isMember("q3"))
    {
        Send_Error(404, Base64Encode(Error_Data_Param_Miss));
		return;
    }
    
    string sValues;
    sValues += ONE_VALUE(jData["name"].asString());
    sValues += "," + ONE_VALUE(jData["passwd"].asString());
    sValues += "," + ONE_VALUE(jData["a1"].asString());
    sValues += "," + ONE_VALUE(jData["q1"].asString());
    sValues += "," + ONE_VALUE(jData["a2"].asString());
    sValues += "," + ONE_VALUE(jData["q2"].asString());
    sValues += "," + ONE_VALUE(jData["a3"].asString());
    sValues += "," + ONE_VALUE(jData["q3"].asString());

    //cout << "Insert Str : " << REGISTER_STR(sValues) << endl;

    CMySQL_Client * pMySQL = CMySQL_Client::GetInstance();
    int ret = pMySQL->Insert(REGISTER_STR(sValues));
    if(ret <= 0)
    {
        Send_Fail(502, Base64Encode(Error_Operation_Rrror(2, "MySQL Insert Error")));
		return;
    }

    Send(200, Base64Encode(Execute_Successfully("User Register Success")));
}