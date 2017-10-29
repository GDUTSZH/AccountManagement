#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Register.h"
#include "HttpCommon.h"
#include "Error.h"
#include "UserRegister.h"
#include "UserLogin.h"
#include "TicketUpdate.h"

MAP("ErrorClass", CError)
MAP("UserRegister", CUserRegister)
MAP("UserLogin",CUserLogin)
MAP("TicketUpdate",CTicketUpdate)

#endif /* _INTERFACE_H_ */