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
#include "UserAddAccount.h"
#include "UserAddType.h"
#include "UserDestory.h"
#include "UserDeleteAccount.h"
#include "UserDeleteType.h"
#include "UserChangeAccount.h"
#include "UserChangeType.h"

MAP("ErrorClass", CError)
MAP("UserRegister", CUserRegister)
MAP("UserLogin",CUserLogin)
MAP("TicketUpdate",CTicketUpdate)
MAP("ResetPassword",CResetPassword)
MAP("UserGetData",CUserGetData)
MAP("ForgetPassword",CUserForgetPassword)
MAP("GetQuestion",CUserGetQuestion)
MAP("AddAccount",CUserAddAccount)
MAP("AddType",CUserAddType)
MAP("Destory",CUserDestory)
MAP("DeleteAccount",CUserDeleteAccount)
MAP("DeleteType",CUserDeleteType)
MAP("ChangeAccount",CUserChangeAccount)
MAP("ChangeType",CUserChangeType)

#endif /* _INTERFACE_H_ */