#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Register.h"
#include "HttpCommon.h"
#include "Error.h"
#include "UserRegister.h"
#include "UserLogin.h"
#include "TicketUpdate.h"
#include "ResetPassword.h"
#include "UserGetData.h"
#include "UserForgetPassword.h"
#include "UserGetQuestion.h"

MAP("ErrorClass", CError)
MAP("UserRegister", CUserRegister)
MAP("UserLogin",CUserLogin)
MAP("TicketUpdate",CTicketUpdate)
MAP("ResetPassword",CResetPassword)
MAP("UserGetData",CUserGetData)
MAP("ForgetPassword",CUserForgetPassword)
MAP("GetQuestion",CUserGetQuestion)

#endif /* _INTERFACE_H_ */