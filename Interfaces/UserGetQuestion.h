#ifndef _USER_GET_QUESTION_H_
#define _USER_GET_QUESTION_H_

#include "HttpCommon.h"

class CUserGetQuestion : public CHttpCommon
{
public:
	CUserGetQuestion(PREQ pReq);
	virtual ~CUserGetQuestion();

	virtual void Handle();
};

#endif /* _USER_GET_QUESTION_H_ */