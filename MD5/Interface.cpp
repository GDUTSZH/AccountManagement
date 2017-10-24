#include "stdafx.h"
#include "Interface.h"  
#include <iostream>  
#include <string>  
using std::string;  
using std::cout;  
using std::endl;  
  
//接口的外部实现  
void MD5::encode()  
{  
      
}  
void MD5::decode()  
{  
     
}  

//需要导出的函数，即用户在外部可以调用的接口  
_declspec(dllexport)bool MD5(void** _RtObject)  
{  
    return true;  
}  