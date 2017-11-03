#ifndef _USER_GET_DATA_H_
#define _USER_GET_DATA_H_

#include "HttpCommon.h"

class CUserGetData : public CHttpCommon
{
public:
    CUserGetData(PREQ pReq);
    virtual ~CUserGetData();

    virtual void Handle();
};

#endif /* _USER_GET_DATA_H_ */