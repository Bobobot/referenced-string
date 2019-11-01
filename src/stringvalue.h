#pragma once
#include <cstring>
#include <iostream>

//Egy osztály ami egy stringet tárol, és azt, hogy hány érvényes reference van jelenleg rá (refCount).
//Ha a refCount 0, akkor felszabadítja a karakterlánc helyét a memóriában.
class StringValue {
	int refCount;
	char *data;
public:
	StringValue(const char *);
	void increaseRefCount();
	void decreaseRefCount();
	char *c_str();
	int length();
	int getRefCount();
	char &operator[](int index);
	~StringValue();
};
