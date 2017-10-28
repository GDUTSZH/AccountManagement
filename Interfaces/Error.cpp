#include "Error.h"

CError::CError(PREQ pReq) : CHttpCommon(pReq)
{
}


CError::~CError()
{
}

void CError::Handle()
{
	Send_Error(404, "ERROR");
	//SetContant("This is a error commond");
	//std::cout << "This is a error commond" << std::endl;
}