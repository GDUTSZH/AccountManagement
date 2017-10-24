#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "Register.h"
#include "HttpCommon.h"
#include "Login.h"
#include "Play.h"
#include "Error.h"

MAP("ErrorClass", CError)
MAP("LoginClass", CLogin)
MAP("PlayClass", CPlay)

#endif /* _INTERFACE_H_ */