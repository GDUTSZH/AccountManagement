#ifndef _USER_CHANGE_TYPE_H_
#define _USER_CHANGE_TYPE_H_

#include "HttpCommon.h"

class CUserChangeType : public CHttpCommon
{
public:
	CUserChangeType(PREQ pReq);
    virtual ~CUserChangeType();
    
	virtual void Handle();
};

#endif /* _USER_CHANGE_TYPE_H_ */