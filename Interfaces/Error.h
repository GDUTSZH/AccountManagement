#ifndef _ERROR_H_
#define _ERROR_H_

#include "HttpCommon.h"
class CError : public CHttpCommon
{
public:
	CError(PREQ pReq);
	virtual ~CError();

	virtual void Handle();
};

#endif /* _ERROR_H_ */

