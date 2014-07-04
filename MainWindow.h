#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT Stuff
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

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
		MainWindow(string database);
		~MainWindow();

	private slots:
		void showSearchResults();
		void addWeapons();

	private:
		void generateDatabase(string database);
		string toString(int number);

		vector<string> caseWeapons, caseList;
		vector<string> userWeapons;
		string caseName = "";
		string uniqueId = "";
		map<string,vector<string> > lookup;
		//QT STuff
		QWidget *mainWidget;
		QVBoxLayout *mainLayout;
		QHBoxLayout *topBarLayout;
		QHBoxLayout *lowerBarLayout;
		QVBoxLayout *buttonLayout;
		QListWidget *weaponList;
		QListWidget *resultsList;
		QListWidget *selectedList;
		QPushButton *addWeapon;
		QPushButton *showResults;

};
#endif