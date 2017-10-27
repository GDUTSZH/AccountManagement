#ifndef _PLAY_H_
#define _PLAY_H_

#include "HttpCommon.h"

class CPlay : public CHttpCommon
{
public:
	CPlay();
	virtual ~CPlay();

	void Handle();
};

#endif /* _PLAY_H_ */

