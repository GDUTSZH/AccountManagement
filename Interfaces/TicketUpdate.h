#ifndef _TICKET_UPDATE_H_
#define _TICKET_UPDATE_H_

#include "HttpCommon.h"

class CTicketUpdate : public CHttpCommon
{
public:
	CTicketUpdate(PREQ pReq);
	virtual ~CTicketUpdate();
    
	virtual void Handle();
};

#endif /* _TICKET_UPDATE_H_ */