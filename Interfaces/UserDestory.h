#ifndef _USER_DESTORY_H_
#define _USER_DESTORY_H_

#include "HttpCommon.h"

class CUserDestory : public CHttpCommon
{
public:
	CUserDestory(PREQ pReq);
	virtual ~CUserDestory();

	virtual void Handle();
};

#endif /* _USER_DESTORY_H_ */