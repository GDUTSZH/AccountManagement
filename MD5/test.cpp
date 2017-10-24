/**
 * @file test.cpp
 * @The test file of md5.
 * @author Jiewei Wei
 * @mail weijieweijerry@163.com
 * @github https://github.com/JieweiWei
 * @data Oct 19 2014
 *
 */
#include "stdafx.h"
#include <iostream>

#include "MD5.h"

using std::cout;
using std::endl;

void printMD5(const string& message) {
  cout << "密文为： "
       << MD5(message).toStr() << endl;
}

int main() {
  std::string a;
  printf(" 请输入明文");
  std::cin>>a;
  printMD5(a);

  system("pause");
	return 0;
}
