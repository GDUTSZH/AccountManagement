#ifndef _USER_ADD_ACCOUNT_H_
#define _USER_ADD_ACCOUNT_H_

#include "HttpCommon.h"

class CUserAddAccount : public CHttpCommon
{
public:
	CUserAddAccount(PREQ pReq);
	virtual ~CUserAddAccount();
    
	virtual void Handle();
};

#endif /* _USER_ADD_ACCOUNT_H_ */