#ifndef _RESET_PASSWORD_H_
#define _RESET_PASSWORD_H_

#include "HttpCommon.h"

class CResetPassword : public CHttpCommon
{
public:
    CResetPassword(PREQ pReq);
    virtual ~CResetPassword();
    
	virtual void Handle();
};

#endif /* _RESET_PASSWORD_H_ */