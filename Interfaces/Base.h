#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include "json/json.h"
#include "../Base64/Base64.h"

#include "../MysqlClient/MySQL_Client.h"
#include "../TicketManager/TicketManager.h"

using namespace std;

#define ONE_VALUE(VALUE)  string("\'") + (VALUE) + string("\'") 

//执行成功
#define Execute_Successfully(sData) 	string("{\"code\":1,\"contant\":{\"data\":\"Success:") + (sData) + "\"}}"
//参数列表解析错误
#define Error_Param_Parse_Failure 	"{\"code\":2,\"contant\":{\"data\":\"Error:Parameter Parse Failure.\"}}"
//参数缺失
#define Error_Timestamp_NoExist 	"{\"code\":2,\"contant\":{\"data\":\"Error:Timestamp No Exist.\"}}"
#define Error_Data_NoExist			"{\"code\":2,\"contant\":{\"data\":\"Error:Data No Exist.\"}}"
#define Error_Token_NoExist			"{\"code\":2,\"contant\":{\"data\":\"Error:Token No Exist.\"}}"
//Data数据格式错误
#define Error_Data_Format_Wrong		"{\"code\":2,\"contant\":{\"data\":\"Error:Data Format Wrong.\"}}"
#define Error_Data_Param_Miss       "{\"code\":2,\"contant\":{\"data\":\"Error:Data Param Miss.\"}}"

#define Error_Operation_Rrror(nCode,sData)  "{\"code\":" + Int2String(nCode) + ",\"contant\":{\"data\":\"Error:" + (sData) + "\"}}"

typedef struct evhttp_request* PREQ;
typedef struct evbuffer* PBUF;

string Int2String(int n);

#endif /* _BASE_H_ */