#include "Login.h"

CLogin::CLogin(PREQ pReq) : CHttpCommon(pReq)
{
}

CLogin::~CLogin()
{
}

void CLogin::Handle()
{
	Json::Value jRoot;
	if(!ParseParam(jRoot))
	{
		Send_Error(404, "Param Error");
		return;
	}
	Send(200, jRoot.toStyledString());
}