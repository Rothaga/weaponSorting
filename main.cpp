/*
 * main.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: Allen Shi
 */
 //Input output streams
#include <iostream>
#include <sstream>
#include <fstream>

 //Data structures
#include <string>
#include <vector>
#include <map>

 //Errors
#include <exception>
using namespace std;

//GUI
#include <QApplication>
//#include "MainWindow.h"

//Converts a number to a string
//Returns a string
string toString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
int main(int argc, char * argv[])
{
	QApplication app(argc, argv);
	ifstream ifile("database.txt"); //Load Database
	vector<string> caseWeapons, caseList;
	vector<string> userWeapons;
	string caseName = "";
	string uniqueId = "";
	map<string,vector<string> > lookup;
	if(ifile.fail())
	{
		cout << "Unable to open Weapon Database" << endl;
		return 1;
	}
	while(!ifile.eof()) //Read in the database
	{
		string isCase;
		int quality;
		ifile >> isCase;
		if(isCase == "~")
		{
			//Reached new Case,
			// push back the list of weapons and 
			//get ready for new inputs
			if(uniqueId != "") 
			{
				lookup[uniqueId] = caseWeapons;
				caseWeapons.clear();
			}
			ifile >> caseName >> quality;
			uniqueId = caseName + toString(quality);
			caseList.push_back(uniqueId);
		}
		else if(isCase == "!") //Adding a skin to a case
		{
			string skin;
			ifile >> skin;
			caseWeapons.push_back(skin);
		}
	}
	ifile.close();
	ifile.open("weapons.txt");
	while(!ifile.eof()) // Read in User provided weapons
	{
		string weaponInput;
		ifile >> weaponInput;
		userWeapons.push_back(weaponInput);
	}
	ifile.close();
	//Calculate what type of quality from first skin
	string firstCaseName;
	vector<string> userCases;
	for(int h = 0; h < userWeapons.size(); h++)
	{
		for(int i = 0; i < caseList.size();i++)
		{
			vector<string> currCase = lookup[caseList[i]];
			for(int j = 0; j < currCase.size(); j++)
			{
				if(currCase[j] == userWeapons[0])
					firstCaseName = caseList[i];
				if(currCase[j] == userWeapons[h])
				{
					string temp = caseList[i];
					temp = temp.substr(0,temp.length()-1);
					userCases.push_back(temp);
				}	
			}
		}
	}
	ofstream ofile("upgrade.txt");
	//Add weaponQuality to the end of the casename to figure out next tier weapons
	int firstQuality = firstCaseName[firstCaseName.length() - 1] - '0';//convert the char into an int;
	for(int i = 0; i < userCases.size(); i++)
	{
		try
		{
			string name = userCases[i] + toString(firstQuality+1);
			vector<string> outcomes = lookup[name];
			for(int j = 0; j< outcomes.size(); j++)
			{
				ofile << outcomes[j] << endl;
			}
		}
		catch(exception &e)
		{
		}
	}
	ofile.close();
}


