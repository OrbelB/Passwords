#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "PasswordBasic.h"

using namespace std;
using std::time;

PasswordBasic::PasswordBasic() :UpperArr{ 'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M' }
, LowerArr{ 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m' }
, NumberArr{ '0','1', '2','3','4','5','6','7','8','9' }
, SymbolArr{ '!' ,'?' ,'@' ,'$' ,'%' ,'^' ,'&' ,'*' ,'(' ,')' ,'-' ,'_' ,'+' ,'=' ,'{' ,'}' ,'[' ,']' ,'<' ,'>' ,'/' ,(char)' \\',   (char)' | ', (char)' * ' ,'~', ' ' }
{
	srand( time(NULL));
	FinalPassword = "";
	ArrSizeULS = 26;
	ArrSizeN = 10;
	passSize = 8;
	PasswordUser = new char[GetPassSize()];
}
PasswordBasic::~PasswordBasic()
{
	delete[] PasswordUser;
}

ostream& operator<<(ostream& out, PasswordBasic& pass)
{
	out << "The Password is: " << pass.GetPassword() << endl;
	out << "Generating another password will Delete previos Password" << endl;
	return out;
}
const char PasswordBasic::GetUpper(int pos)
{
	char temp = ':';
	if (pos >= 0 && pos < GetArrSizeULS())
	{
		temp = UpperArr[pos];
	}
	return temp;
}
const char PasswordBasic::GetLower(int pos)
{
	char temp = ':';
	if (pos >= 0 && pos < GetArrSizeULS())
	{
		temp = LowerArr[pos];
	}
	return temp;
}
const char PasswordBasic::GetNumber(int pos)
{
	char temp = ':';
	if (pos >= 0 && pos < GetArrSizeN())
	{
		temp = NumberArr[pos];
	}
	return temp;
}
const char PasswordBasic::GetSymbol(int pos)
{
	char temp = ':';
	if (pos >= 0 && pos < GetArrSizeULS())
	{
		temp = SymbolArr[pos];
	}
	return temp;
}
const string PasswordBasic::GetPassword()
{
	return FinalPassword;
}
const int PasswordBasic::GetArrSizeULS()
{
	return ArrSizeULS;
}
const int PasswordBasic::GetArrSizeN()
{
	return ArrSizeN;
}
const int PasswordBasic::GetPassSize()
{
	return passSize;
}


const string PasswordBasic::ConvertChartoString()
{
	FinalPassword = "";
	for (int i = 0; i < GetPassSize(); i++)
	{
		FinalPassword += PasswordUser[i];
	}
	return FinalPassword;
}
void PasswordBasic::ChangeLength(int L)
{
	passSize = L;
	delete[] PasswordUser;
	PasswordUser = new char[L];
}

string PasswordBasic::GeneratePassword()
{
	int Choice;
	for (int i = 0; i < GetPassSize();i++)
	{
		Choice = rand() % 4;
		switch (Choice)
		{
		case 0: //get a random character from UpperArr
			{
			PasswordUser[i] = GetUpper(GetRandULS());
			break;
			}
		case 1 :
			{
			PasswordUser[i] = GetLower(GetRandULS());
			break;
			}
		case 2:
			{
			PasswordUser[i] = GetSymbol(GetRandULS());
			break;
			}
		case 3:
			{
			PasswordUser[i] = GetNumber(GetRandN());
			}
		}
	}
	return ConvertChartoString();
}

const int PasswordBasic::GetRandN()
{
	return rand() % GetArrSizeN();
}
const int PasswordBasic::GetRandULS()
{
	return rand() % GetArrSizeULS();
}