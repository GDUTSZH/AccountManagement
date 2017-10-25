#include <iostream>
#include "MySQL_Client.h"
using namespace std;

int main()
{
    // int nCode;
    // int ret;
    // Json::Value jRoot;
    // string sQuery;
    // char c;
    // char c_str[200];

    // CMySQL_Client * pMySQL = CMySQL_Client::GetInstance();
    
    // while(cin >> nCode)
    // {
    //     cin >> c;
    //     cin.getline(c_str, 200);
    //     getline(cin, sQuery);
    //     switch(nCode)
    //     {
    //     case 1:
    //         ret = pMySQL->Insert(sQuery);
    //         cout << "影响了" << ret << "行" <<endl;
    //         break;
    //     case 2:
    //         ret = pMySQL->Update(sQuery);
    //         cout << "影响了" << ret << "行" <<endl;
    //         break;
    //     case 3:
    //         ret = pMySQL->Delete(sQuery);
    //         cout << "影响了" << ret << "行" <<endl;
    //         break;
    //     case 4:
    //         jRoot = pMySQL->Select(sQuery);
    //         cout << "查询结果" << endl << jRoot << endl;
    //         break;
    //     default:
    //         break;
    //     }
    // }

    CMySQL_Client * pMySQL = CMySQL_Client::GetInstance();
    int ret = 0;

    int n;
    cin >> n;
    ret = pMySQL->Insert("insert into Stu(user_name, user_old) values('Jack', 22);");
    cout << "影响了" << ret << "行" <<endl;

    cin >> n;
    ret = pMySQL->Insert("insert into Stu(user_name, user_old) values('Rose', 23);");
    cout << "影响了" << ret << "行" <<endl;

    cin >> n;
    ret = pMySQL->Insert("insert into Stu(user_name, user_old) values('Tom', 27);");
    cout << "影响了" << ret << "行" <<endl;

    cin >> n;
    ret = pMySQL->Update("update Stu set user_old=user_old-10 where user_name = 'Rose';");
    cout << "影响了" << ret << "行" <<endl;

    cin >> n;
    ret = pMySQL->Delete("delete from Stu where user_name = 'Jack'");
    cout << "影响了" << ret << "行" <<endl;

    cin >> n;
    Json::Value jRoot = pMySQL->Select("Select * from Stu;");
    cout << endl << jRoot << endl;
    
    return 0;
}