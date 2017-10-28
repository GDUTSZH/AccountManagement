#ifndef _USER_REGISTER_H_
#define _USER_REGISTER_H_

#include "HttpCommon.h"

class CUserRegister : public CHttpCommon
{
public:
	CUserRegister(PREQ pReq);
	virtual ~CUserRegister();

	virtual void Handle();
};

#endif /* _USER_REGISTER_H_ */