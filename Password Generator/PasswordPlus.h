#pragma once
#ifndef PASSWORDPLUS_H
#define PASSWORDPLUS_H

#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include "PasswordBasic.h"
#include "PasswordPlus.h"
using namespace std;

class PasswordPlus : PasswordBasic
{
	friend ostream& operator<<(ostream&, PasswordPlus&);
private:
	char* Exclude; //The DAM array that will hold the excluded chatracters
	int ExcludeSize; //The Size of the Exclusion Array
	string UserName; //User has the option to include Account UserName
	string AccountType; //User has the option to include what kind of account it is 
	string Comment; //user has the option to include a comment
	ofstream UserFile;
	string FileName;

	PasswordPlus& SetFileName(string); //Private function that updates the name of the file when a new one is opened/ start of Object
	PasswordPlus& SetExclusionSize(int); //Updates the size of the exclusions size variable
	const bool ExcludeCheck(char); //utility function

public:
	PasswordPlus(string = "PasswordPlus.txt", string = "Admin", string = "",bool = 0, int = 8, int = 5);
	~PasswordPlus();
	
	string GeneratePassword(int = 0); //Generates password from the 8 options availeble
	int RatePassword();  //This Function rates the newly generated password
	int RatePassword(string); //This function rates an user input password

	void SaveToFile(); //Saves password To File;
	bool NewFile(string, bool = 0); //Opens a new file, could be an exiting or new file 0 = NewFile, 1 = Exsisting File

	PasswordPlus& SetUserName(string); //Sets the username
	PasswordPlus& SetAccountType(string); //Sets account type 
	PasswordPlus& AddComment(string); //updates comment variable
	const int GetExlusionSize();
	const string GetUserName();
	const string GetAccountType();
	const string GetComment();
	const string GetFileName();
	const string GetPassword();
	void ChangeLength(int); //password length inherited, changes the length of password

	PasswordPlus& ChangeExcusionSize(bool = false ,int = 10); //Creates a new DAM array true = Hold previos exclusions, fasle = delete previos variables
	bool AddExclusion(char);
	bool RemoveExclusion(char);
	const void PrintExclusions();

};
#endif