#ifndef _HTTP_COMMON_H_
#define _HTTP_COMMON_H_

#include "Base.h"

class CHttpCommon
{
public:
	CHttpCommon(PREQ pReq);
	virtual ~CHttpCommon();

	virtual void Handle() = 0;
	
	bool ParseParam(Json::Value &jData);
	void Send(int nCode, string sMessage);
	void Send_Fail(int nCode, string sMessage);
	void Send_Error(int nCode, string sMessage);

protected:
	PREQ pReq;
};

#endif /* _HTTP_COMMON_H_ */
