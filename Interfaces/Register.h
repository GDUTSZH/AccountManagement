#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <iostream>
#include <string>
#include <map>
#include "HttpCommon.h"
using namespace std;

typedef void *(*CREATE_FUNC)();

class ObjectFactory
{
public:
	static void * CreateObject(const string &interface_name)
	{
		if (ClassMAP.find(interface_name) != ClassMAP.end())
			return ClassMAP[interface_name]();
		return ClassMAP["ErrorClass"]();
	}
	static void Register(const string &interface_name, CREATE_FUNC func)
	{
		ClassMAP[interface_name] = func;
	}

private:
	static std::map<string, CREATE_FUNC> ClassMAP;
};
std::map<string, CREATE_FUNC> ObjectFactory::ClassMAP;

class Register
{
public:
	Register(const string &interface_name, CREATE_FUNC func)
	{
		ObjectFactory::Register(interface_name, func);
	}
};

#define MAP(interface_name, class_name)	\
class class_name##Register				\
{										\
public:									\
	static void * NewInstance()			\
	{									\
		return new class_name();		\
	}									\
private:								\
	static Register _reg;				\
};										\
Register class_name##Register::_reg(interface_name, class_name##Register::NewInstance);

#endif /* _REGISTER_H_ */