#include "mystring.h"

std::map<const char *, StringValue *> MyString::stringMap;

void MyString::decreaseStringRef() {
	string->decreaseRefCount();
	if (string->getRefCount() == 0) {
		stringMap.erase(string->c_str());
		delete string;
	}
}

void MyString::initStringValue(const char * src) {
	if (stringMap.count(src) > 0) {
		string = stringMap[src];
		string->increaseRefCount();
	} else {
		string = new StringValue{src};
		stringMap[src] = string;
	}
}

MyString::MyString(const char *src) {
	initStringValue(src);
}

MyString::MyString(const MyString &other) {
	string = other.string;
	string->increaseRefCount();
}

MyString::MyString(MyString &&other) noexcept {
	string = other.string;
	other.string = nullptr;
}

MyString &MyString::operator=(MyString &&other) noexcept {
	if (this != &other) {
		decreaseStringRef();
		string = other.string;
		other.string = nullptr;
	}
	return *this;
}

char &MyString::operator[](int index) const {
	return (*string)[index];
}

MyString &MyString::operator=(const MyString &other) {
	decreaseStringRef();
	string = other.string;
	string->increaseRefCount();
	return *this;
}

//TODO első szorgalmi

StringProxy MyString::operator[](int index) {
	return StringProxy{this, index};
}

/*
char &MyString::operator[](int index) {
	if (string->getRefCount() == 1) return (*string)[index]; //ha csak egy reference van a stringre, akkor felesleges lemásolni
	decreaseStringRef();
	string = new StringValue{string->c_str()};
	return (*string)[index];
}
*/

void MyString::replaceChar(int index, char c) {
	char *tempString = new char[length() + 1];
	strcpy(tempString, string->c_str());
	decreaseStringRef();
	tempString[index] = c;
	initStringValue(tempString);
	delete[] tempString;
}

char *MyString::c_str() {
	return string->c_str();
}

int MyString::length() {
	return string->length();
}

MyString::~MyString() {
	if (string != nullptr) decreaseStringRef();
}

//operator overloadok

MyString operator+(MyString s1, MyString s2) {
	char *tempString = new char[s1.length() + s2.length() + 1];
	strcpy(tempString, s1.c_str());
	strcat(tempString, s2.c_str());
	MyString retString(tempString);
	delete[] tempString;
	return retString;
}

MyString &operator+=(MyString &s1, MyString s2) {
	return s1 = s1 + s2;
}

MyString operator+(MyString s, char c) {
	char *tempString = new char[s.length() + 2]; //+ 2, mert egy a charnak, egy meg a lezáró 0nak
	strcpy(tempString, s.c_str());
	tempString[s.length()] = c;
	tempString[s.length() + 1] = 0;
	MyString retString(tempString);
	delete[] tempString;
	return retString;
}

MyString &operator+=(MyString &s, char c) {
	return s = s + c;
}

std::ostream &operator<<(std::ostream &os, MyString s) {
	return os << s.c_str();
}

std::istream &operator>>(std::istream &is, MyString &s) {
	const int stringSizeIncrement = 10;
	int stringSize = stringSizeIncrement + s.length(); //elég helyet foglalunk ahhoz, hogy beférjen a mostani string + még néhány karakter
	char *tempString = new char[stringSize]; //ez lesz az új memóriahelye a stringünknek
	strcpy(tempString, s.string->c_str()); //belemásoljuk a régi string tartalmát az elejére

	char c;
	int counter = s.length(); //ez tartja számon hogy éppen hol tartunk a stringben
	while (is.get(c)) {
		tempString[counter++] = c;
		if (is.peek() == EOF) break; // ha a kövi karakter EOF akkor ne olvassa tovább
		if (isspace(c)) break;

		if (counter == stringSize) { //ha betelik a stringnek foglalt memóriaterület, akkor nagyobbat kell foglalnunk
			char *newTempString = new char[stringSize + stringSizeIncrement];
			memcpy(newTempString, tempString, stringSize);
			stringSize += stringSizeIncrement;
			delete[] tempString;
			tempString = newTempString;
		}
	}
	tempString[counter] = 0; //lezáró 0
	s.decreaseStringRef();
	s.string = new StringValue{tempString};
	delete[] tempString;
	return is;
}
