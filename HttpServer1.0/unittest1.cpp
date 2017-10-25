#include "stdafx.h"
#include "CppUnitTest.h"
#include"../linux_project/HttpCommon.h"
#include"../linux_project/Register.h"
#include"../linux_project/Interface.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(playclass)
		{
			CHttpCommon * myHttp = (CHttpCommon *)ObjectFactory::CreateObject("PlayClass");
			string a("Play Handle");

			myHttp->Handle();
			Assert::AreEqual(a,myHttp->GetContant());
			
		}

		TEST_METHOD(errorclass)
		{
			CHttpCommon * myHttp = (CHttpCommon *)ObjectFactory::CreateObject("aas");
			string a("This is a error commond");

			myHttp->Handle();
			Assert::AreEqual(a, myHttp->GetContant());

		}

		TEST_METHOD(loginclass)
		{
			CHttpCommon * myHttp = (CHttpCommon *)ObjectFactory::CreateObject("LoginClass");
			string a("Login Handle");

			myHttp->Handle();
			Assert::AreEqual(a, myHttp->GetContant());

		}
	};
}