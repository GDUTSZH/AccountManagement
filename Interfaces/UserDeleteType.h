#ifndef _USER_DELETE_TYPE_H_
#define _USER_DELETE_TYPE_H_

#include "HttpCommon.h"

class CUserDeleteType : public CHttpCommon
{
public:
	CUserDeleteType(PREQ pReq);
    virtual ~CUserDeleteType();
    
	virtual void Handle();
};

#endif /* _USER_DELETE_TYPE_H_ */