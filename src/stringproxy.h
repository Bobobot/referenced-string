#pragma once
#include "mystring.h"

class MyString; //circular dependency miatt

class StringProxy {
	MyString *myString;
	int index;
public:
	StringProxy(MyString *myString, int index) : myString(myString), index(index) {}

	char operator=(const char);

	operator char();
};
