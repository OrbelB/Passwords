
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include "PasswordBasic.h"
#include "PasswordPlus.h"
using namespace std;

PasswordPlus::PasswordPlus(string File,string UserN, string acctype, bool OpenType, int PassSize, int Exclu):PasswordBasic()
{
	SetFileName(File)
		.SetUserName(UserN)
		.SetAccountType(acctype)
		.ChangeExcusionSize(false, Exclu)
		.SetExclusionSize(Exclu)
		.AddComment("Created Using PasswordPlus");
		ChangeLength(PassSize);

	NewFile(GetFileName(), OpenType);
}
PasswordPlus::~PasswordPlus()
{
	delete[] Exclude;
	UserFile.close();
}


ostream& operator<<(ostream& out, PasswordPlus& pass)
{
	out << endl;
	out << pass.GetAccountType() << endl;
	out << "User Name: " << pass.GetUserName() << endl;
	out << "Password: " << pass.GetPassword() << endl;
	out << "Comment: " << endl << pass.GetComment() << endl;
	out << "File Being Used " << pass.GetFileName() << endl;
	return out;
}


//SetFunctions of PasswordPlus class
//SetFileName is a private function
PasswordPlus& PasswordPlus::SetFileName(string F) //Private Function, changes the FileName
{
	FileName = F;
	return *this;
} 
PasswordPlus& PasswordPlus::SetUserName(string name)
{
	UserName = name;
	return *this;
}
PasswordPlus& PasswordPlus::SetAccountType(string Acc)
{
	AccountType = Acc;
	return *this;
}

PasswordPlus& PasswordPlus::AddComment(string Acc)
{
	Comment = Acc;
	return *this;
}

//Get Functions of PlassswordPlus class
const int PasswordPlus::GetExlusionSize()
{
	return ExcludeSize;
}
const string PasswordPlus::GetUserName()
{
	return UserName;
}
const string PasswordPlus::GetAccountType()
{
	return AccountType;
}
const string PasswordPlus::GetComment()
{
	return Comment;
}
const string PasswordPlus::GetFileName()
{
	return FileName;
} 
const string PasswordPlus::GetPassword()
{
	string f = PasswordBasic::GetPassword();
	return f;
}
//File Functions for PasswordPlus
void PasswordPlus::SaveToFile()
{
	UserFile << GetAccountType() << endl;
	UserFile << "UserName: " << GetUserName() << endl;
	UserFile << "Password: " << GetPassword() << endl;
	UserFile << "Comment: " << endl << GetComment() << endl;
	UserFile << "-------------------------------------------------------------" << endl;
}
bool PasswordPlus::NewFile(string Name, bool mode)
{
	if (UserFile)
	{
		UserFile.close();
	}
	SetFileName(Name);
	if (mode)
	{
		UserFile.open(GetFileName(), ios::app);
		if (UserFile)
		{
			return true;
		}
		return false;
	}
	else
	{
		UserFile.open(GetFileName());
		if (UserFile)
		{
			return true;
		}
		return false;
	}
}
//Exclusion functions of PasswordPlus class
//Creates a new DAM array true = Hold previos exclusions, fasle = delete previos variables
const bool PasswordPlus::ExcludeCheck(char ch)
{
	for (int i = 0; i < GetExlusionSize(); i++)
	{
		if (Exclude[i] == ch)
		{
			return false;
		}
	}
	return true;
}
PasswordPlus& PasswordPlus::ChangeExcusionSize(bool keep, int newsz)
{
	if (keep)
	{
		char* temp = new char[newsz];
		for (int i = 0; i < newsz; i++)
		{
			temp[i] = ':';
		}
		if (newsz > GetExlusionSize())
		{
			for (int i = 0; i < GetExlusionSize(); i++)
			{
				temp[i] = Exclude[i];
			}
		}
		else
		{
			cout << endl << "Some Exclusion may have been lost" << endl;
			for (int i = 0; i <newsz; i++)
			{
				temp[i] = Exclude[i];
			}
		}
		delete[] Exclude;
		Exclude = temp;
		SetExclusionSize(newsz);
	}
	else
	{
		delete[] Exclude;
		SetExclusionSize(newsz);
		Exclude = new char[GetExlusionSize()];
		for (int i = 0; i < GetExlusionSize(); i++)
		{
			Exclude[i] = ':';
		}
	}
	return *this;
}
bool PasswordPlus::AddExclusion(char Ex)
{
	if (ExcludeCheck(Ex))
	{
		for (int i = 0; i < GetExlusionSize(); i++)
		{
			if (Exclude[i] == ':')
			{
				Exclude[i] = Ex;
				return true;
			}
		}
	}
	return false;
}
bool PasswordPlus::RemoveExclusion(char ch)
{
	for (int i = 0; i < GetExlusionSize(); i++)
	{
		if (Exclude[i] == ch)
		{
			Exclude[i] = ':';
			return true;
		}
	}
	return false;
}
const void PasswordPlus::PrintExclusions()
{
	cout << endl << "The Current Exclusions are: ";
	for (int i = 0; i < GetExlusionSize(); i++)
	{
		if (Exclude[i] != ':')
		{
			cout << Exclude[i] << " ";
		}
	}
	cout << endl;
}
PasswordPlus& PasswordPlus::SetExclusionSize(int siz) //updates the member variable of the new size
{
	ExcludeSize = siz;
	return *this;
}

//Password Generation functions for PasswordPlus
void PasswordPlus::ChangeLength(int size)
{
	PasswordBasic::ChangeLength(size);
}
string PasswordPlus::GeneratePassword(int sel)
{
	bool Number = false;
	bool UpperL = false;
	bool LowerL = false;
	bool Symbol = false;
	int PassCapasity = 0;
	int choice;
	int num = 0;
	char character;
	if (sel == 0)
	{
		int temp = GetPassSize();
		ChangeLength(8);
		string password = PasswordBasic::GeneratePassword();
		ChangeLength(temp);
		return password;
	}
	if (sel == 1 || sel == 4 || sel == 5 || sel == 6 || sel == 7)
	{
		Number = true;
		if (sel == 4 || sel == 5 || sel == 6) //selections that include numbers in password
		{
			if (sel == 4) //numbers + lower letters
			{
				LowerL = true;
			}
			else if (sel == 5) //numbers + Upper letters
			{
				UpperL = true;
			}
			else if (sel == 6) //numbers + Lower + Upper Letters 
			{
				UpperL = true;
				LowerL = true;
			}
		}
		else if (sel == 7) //Numbers + Symbols
		{
			Symbol = true;
		}
	}
	else if (sel == 2 || sel == 3 || sel == 8)
	{
		if (sel != 8)
		{
			if (sel == 2)
			{
				LowerL = true;
			}
			else
			{
				UpperL = true;
			}
		}
		else
		{
			UpperL = true; 
			LowerL = true;
			Symbol = true;
		}
	}
	else
	{
		LowerL = true;
		UpperL = true;
		Number = true;
		Symbol = true;
	}
	while (PassCapasity != GetPassSize())
	{
		choice = rand() % 4;
		if(choice == 0 && Number)
		{
			character = GetNumber(rand() % GetArrSizeN());
			if (ExcludeCheck(character))
			{
				PasswordUser[PassCapasity] = character;
				PassCapasity++;
			}
		}
		else if (choice == 1 && UpperL)
		{
			character = GetUpper(rand() % GetArrSizeULS());
			if (ExcludeCheck(character))
			{
				PasswordUser[PassCapasity] = character;
				PassCapasity++;
			}
		}
		else if (choice == 2 && LowerL)
		{
			character = GetLower(rand() % GetArrSizeULS());
			if (ExcludeCheck(character))
			{
				PasswordUser[PassCapasity] = character;
				PassCapasity++;
			}
		}
		else if (choice == 3 && Symbol)
		{
			character = GetSymbol(rand() % GetArrSizeULS());
			if (ExcludeCheck(character))
			{
				PasswordUser[PassCapasity] = character;
				PassCapasity++;
			}
		}
	} 
	return ConvertChartoString();
}
int  PasswordPlus::RatePassword()
{
	int score = RatePassword(GetPassword());
	return score;
}
int PasswordPlus::RatePassword(string pass)
{
	int score = 0;
	int NLowL = 0;
	int NUpL = 0;
	int NNum = 0;
	int NSym = 0;
	bool found = false; 
	string strScore;
	if (pass.size() >= 8)
	{
		score += 3;
	}
	for (int i = 0; i < pass.size(); i++)
	{
		found = false;
		char ch = pass[i];
		if (!found)
		{
			for (int U = 0; U < GetArrSizeULS(); U++)
			{
				if (ch == GetUpper(U))
				{
					NUpL++;
					found = true;
				}
				else if (ch == GetLower(U))
				{
					NLowL++;
					found = true;
				}
			}
		}
		if (!found)
		{
			for (int U = 0; U < GetArrSizeN(); U++)
			{
				if (ch == GetNumber(U))
				{
					NNum++;
					found = true;
				}
			}
		}
		if (!found)
		{
			for (int U = 0; U < GetArrSizeULS(); U++)
			{
				if (ch == GetSymbol(U))
				{
					NSym++;
					found = true;
				}
			}
		}
	}
	if (NUpL >= 1)
	{
		score++;
	}
	if (NLowL >= 1)
	{
		score++;
	}
	if (NNum >= 2)
	{
		score += 2;
	}
	if (NSym >= 3)
	{
		score += 3;
	}
	return score;
}

/*
	switch (sel)
	{
		case 0:
		{
			int temp = GetPassSize();
			ChangeLength(8);
			string password = PasswordBasic::GeneratePassword();
			ChangeLength(temp);
			return password;
			break;
		}
		case 1:
		{
			for (int i = 0; i < GetPassSize(); i++)
			{
				PasswordUser[i] = GetNumber(GetRandN());
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < GetPassSize(); i++)
			{
				PasswordUser[i] = GetLower(GetRandULS());
			}
			break;
		}
		case 3:
		{
			for (int i = 0; i < GetPassSize(); i++)
			{
				PasswordUser[i] = GetUpper(GetRandULS());
			}
			break;
		}
		case 4:
		{
			int Choice;
			for (int i = 0; i < GetPassSize(); i++)
			{
				Choice = rand() % 2;
				switch (Choice)
				{
					case 0: //get a random character from UpperArr
					{
						PasswordUser[i] = GetNumber(GetRandN());
						break;
					}
					case 1:
					{
						PasswordUser[i] = GetLower(GetRandULS());
						break;
					}
				}
			}
			break;
		}
		case 5:
		{
			int Choice;
			for (int i = 0; i < GetPassSize(); i++)
			{
				Choice = rand() % 2;
				switch (Choice)
				{
					case 0: //get a random character from UpperArr
					{
						PasswordUser[i] = GetNumber(GetRandN());
						break;
					}
					case 1:
					{
						PasswordUser[i] = GetUpper(GetRandULS());
						break;
					}
				}
			}
			break;
		}
		case 6:
		{
			int Choice;
			for (int i = 0; i < GetPassSize(); i++)
			{
				Choice = rand() % 3;
				switch (Choice)
				{
					case 0: //get a random character from UpperArr
					{
						PasswordUser[i] = GetNumber(GetRandN());
						break;
					}
					case 1:
					{
						PasswordUser[i] = GetLower(GetRandULS());
						break;
					}
					case 2:
					{
						PasswordUser[i] = GetUpper(GetRandULS());
						break;
					}
				}
			}
			break;
		}
		case 7:
		{
			int Choice;
			for (int i = 0; i < GetPassSize(); i++)
			{
				Choice = rand() % 2;
				switch (Choice)
				{
					case 0: //get a random character from UpperArr
					{
						PasswordUser[i] = GetNumber(GetRandN());
						break;
					}
					case 1:
					{
						PasswordUser[i] = GetSymbol(GetRandULS());
						break;
					}
				}
			}
			break;
		}
		case 8:
		{
			int Choice;
			for (int i = 0; i < GetPassSize(); i++)
			{
				Choice = rand() % 2;
				switch (Choice)
				{
				case 0: //get a random character from UpperArr
				{
					PasswordUser[i] = GetLower(GetRandULS());
					break;
				}
				case 1:
				{
					PasswordUser[i] = GetSymbol(GetRandULS());
					break;
				}
				case 2:
				{
					PasswordUser[i] = GetUpper(GetRandULS());
				}
				}
			}
			break;
		}
		case 9:
		{
			PasswordBasic::GeneratePassword();
			break;
		}
	}
	return ConvertChartoString();
*/