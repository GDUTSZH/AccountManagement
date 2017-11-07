#ifndef _USER_DELETE_ACCOUNT_H_
#define _USER_DELETE_ACCOUNT_H_

#include "HttpCommon.h"

class CUserDeleteAccount : public CHttpCommon
{
public:
	CUserDeleteAccount(PREQ pReq);
    virtual ~CUserDeleteAccount();
    
	virtual void Handle();
};

#endif /* _USER_DELETE_ACCOUNT_H_ */