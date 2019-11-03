#include <iostream>
#include "mystring.h"

int main() {

	//Régi tesztesetek

	/*
	MyString myString1{}; //paraméter nélküli konstruktor
	MyString myString2{"kacsa"}; //const char* paraméterű konstruktor
	MyString myString3{myString2}; //másoló konstruktor
	MyString myString4{MyString{"kacsakacsa"}}; //mozgató konstruktor

	myString1 = "ascak"; //const char* paraméterű operator=
	myString1 = MyString("liba"); //mozgató értékadás
	myString1 = myString2; //const MyString& paraméterű operator=

	//a myString1 és myString2 most ugyanarra a stringre mutat, viszont ha meghívjuk az operator[]-t az egyiken, akkor lemásolódik
	myString1[0] = 'l';
	std::cout << myString1[0] << std::endl; //ez most már l
	std::cout << myString2[0] << std::endl; //még mindig k-t ír ki
	std::cout << myString2.length() << std::endl; //a kacsa 5 karakterből áll

	//a maradék operator overloadok
	std::cout << myString1 << std::endl; //operator<<
	std::cout << myString1 + myString2 << std::endl; //MyString paraméterű operator+
	myString1 += myString2; //MyString paraméterű operator+=
	std::cout << myString1 << std::endl;
	std::cout << myString1 + 'k' << std::endl; //char paraméterű operator+
	myString1 += 'l'; //char paraméterű operator+=
	std::cout << myString1 << std::endl;

	std::cin >> myString1; //operator>>
	std::cout << myString1 << std::endl;
	*/
	//Új tesztesetek

	MyString kacsaString1{"kacsa"};
	MyString kacsaString2{"kacsa"};
	
	MyString a = "hello";
	MyString b = a;
	std::cout << b[1] << std::endl;          /* e */

	a[1] = 'a';
	b[1] = b[4];
	std::cout << a << " " << b << std::endl; /* hallo hello */
}