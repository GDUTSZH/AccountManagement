#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "HttpCommon.h"

class CLogin : public CHttpCommon
{
public:
	CLogin(PREQ pReq);
	virtual ~CLogin();

	virtual void Handle();
};

#endif /* _LOGIN_H_ */