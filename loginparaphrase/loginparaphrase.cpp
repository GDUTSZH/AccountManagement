#include "loginparaphrase.h"

loginparaphrase::loginparaphrase()
{}
vector<string> loginparaphrase::split(const string &s, const string &seperator){
        vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;
  while(i != s.size()){
    //找到字符串中首个不等于分隔符的字母；
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i]==seperator[x]){
            ++i;
            flag= 0;
            break;
            }
            }

    //找到又一个分隔符，将两个分隔符之间的字符串取出；
    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
        for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
                flag = 1;
               break;
     }
     if(flag == 0)
        ++j;
     }
     if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

int loginparaphrase::dividemessage(const string useruri,vector<vector<map<string,string> > > &uservector){
    vector<string> result1=split(useruri,"?");
    vector<map<string,string> > usermassage;

    vector<string> result2=split(result1[1],"&");
    for(int i=0;i<3;i++){
          vector<string> result3=split(result2[i],"=");
          map<string,string> mes;
          mes.insert(pair<string, string>(result3[0], result3[1]));
          usermassage.push_back(mes);
    }
    uservector.push_back(usermassage);
    return 0;
}

void loginparaphrase::showcasemessage( const string str){
     dividemessage(str,&this.uservector);
     vector<map<string,string> > user0message=uservector[0];
     map<string,string>::iterator it;
     for(int usernum=0;usernum<uservector.capacity();usernum++){
            cout<<"这是第"<<usernum+1<<"位用户的信息"<<endl;
     int i=0;
     while(i<3){
             for(it=user0message[i].begin();it!=user0message[i].end();++it)
            cout<<"key:"<<it->first<<"  "<<"value:"<<it->second<<endl;
        i++;
     }
     }

}
