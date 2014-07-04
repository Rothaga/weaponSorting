#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT Stuff
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QString>

//Data Structures
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
class MainWindow: public QMainWindow{
	Q_OBJECT

	public:
		MainWindow(string database, QWidget *parent = 0);
		~MainWindow();

	private slots:
		void showSearchResults();
		void addWeapons();
		void removeWeapons();

	private:
		void generateDatabase(string database);
		void sortDatabase();
		vector<string> mergeSort(vector<string> myVector);
		vector<string> merge(vector<string> left, vector<string> right);
		string toString(int number);

		vector<string> caseWeapons, caseList;
		vector<string> userWeapons, masterList;
		string caseName = "";
		string uniqueId = "";
		map<string,vector<string> > lookup;
		//QT STuff
		QWidget *mainWidget;
		QVBoxLayout *mainLayout;
		QHBoxLayout *topBarLayout;
		QHBoxLayout *lowerBarLayout;
		QHBoxLayout *labelLayout;
		QVBoxLayout *buttonLayout;
		QListWidget *weaponList;
		QListWidget *resultsList;
		QListWidget *selectedList;
		QPushButton *addWeapon;
		QPushButton *removeWeapon;
		QPushButton *showResults;
		QLabel *databaseLabel;
		QLabel *selectedLabel;
		QLabel *resultsLabel;

};
#endif