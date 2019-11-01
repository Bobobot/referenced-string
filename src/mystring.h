#pragma once
#include <map>
#include "stringvalue.h"
#include "stringproxy.h"

class StringProxy; //circular dependency miatt

class MyString {

	static std::map<const char *, StringValue *> stringMap;

	StringValue *string; //ez tárolja magát a stringet és azt, hogy hány reference van rajta

	void decreaseStringRef();
	void initStringValue(const char *);

public:
	MyString(const char * = "");
	MyString(const MyString &);
	MyString(MyString &&) noexcept;

	MyString &operator=(const MyString &);
	MyString &operator=(MyString &&) noexcept;
	char &operator[](int index) const;
	StringProxy operator[](int);
	//char &operator[](int index);

	//Lecseréli az indexedik helyen álló karaktert a paraméterben lévőre. Ehhez természetesen a string tagváltozó értékét újra kell számolni
	void replaceChar(int, char); 

	char *c_str();
	int length();
	~MyString();

	friend std::istream &operator>>(std::istream &is, MyString &s);
};

MyString operator+(MyString s1, MyString s2);
MyString &operator+=(MyString &s1, MyString s2);
MyString operator+(MyString s, char c);
MyString &operator+=(MyString &s, char c);
std::ostream &operator<<(std::ostream &os, MyString s);
