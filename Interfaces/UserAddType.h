#ifndef _USER_ADD_TYPE_H_
#define _USER_ADD_TYPE_H_

#include "HttpCommon.h"

class CUserAddType : public CHttpCommon
{
public:
	CUserAddType(PREQ pReq);
    virtual ~CUserAddType();
    
	virtual void Handle();
};

#endif /* _USER_ADD_TYPE_H_ */