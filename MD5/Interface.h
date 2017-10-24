#include "stdafx.h"
#ifndef INTERFACE_DEFINE_AND_REALIZE  
#define INTERFACE_DEFINE_AND_REALIZE  
#include <string>  
using std::string;  
//define interface  
class MD5  
{  
public:  
    MD5():m_StrName("###")  
    {};  
    virtual ~MD5(){};  
    virtual void getDigest()=0;  
    virtual void toStr()=0;  
    virtual void decode()=0; 
    virtual void encode()=0;    
private:  
    string m_StrName;  
};  

#endif