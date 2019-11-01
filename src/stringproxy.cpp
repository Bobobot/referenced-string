#include "stringproxy.h"

char StringProxy::operator=(const char c) {
	myString->replaceChar(index, c);
	return c;
}

StringProxy::operator char() {
	return myString->c_str()[index];
}
