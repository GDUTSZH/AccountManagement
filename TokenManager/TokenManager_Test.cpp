#include <iostream>
#include <string>
#include "TokenManager.h"
#include "unistd.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
using namespace std;

int main()
{
    CTokenManager * pManeger = CTokenManager::GetInstance();

    pManeger->StartManager();
    char C[20];
    vector<string> v;
    stringstream ss;
    string sTmp;
    for(int i=0;i<200;++i)
    {
        if(i<12)
            v.push_back(pManeger->GetToken("TestName"));
        string sTrue = "有效Token : ";
        string sFalse = "过时失效Token ：";
        for(int j=0;j<v.size();++j)
        {
            ss.clear();
            ss << j+1;
            ss >> sTmp;
            if(pManeger->VolidateToken(v[j]))
            {
                sTrue += sTmp + "    ";
                if((j+1)%3 == 0)
                    v[j] = pManeger->SwapToken(v[j], "TestName");
            }
            else
                sFalse += sTmp + "    ";
        }
        cout << sTrue << endl;
        cout << sFalse << endl;
        sleep(10);
    }

    return 0;
}