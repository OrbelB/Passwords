#include <iostream>
#include <ctime>
#include <sstream>
#include "PasswordBasic.h"
#include "PasswordPlus.h"
#include "Menu.h"
using namespace std;

int main()
{
	
	Menu Main("Main_Menu.txt");
	Menu ChangeInfo("Change_Information.txt");
	Menu ChangeFile("Change_File.txt");
	Menu Exclusion("Exclusion.txt");
	Menu GPassword("GPassword.txt");
	Menu RatePassword("RatePassword.txt");
	PasswordPlus UserPassword;

	int TSize;
	bool OP = false;
	string choice = "No";
	string info;
	//Start of Menu
	cout << "Welcome To PasswordPlus." << endl;
	cout << "Skip personal info? (Yes || No): " << endl;
	getline(cin, choice);
	if (choice == "No")
	{
		cout << "UserName? ";
		getline(cin, info);
		UserPassword.SetUserName(info);
		cout << "Acount type? ";
		getline(cin, info);
		UserPassword.SetAccountType(info);
		cout << "Password Size? ";
		cin >> TSize;
		UserPassword.ChangeLength(TSize);
		cin.ignore();
		cout << "File Name? ";
		getline(cin, info);
		cout << "Open Type? (0 = new file || 1 = Exsisting File) ";
		cin >> OP;
		UserPassword.NewFile(info, OP);
	}
	char UserSelection = ' ';
	do
	{
		//cin.ignore();
		cout << Main;
		cout  << ":: ";
		cin >> UserSelection;
		switch (UserSelection)
		{
			case '1':
			{
				cout << UserPassword;
				break;
			}
			case '2':
			{
				do
				{
					cout << ChangeInfo;
					cout << endl << ":: ";
					cin >> UserSelection;
					cin.ignore();
					switch(UserSelection)
					{
						case '1':
						{
							cout << "New User Name? ";
							getline(cin, info);
							UserPassword.SetUserName(info);
							break;
						}
						case '2':
						{
							cout << "New Acount Type? ";
							getline(cin, info);
							UserPassword.SetAccountType(info);
							break;
						}
						case '3':
						{
							cout << "Add Comment? ";
							getline(cin, info);
							UserPassword.AddComment(info);
							break;
						}
					}
				} while (UserSelection != '4');
				break;
			}
			case '3':
			{
				do
				{
					cout << ChangeFile;
					cout << endl << ":: ";
					cin >> UserSelection;
					cin.ignore();
					if (UserSelection == '1')
					{
						UserPassword.SaveToFile();
						cout << "Password has been saved to file " << UserPassword.GetFileName();
					}
					else if (UserSelection == '2')
					{
						cout << "File Name? ";
						getline(cin, info);
						cout << "Open Type? (0 = new file || 1 = Exsisting File) ";
						cin >> OP;
						UserPassword.NewFile(info, OP);
					}
				} while (UserSelection != '3');
				break;
			}
			case '4':
			{
				char EX = ' ';
				do
				{
					cout << Exclusion;
					cout << endl << ":: ";
					cin >> UserSelection;
					cin.ignore();
					switch (UserSelection)
					{
						case '1':
						{
							cout << "Add Exclusions? ";
							cin >> EX;
							if (UserPassword.AddExclusion(EX))
							{
								cout << "Exclusion Accepted" << endl;
							}
							else
							{
								cout << "Failed to add Exclusion(Array may be full)" << endl;
							}
							break;
						}
						case '2':
						{
							cout << "Delete Exclusion? "; 
							cin >> EX;
							if (UserPassword.RemoveExclusion(EX))
							{
								cout << "Exclusion Deleted" << endl;
							}
							else
							{
								cout << "Failed to Delete Exclusion" << endl;
							}
							break;
						}
						case '3':
						{
							cout << "New Exclusion Array Size? ";
							cin >> TSize;
							cout << "0 = Delete previos Exclusions || 1 = Keep previos Exclusions" << endl;
							cout << "Keep previos Exclusion in new Exclusion array? ";
							cin >> OP;
							UserPassword.ChangeExcusionSize(OP, TSize);
							cout << "The Size of the Exclusion is: " << UserPassword.GetExlusionSize();
							break;
						}
						case '4':
						{
							UserPassword.PrintExclusions();
							break;
						}
						case '5':
						{
							cout << "The Size of the Exclusion is: " << UserPassword.GetExlusionSize();
							break;
						}
					}
				} while (UserSelection != '6');
				break;
			}
			case '5':
			{
				int GPSelection = 0;
				do
				{
					cout << GPassword;
					cout << endl << ":: ";
					cin >> GPSelection;
					if (GPSelection > 0 && GPSelection < 11)
					{
						GPSelection--;
						cout << "The Generated Password is: " << UserPassword.GeneratePassword(GPSelection) << endl;
					}
					else if (GPSelection == 11)
					{
						int tempSize = 0;
						cout << "New Size? ";
						cin >> tempSize;
						UserPassword.ChangeLength(tempSize);
						cout << "The new Size is new " << tempSize;
					}
				} while (GPSelection != 12);
				break;
			}
			case '6':
			{
				do
				{
					cout << RatePassword;
					cout << endl << ":: ";
					cin >> UserSelection;
					cin.ignore();
					if (UserSelection == '1')
					{
						int rating = UserPassword.RatePassword();
						cout << "The rating given is: " << rating << "/10" << endl;
					}
					else if (UserSelection == '2')
					{
						string PersonalPassword = "123";
						cout << "Enter Password to be Rated ";
						getline(cin, PersonalPassword);
						int rating = UserPassword.RatePassword(PersonalPassword);
						cout << "The rating given is: " << rating << "/10" << endl;
					}
				} while (UserSelection != '3');
				break;
			}
		}

	} while (UserSelection != '7');
	cout <<  endl << endl << "Thank You For Using PasswordPlus" << endl << endl;
	system("PAUSE");
	
}
