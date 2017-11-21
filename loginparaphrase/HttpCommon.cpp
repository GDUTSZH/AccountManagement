#include "HttpCommon.h"


CHttpCommon::CHttpCommon(PREQ pReq)
{
	this->pReq = pReq;
}

CHttpCommon::~CHttpCommon()
{}

bool CHttpCommon::ParseParam(Json::Value &jData)
{
	string sURI = evhttp_request_get_uri(pReq);

	int nPos;
	string sParamList;
	
	//截取出参数表
	nPos = sURI.find('?', (unsigned int)1);
	sParamList = sURI.substr(nPos+1, sURI.size() - nPos);

	printf("原请求参数列表： %s\n", sParamList.c_str());

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

	//printf("格式化请求参数： %s\n", sParamList.c_str());

	//解析成Json
	Json::Reader jReader;
	if ( ! jReader.parse(sParamList.c_str(), jData))
	{
		Send_Error(404, Error_Param_Parse_Failure);
		return false;
	}
	
	if ( ! jData.isMember("tm"))
	{
		Send_Error(404, Error_Timestamp_NoExist);
		return false;
	}
	if ( ! jData.isMember("data"))
	{
		Send_Error(404, Error_Data_NoExist);
		return false;
	}
	if ( ! jData.isMember("token"))
	{
		Send_Error(404, Error_Token_NoExist);
		return false;
	}
	
	//这里需要对三个参数进行解密
	//再判断时间戳是否在一分钟以内
	//再计算Token验证数据是否被窜改

	//解析data
	string sData = Base64Decode(jData["data"].asString());

	printf("Base64解析得到的Data： %s\n", sData.c_str());

    if(!jReader.parse(sData, jData))
    {
        Send_Error(404, Error_Data_Format_Wrong);
		return false;
    }

	return true;
}

void CHttpCommon::Send(int nCode, string sMessage)
{
	evbuffer* pBuf = evbuffer_new();
	sMessage = Base64Encode(sMessage);
	evbuffer_add_printf(pBuf, sMessage.c_str());
	evhttp_send_reply(pReq, nCode, "OK", pBuf);
	evbuffer_free(pBuf);
}

void CHttpCommon::Send_Fail(int nCode, string sMessage)
{
	evbuffer* pBuf = evbuffer_new();
	sMessage = Base64Encode(sMessage);
	evbuffer_add_printf(pBuf, sMessage.c_str());
	evhttp_send_reply(pReq, nCode, "Fail", pBuf);
	evbuffer_free(pBuf);
}

void CHttpCommon::Send_Error(int nCode, string sMessage)
{
	evbuffer* pBuf = evbuffer_new();
	sMessage = Base64Encode(sMessage);
	evbuffer_add_printf(pBuf, sMessage.c_str());
	evhttp_send_reply(pReq, nCode, "Error", pBuf);
	evbuffer_free(pBuf);
}