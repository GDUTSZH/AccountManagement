#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include "json/json.h"
#include "../Base64/Base64.h"

#include "../MysqlClient/MySQL_Client.h"

using namespace std;

typedef struct evhttp_request* PREQ;
typedef struct evbuffer* PBUF;

#endif /* _BASE_H_ */