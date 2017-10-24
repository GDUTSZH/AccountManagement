#ifndef _ERROR_H_
#define _ERROR_H_

#include "HttpCommon.h"
class CError : public CHttpCommon
{
public:
	CError();
	virtual ~CError();

	virtual void Handle();
};

#endif /* _ERROR_H_ */

