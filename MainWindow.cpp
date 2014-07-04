#include "MainWindow.h"
using namespace std;
MainWindow :: MainWindow(string database, QWidget *parent)
{
	generateDatabase(database);
	mainWidget = new QWidget(this);
	mainLayout = new QVBoxLayout();
	topBarLayout = new QHBoxLayout();
	lowerBarLayout = new QHBoxLayout();
	labelLayout = new QHBoxLayout();
	buttonLayout = new QVBoxLayout();
	weaponList = new QListWidget();
	selectedList = new QListWidget();
	resultsList = new QListWidget();
	addWeapon = new QPushButton("Add Weapon");
	removeWeapon = new QPushButton("Remove All Weapons");
	showResults = new QPushButton("Show Results");
	databaseLabel = new QLabel();
	selectedLabel = new QLabel();
	resultsLabel = new QLabel();
	databaseLabel->setText("Weapon Database");
	selectedLabel->setText("Your Weapons");
	resultsLabel->setText("Potential Upgrades");
	//Labels
	labelLayout->addWidget(databaseLabel);
	labelLayout->addWidget(selectedLabel);
	//Stack buttons vertically
	buttonLayout->addWidget(addWeapon);
	buttonLayout->addWidget(removeWeapon);
	buttonLayout->addWidget(showResults);
	//Add to Top bar
	topBarLayout->addWidget(weaponList);
	topBarLayout->addWidget(selectedList);
	topBarLayout->addLayout(buttonLayout);
	//Add to Bottombar
	lowerBarLayout->addWidget(resultsList);
	//Set as main layout
	mainLayout->addLayout(labelLayout);
	mainLayout->addLayout(topBarLayout);
	mainLayout->addWidget(resultsLabel);
	mainLayout->addLayout(lowerBarLayout);
	mainWidget->setLayout(mainLayout);
	mainWidget->adjustSize();

	QObject::connect(addWeapon, SIGNAL(clicked()), this, SLOT(addWeapons()));
	QObject::connect(removeWeapon, SIGNAL(clicked()), this, SLOT(removeWeapons()));
	QObject::connect(showResults, SIGNAL(clicked()), this, SLOT(showSearchResults()));

	sortDatabase();
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
	QString q = weaponList->currentItem()->text();
	string weapon = q.toStdString();
	if(std::find(userWeapons.begin(), userWeapons.end(), weapon) == userWeapons.end())
	{
		selectedList->addItem(q);
		userWeapons.push_back(weapon);
	}
	
}
void MainWindow :: removeWeapons()
{
	selectedList->clear();
	userWeapons.clear();
}
void MainWindow :: showSearchResults()
{
	//Calculate what type of quality from first skin
	resultsList->clear();
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
					userCases.push_back(temp);
				}	
			}
		}
	}
	//Add weapon quality to the end of the casename to figure out next tier weapons
	int firstQuality = firstCaseName[firstCaseName.length() - 1] - '0';//convert the char into an int;
	bool validCombination = true;
	//Check that input is valid
	for(int k = 0; k < userCases.size(); k++)
	{
		string buff = userCases[k];
		int typeQuality = buff[buff.length()- 1] - '0';
		if(typeQuality == 6 || typeQuality != firstQuality)
			validCombination = false;
			
	}
	if(validCombination)
	{
		for(int i = 0; i < userCases.size(); i++)
		{
			string name = userCases[i].substr(0, userCases[i].length() - 1) + toString(firstQuality+1);
			vector<string> outcomes = lookup[name];
			for(int j = 0; j< outcomes.size(); j++)
			{
				resultsList->addItem(QString::fromStdString(outcomes[j]));
			}
		}
	}
	else
		resultsList->addItem(QString::fromStdString("Invalid Combination"));
	
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
				masterList.push_back(skin);
				caseWeapons.push_back(skin);
			}
		}
	}
	ifile.close();
}
vector<string> MainWindow :: mergeSort(vector<string> myVector)
{
	if(myVector.size() < 2)
		return myVector;
	vector<string> left,right;
	int middle = myVector.size()/2;
	for(int i = 0; i < middle; i++)
		left.push_back(myVector[i]);
	for(int j = middle; j < myVector.size(); j++)
		right.push_back(myVector[j]);
	left = mergeSort(left);
	right = mergeSort(right);
	return merge(left,right);
}
vector<string> MainWindow :: merge(vector<string> left, vector<string> right)
{
	vector<string> result;
	while(left.size() > 0 || right.size() > 0)
	{
		if(left.size()> 0 && right.size() > 0)
		{
			if(left[0] < right[0])
			{
				result.push_back(left[0]);
				left.erase(left.begin());
			}
			else
			{
				result.push_back(right[0]);
				right.erase(right.begin());
			}
		}
		else if(left.size() > 0)
		{
			result.push_back(left[0]);
			left.erase(left.begin());
		}
		else
		{
			result.push_back(right[0]);
			right.erase(right.begin());
		}
	}
	return result;
}
void MainWindow :: sortDatabase()
{
	masterList = mergeSort(masterList);
	for(int i =0; i < masterList.size(); i++)
		weaponList->addItem(QString::fromStdString(masterList[i]));
}