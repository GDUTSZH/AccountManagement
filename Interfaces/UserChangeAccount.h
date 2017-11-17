#ifndef _USER_CHANGE_ACCOUNT_H_
#define _USER_CHANGE_ACCOUNT_H_

#include "HttpCommon.h"

class CUserChangeAccount : public CHttpCommon
{
public:
	CUserChangeAccount(PREQ pReq);
    virtual ~CUserChangeAccount();
    
	virtual void Handle();
};

#endif /* _USER_CHANGE_ACCOUNT_H_ */