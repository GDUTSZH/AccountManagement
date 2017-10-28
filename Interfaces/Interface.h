#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Register.h"
#include "HttpCommon.h"
#include "Login.h"
#include "Error.h"
#include "UserRegister.h"

MAP("ErrorClass", CError)
MAP("LoginClass", CLogin)
MAP("UserRegister", CUserRegister)

#endif /* _INTERFACE_H_ */