#include "stringvalue.h"

StringValue::StringValue(const char *src) {
	data = new char[strlen(src) + 1];
	strcpy(data, src);
	refCount = 1;
}

void StringValue::increaseRefCount() {
	refCount++;
}

void StringValue::decreaseRefCount() {
	refCount--;
}

char *StringValue::c_str() {
	return data;
}

int StringValue::length() {
	return strlen(data);
}

int StringValue::getRefCount() {
	return refCount;
}

char &StringValue::operator[](int index) {
	return data[index];
}

StringValue::~StringValue() {
	delete[] data;
}
