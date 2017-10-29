#include "HttpCommon.h"


CHttpCommon::CHttpCommon(PREQ pReq)
{
	this->pReq = pReq;
}

CHttpCommon::~CHttpCommon()
{}

bool CHttpCommon::ParseParam(Json::Value &jRoot)
{
	string sURI = evhttp_request_get_uri(pReq);

	int nPos;
	string sParamList;
	
	//截取出参数表
	nPos = sURI.find('?', (unsigned int)1);
	sParamList = sURI.substr(nPos+1, sURI.size() - nPos);

	//把参数列表格式化成Json
	sParamList = "{\"" + sParamList + "\"}";
	int nIndex, nIndex2;
	if(-1 != (nIndex2 = sParamList.find("=")))
	{
		sParamList.replace(nIndex2, 1, "\":\"");
	}
	while(-1 != (nIndex = sParamList.find("&")))
	{
		if(-1 != (nIndex2 = sParamList.find("=", nIndex)))
		{
			sParamList.replace(nIndex2, 1, "\":\"");
		}
		sParamList.replace(nIndex, 1, "\",\"");
	}

	//解析成Json
	Json::Reader jReader;
	if ( ! jReader.parse(sParamList.c_str(), jRoot))
	{
		jReader.parse(string(Error_Param_Parse_Failure).c_str(), jRoot);
		return false;
	}
	
	if ( ! jRoot.isMember("tm"))
	{
		jReader.parse(string(Error_Timestamp_NoExist).c_str(), jRoot);
		return false;
	}
	if ( ! jRoot.isMember("data"))
	{
		jReader.parse(string(Error_Data_NoExist).c_str(), jRoot);
		return false;
	}
	if ( ! jRoot.isMember("token"))
	{
		jReader.parse(string(Error_Token_NoExist).c_str(), jRoot);
		return false;
	}
	
	//这里需要对三个参数进行解密
	//再判断时间戳是否在一分钟以内
	//再计算Token验证数据是否被窜改

	return true;
}

void CHttpCommon::Send(int nCode, string sMessage)
{
	evbuffer* pBuf = evbuffer_new();
	evbuffer_add_printf(pBuf, sMessage.c_str());
	evhttp_send_reply(pReq, nCode, "OK", pBuf);
	evbuffer_free(pBuf);
}

void CHttpCommon::Send_Fail(int nCode, string sMessage)
{
	evbuffer* pBuf = evbuffer_new();
	evbuffer_add_printf(pBuf, sMessage.c_str());
	evhttp_send_reply(pReq, nCode, "Fail", pBuf);
	evbuffer_free(pBuf);
}

void CHttpCommon::Send_Error(int nCode, string sMessage)
{
	evbuffer* pBuf = evbuffer_new();
	evbuffer_add_printf(pBuf, sMessage.c_str());
	evhttp_send_reply(pReq, nCode, "Error", pBuf);
	evbuffer_free(pBuf);
}