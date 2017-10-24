#include <iostream>
#include "MySQL_Client.h"
using namespace std;

int main()
{
    CMySQL_Client * pMySQL = CMySQL_Client::GetInstance();

    int ret = 0;
    ret = pMySQL->Insert("insert into Stu(user_name, user_old) values(\'小王\', 22);");
    cout << "影响了" << ret << "行" <<endl;

    ret = pMySQL->Insert("insert into Stu(user_name, user_old) values(\'小红\', 23);");
    cout << "影响了" << ret << "行" <<endl;

    ret = pMySQL->Insert("insert into Stu(user_name, user_old) values('小张', 27);");
    cout << "影响了" << ret << "行" <<endl;

    ret = pMySQL->Update("update Stu set user_old=10 where user_name = '小红';");
    cout << "影响了" << ret << "行" <<endl;

    ret = pMySQL->Delete("delete from Stu where user_name = '小明'");
    cout << "影响了" << ret << "行" <<endl;

    Json::Value jRoot = pMySQL->Select("Select * from Stu;");
    cout << endl << jRoot << endl;
	// bool connected = Connect(pMySQL, "120.78.92.86",3306,"mysqlDBA","GDUT14_iot1_DBA","TestDB",0);
	// if(connected)
	// 	cout << "MySql Connect Success" << endl;
	// else
	// 	cout << "MySql Connect Faild " << endl;

    //delete pMySQL;
    return 0;
}