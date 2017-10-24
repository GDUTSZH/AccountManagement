#ifndef LOGINPARAPHRASE_H_INCLUDED
#define LOGINPARAPHRASE_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
    class loginparaphrase{
       private:
           vector<vector<map<string,string> > > uservector;
           vector<string> split(const string &s, const string &seperator);

       public:
        loginparaphrase();
        int dividemessage(const string useruri,vector<vector<map<string,string> > > &uservector);
        void showcasemessage(const string str);


    };


#endif // LOGINPARAPHRASE_H_INCLUDED
