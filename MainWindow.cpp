#include "MainWindow.h"

MainWindow :: MainWindow(string database)
{
	generateDatabase(database);
	mainWidget = new QWidget(this);
	mainLayout = new QVBoxLayout();
	topBarLayout = new QHBoxLayout();
	lowerBarLayout = new QHBoxLayout();
	buttonLayout = new QVBoxLayout();
	weaponList = new QListWidget();
	selectedList = new QListWidget();
	resultsList = new QListWidget();
	addWeapon = new QPushButton("Add Weapon");
	showResults = new QPushButton("Show Results");
	//Stack buttons vertically
	buttonLayout->addWidget(addWeapon);
	buttonLayout->addWidget(showResults);
	//Add to Top bar
	//topBarLayout->addWidget(weaponList);
	//topBarLayout->addWidget(selectedList);
	topBarLayout->addLayout(buttonLayout);
	//Add to Bottombar
	lowerBarLayout->addWidget(resultsList);
	//Set as main layout
	mainLayout->addLayout(topBarLayout);
	//mainLayout->addLayout(lowerBarLayout);
	mainWidget->setLayout(mainLayout);

	QObject::connect(addWeapon, SIGNAL(clicked()), this, SLOT(addWeapons()));
	QObject::connect(showResults, SIGNAL(clicked()), this, SLOT(showSearchResults()));
}
MainWindow :: ~MainWindow(){}
//Converts a number to a string
//Returns a string
string MainWindow :: toString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
void MainWindow :: addWeapons()
{

}
void MainWindow :: showSearchResults()
{

}
void MainWindow :: generateDatabase(string database)
{
	ifstream ifile("database.txt"); //Load Database
	if(ifile.fail())
	{
		cout << "Unable to open Weapon Database" << endl;
	}
	else
	{
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
	}
	ifile.close();
}