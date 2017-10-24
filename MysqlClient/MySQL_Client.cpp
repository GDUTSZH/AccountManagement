#include "MySQL_Client.h"

CMySQL_Client::Destructor CMySQL_Client::destructor;
CMySQL_Client* CMySQL_Client::m_pInstance = NULL;

CMySQL_Client::CMySQL_Client()
{
	m_pMysql = new MYSQL();

	cout << "Init ..." <<endl;
	mysql_init(m_pMysql);

	cout << "Connect ..." <<endl;
	
	int connected = Connect("120.78.92.86",3306,"mysqlDBA","GDUT14_iot1_DBA","TestDB",0);

	if(connected)
		cout << "MySql Connect Success" << endl;
	else
		cout << "MySql Connect Faild " << endl;

	if(SetCharacter())
		cout << "Set Chinese Success" << endl;
	else
		cout << "Set Chinese Faild" << endl;
}

CMySQL_Client::~CMySQL_Client()
{
	if (NULL != m_pMysql)
	{
		mysql_close(m_pMysql);
		delete m_pMysql;
	}
}

CMySQL_Client* CMySQL_Client::GetInstance()
{
	if (NULL == m_pInstance)
		m_pInstance = new CMySQL_Client();
	return m_pInstance;
}

bool CMySQL_Client::Connect(string sIP, int nPort, string sUserName, string sPassword, string sDBname, int nTimeout)
{
	if(!mysql_real_connect(m_pMysql, sIP.c_str(), sUserName.c_str(), sPassword.c_str(), sDBname.c_str(), nPort, NULL, 0))
		return false;
	return true;
}

bool CMySQL_Client::SetCharacter()
{
	int ret = mysql_query(m_pMysql, "SET NAMES utf8");
	if(0 == ret)
		return true;
	return false;
}

int CMySQL_Client::Insert(string sQueny)
{
	int ret = mysql_query(m_pMysql, sQueny.c_str());
	if(0 == ret)
	{
		int num_rows = mysql_affected_rows(m_pMysql);  //返回update,insert,delete影响的行数
		return num_rows;
	}
	return 0;
}

int CMySQL_Client::Delete(string sQueny)
{
	int ret = mysql_query(m_pMysql, sQueny.c_str());
	if(0 == ret)
	{
		int num_rows = mysql_affected_rows(m_pMysql);  //返回update,insert,delete影响的行数
		return num_rows;
	}
	return 0;
}

int CMySQL_Client::Update(string sQueny)
{
	int ret = mysql_query(m_pMysql, sQueny.c_str());
	if(0 == ret)
	{
		int num_rows = mysql_affected_rows(m_pMysql);  //返回update,insert,delete影响的行数
		return num_rows;
	}
	return 0;
}

Json::Value CMySQL_Client::Select(string sQueny)
{
	Json::Value jRoot;
	jRoot.resize(0);

	if(mysql_query(m_pMysql, sQueny.c_str()))	//查询错误
		return jRoot;

	MYSQL_RES *result = mysql_store_result(m_pMysql);  //获取结果集
	if(!result)
		return jRoot;
	
	int num_fields = mysql_num_fields(result); //获取结果集中总共的字段数，即列数
	int num_rows=mysql_num_rows(result);       //获取结果集中总共的行数

	/*输出結果的字段名*/
	MYSQL_FIELD * pField;
	vector<string> vField(num_fields);
	for (int i = 0; pField = mysql_fetch_field(result); i++)
		vField[i] = pField->name;

	for(int i=0;i<num_rows;i++) //输出每一行
	{
		Json::Value jRow;
		//获取下一行数据
		MYSQL_ROW row = mysql_fetch_row(result);

		for(int j=0;j<num_fields;j++)  //输出每一字段
		{
			jRow[vField[j]] = row[j];
		}
		jRoot[i] = jRow;
	}
	
	return jRoot;
}