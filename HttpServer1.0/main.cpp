#include <iostream>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <string.h>
#include <mutex>
#include <thread>
#include <unistd.h>
#include "../Interfaces/Interface.h"

#include "ThreadPool.h"
#define TNUM 70
using namespace std;

CThreadPool *pMypoll;
bool startHttpServer(const char* ip, int port, void(*cb)(struct evhttp_request *, void *), void *arg)
{
	//创建event_base和evhttp
	event_base* base = event_base_new();
	evhttp* http_server = evhttp_new(base);
	if (!http_server) {
		return false;
	}
	//绑定到指定地址上
	int ret = evhttp_bind_socket(http_server, ip, port & 0xFFFF);
	if (ret != 0) {
		return false;
	}
	//设置事件处理函数
	evhttp_set_gencb(http_server, cb, arg);
	//一次便结束
//	event_base_loopexit(base,NULL);
	//启动事件循环，当有http请求的时候会调用指定的回调
	//unique_lock<mutex> lck(mtx);
	//while(1)
	//{
//		cout<<"a"<<endl;
	  event_base_dispatch(base);
//	  cout<<"ba"<<endl;
	 // cv.wait(lck);
	  //}
	evhttp_free(http_server);
	return true;
}

void MyHttpServerHandler(struct evhttp_request* req );

void start_thread(struct evhttp_request* req,void *arg)
{
	//thread a(MyHttpServerHandler,req);
	//a.detach();
	pMypoll->AddTask(MyHttpServerHandler,req);

	}
	
void MyHttpServerHandler(struct evhttp_request* req)
{
	//获取请求的URI
	string sURI = evhttp_request_get_uri(req);

	string sInterfaceName;	//接口名

	int nSubIndex = sURI.find('?', (unsigned int)1);
	if (-1 != nSubIndex)
		sInterfaceName = sURI.substr(1, nSubIndex-1);

	//生成接口对象并处理
	CHttpCommon * myHttp = (CHttpCommon *)ObjectFactory::CreateObject(sInterfaceName, req);
	myHttp->Handle();
	delete myHttp;
}

void startse()
{
	
	pMypoll=new CThreadPool(10);
	startHttpServer("0.0.0.0", 8080, start_thread, NULL);
	//startHttpServer("0.0.0.0", 80, MyHttpServerHandler, NULL);
}

int main(int argc, char** argv)
{
	std::cout << "Server Start" << std::endl;
	//多线程
/*	thread threads[TNUM];
	for(int i=0;i<TNUM;i++)
		threads[i]=thread(startse);
	for(auto &th:threads)
		th.join();*/
	//启动服务在地址 127.0.0.1:9000 上
	
	startse();

	return 0;
}
