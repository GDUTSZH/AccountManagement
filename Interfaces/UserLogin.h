#ifndef _USER_LOGIN_H_
#define _USER_LOGIN_H_

#include "HttpCommon.h"

class CUserLogin : public CHttpCommon
{
public:
	CUserLogin(PREQ pReq);
	virtual ~CUserLogin();

	virtual void Handle();
};

#endif /* _USER_LOGIN_H_ */