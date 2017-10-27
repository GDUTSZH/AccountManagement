#ifndef _HTTP_COMMON_H_
#define _HTTP_COMMON_H_

#include "Base.h"

class CHttpCommon
{
public:
	CHttpCommon();
	virtual ~CHttpCommon();

	virtual void Handle() = 0;

	void SetContant(string sContant);
	string GetContant();

private:
	string m_sContant;
};

#endif /* _HTTP_COMMON_H_ */
