#pragma once
#ifndef PASSWORDBASIC_H
#define PASSWORDBASIC_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "PasswordBasic.h"
using namespace std;

class PasswordBasic
{
	friend ostream& operator<<(ostream&, PasswordBasic&);
private:

	int passSize;
	int ArrSizeULS;
	int ArrSizeN;
	const char UpperArr[26]; //contains upper case letters
	const char LowerArr[26]; //contains lowercase letters 
	const char NumberArr[10]; //contains numbers 0-9
	const char  SymbolArr[26]; // contains symbols

	string FinalPassword;

protected:
	char* PasswordUser;  //Where ther characters will be added to to create a 8 length password 
//this Variables has to go public because the inherited function GeneratePassword needed it 
	const int GetArrSizeULS();
	const int GetArrSizeN();
	const int GetPassSize();
	void ChangeLength(int);
	// The Get Functions return : when the position requested is out of bounds
	const char GetUpper(int); //Get Function
	const char GetLower(int); // get function
	const char GetNumber(int); // get function
	const char GetSymbol(int); // get function
	const int GetRandN();
	const int GetRandULS();

public:
	PasswordBasic(); //constructor
	~PasswordBasic();
	const string ConvertChartoString(); //converts PasswordUser to string, void the need of returning an array
																	//Sets FinalPassword to the converted charArr
	string GeneratePassword(); // generates the password with the 4 arrays
	const string GetPassword(); // get function return FinalPassword(string)
};
#endif // !PASSWORDBASIC_H
