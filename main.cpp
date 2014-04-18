/*
 * main.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: shist_000
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "lib/quicksort.h"
using namespace std;

int main(int argc, char * argv[])
{
	map<string,vector<string> > lookup;
	char* dataBase = argv[1];
	char* inventory = argv[2];
	ifstream ifile(dataBase);
	string key = "";
	vector<string> skins;
	vector<Case> caseList;
	if(ifile.fail())
	{
		cout << "Unable to open Weapon Database" << endl;
		return 1;
	}
	while(!ifile.eof()) //Read in the database
	{
		string type;
		ifile >> type;
		if(type == "~")
		{
			if(key != "")
			{
				lookup[key] = skins;
				skins.clear();
			}
			ifile >> key;
			Case buff;
			buff.name = key;
			buff.weapons = 0;
			caseList.push_back(buff);
		}
		else if(type == "!")
		{
			string skin;
			ifile >> skin;
			skins.push_back(skin);
		}
	}
	ifile.close();
	ifile.open(inventory);
	if(ifile.fail())
	{
		cout << "Unable to open User inventory" << endl;
		return 2;
	}
	vector<string> allUserSkins;
	while(!ifile.eof())//Read in the users inventory
	{
		string skin;
		ifile >> skin;
		allUserSkins.push_back(skin);
		for(unsigned int i = 0; i < caseList.size(); i++)
		{
			vector<string>possibleMatches = lookup[caseList[i].name];
			for(unsigned int j = 0; j < possibleMatches.size(); j++)
			{
				if(skin == possibleMatches[j])
				{
					caseList[i].userWeapons.push_back(skin);
					caseList[i].weapons++;
				}
			}
		}
	}
	ifile.close();
	Case* cases = new Case[caseList.size()];
	string* userSkins = new string[allUserSkins.size()];
	for(unsigned int i = 0; i < caseList.size();i++)
	{
		cases[i] = caseList[i];
	}
	for(unsigned int i = 0; i < allUserSkins.size();i++)
	{
		userSkins[i] = allUserSkins[i];
	}
	caseComp compare;
	stringComp strcompare;
	QuickSort<Case,caseComp> sort;
	QuickSort<string,stringComp> stringsort;
	cases = sort.randomQuickSort(cases,caseList.size(),compare);
	userSkins = stringsort.randomQuickSort(userSkins,allUserSkins.size(),strcompare);
	for(unsigned int i = 0; i < caseList.size(); i++)
	{
		if(cases[caseList.size() -1 -i].weapons > 2)
		{
			cout << "Case/Quality: " << cases[caseList.size() -1 -i].name  << endl;
			cout << "Num of Weapons: " << cases[caseList.size() -1 -i].weapons << endl;
			cout << "Weapons: " << endl;
			for(unsigned int j = 0; j < cases[caseList.size() -1 -i].userWeapons.size();j++)
				cout << cases[caseList.size() -1 -i].userWeapons[j] << endl;
			cout << endl;
		}
	}
	ofstream ofile(inventory);
	for(unsigned int i = 1; i < allUserSkins.size();i++)
	{
			ofile << userSkins[i] << "\r\n"; //Just "\n" for linux
	}
	ofile.close();
	delete [] userSkins;
	delete [] cases;
}


