#ifndef _MYSQL_CLIENT_H_
#define _MYSQL_CLIENT_H_

#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <vector>
#include "json/json.h"
using namespace std;

class CMySQL_Client
{
private:
	CMySQL_Client();

public:
	~CMySQL_Client();
	static CMySQL_Client* GetInstance();

	/*
	 *	返回值为int的函数返回执行该语句影响的行数，
	 *	返回值为string是函数返回json的数组格式
	 */
	bool Connect(string sIP, int nPort, string sUserName, string sPassword,string sDBname,int nTimeout);
	bool SetCharacter();
	int Insert(string sQueny);
	int Delete(string sQueny);
	int Update(string sQueny);
	Json::Value Select(string sQueny);

private:
	static CMySQL_Client* m_pInstance;
	MYSQL * m_pMysql;

public:
	class Destructor
	{
	public:
		~Destructor()
		{
			if(NULL != CMySQL_Client::m_pInstance)
				delete CMySQL_Client::m_pInstance;
		}
	};
private:
	static Destructor destructor;
};

#endif /* _MYSQL_CLIENT_H_ */