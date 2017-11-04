#ifndef _USER_FORGET_PASSWORD_H_
#define _USER_FORGET_PASSWORD_H_

#include "HttpCommon.h"

class CUserForgetPassword : public CHttpCommon
{
public:
	CUserForgetPassword(PREQ pReq);
	virtual ~CUserForgetPassword();

	virtual void Handle();
};

#endif /* _USER_FORGET_PASSWORD_H_ */
