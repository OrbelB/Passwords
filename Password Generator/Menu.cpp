#include <iostream>
#include <fstream>
#include <string>
#include "Menu.h"
using namespace std;
Menu::Menu(string File)
{
	if (OpenFile(File))
	{
		inFile >> Size;
		MenuArr = new string[GetSize()];
		ReadFile();
	}
	else
	{
		cout << "Program will now close" << endl;
		exit(1);
	}
}
Menu::~Menu()
{
	delete[] MenuArr;
	inFile.close();
}
ostream& operator<<(ostream &out, Menu &men)
{
	for (int i = 0; i < men.GetSize(); i++)
	{
		out << men.MenuArr[i]; 
	}
	return out;
}
bool Menu::OpenFile(string File)
{
	inFile.open(File);
	if (!inFile)
	{
		cout << "Menu File could not be found" << endl << endl;
		Help();
		return false;
	}
	return true;
}
void Menu::ReadFile()
{
	char tempChar[100];
	string STRtemp;
	for (int i = 0; i < GetSize(); i++)
	{
		inFile.getline(tempChar, 101, ';');
		STRtemp =  tempChar;
		MenuArr[i] = STRtemp;
	}
}
const void Menu::Help()
{
	cout << "How to use Menu" << endl;
	cout << "Have the correct file(that exsist)" << endl;
	cout << "The first line of the file should include the number of lines the Menu will have" << endl;
	cout << "Next will be the menu options followed by a ;(100 characters or less)" << endl;
	cout << "Lastly, The Menu Class does not automatically call a function selected, User has to sepecify in main" << endl;
}
const int Menu::GetSize()
{
	return Size;
}