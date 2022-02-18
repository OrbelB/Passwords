#pragma once
#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <string>
#include<iostream>
#include "Menu.h"
using namespace std;

class Menu
{
	friend ostream& operator<<(ostream&, Menu&);
private: 
	string* MenuArr; //the DAM array that will hold the menu options read from file
	int Size; //size of MenuArr
	ifstream inFile;

	bool OpenFile(string); //Opens the file, returns true if succeful
	void ReadFile(); //Reades the file, filles MenuArr with the specified lines

public: 
	Menu(string); //Passing in the file name
	~Menu(); //Deletes DAM array
	const void Help(); // A help function that explains how to use this class 
	const int GetSize();
};
#endif
