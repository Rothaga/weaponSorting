/*
 * quicksort.h
 *
 *  Created on: Apr 13, 2014
 *      Author: shist_000
 */
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#ifndef QUICKSORT_H_
#define QUICKSORT_H_
//Comparators below, self explanatory
struct Case
{
	string name;
	int weapons;
	vector<string> userWeapons;
};
struct caseComp
{
	bool operator()(const Case& case1, const Case& case2)
	{
		return case1.weapons <= case2.weapons;
	}
};
struct stringComp
{
	bool operator()(const string& case1, const string& case2)
	{
		return case1 <= case2;
	}
};
struct intComp
{
	bool operator()(const int& student1, const int& student2)
	{
		return student1 <= student2;
	}
};


template <class T, class Comparator>
class QuickSort
{
public:
	QuickSort ();   // constructor

	~QuickSort (); // destructor

	T * lastQuickSort(T * array, int arrLength, Comparator comp);
	T * randomQuickSort(T * array, int arrLength, Comparator comp);

private:
	T * combine(T * less, T pivot,T * greater, int lessSize, int greatSize);
	vector<T*> mems;
};
template <class T, class Comparator>
QuickSort<T, Comparator> :: QuickSort()
{

}
//Delete dynamically allocated memory
template <class T, class Comparator>
QuickSort<T, Comparator> :: ~QuickSort()
{
}
//Combines two arrays into one array
template <class T, class Comparator>
T * QuickSort<T, Comparator> :: combine(T * less, T pivot, T * greater,int lessSize, int greatSize)
{
	T * combined = new T[lessSize + greatSize + 1];
	int count = 0;
	for(int i = 0; i < lessSize; i++)
	{
		combined[count] = less[i];
		count++;
	}
	combined[count] = pivot;
	count++;
	for(int i = 0; i < greatSize; i++)
	{
		combined[count] = greater[i];
		count++;
	}
	mems.push_back(combined);
	return combined;
}
//Uses comparators and sets the pivot point to the last value in the array
template <class T, class Comparator>
T * QuickSort<T, Comparator> :: lastQuickSort(T * array, int arrLength, Comparator comp)
{
	if(arrLength < 2)
		return array;
	int pivotPoint = arrLength-1;
	T pivot = array[pivotPoint];
	int greatCount = 0;
	int lessCount = 0;
	T * greater = new int[arrLength-1];
	T * lesser = new int[arrLength-1];
	mems.push_back(greater);
	mems.push_back(lesser);
	for(int i = 0; i < arrLength; i++)
	{
		if(pivotPoint != i)
		{
			if(comp(array[i],pivot))
			{
				lesser[lessCount] = array[i];
				lessCount++;
			}
			else
			{
				greater[greatCount] = array[i];
				greatCount++;
			}
		}

	}
	return combine(lastQuickSort(lesser,lessCount,comp),pivot,lastQuickSort(greater,greatCount,comp),lessCount,greatCount);
}
//Uses Random Pivot point
template <class T, class Comparator>
T * QuickSort<T, Comparator> :: randomQuickSort(T * array, int arrLength, Comparator comp)
{
	srand(time(0));
	if(arrLength < 2)
		return array;
	int pivotPoint = (rand() % arrLength);
	T pivot = array[pivotPoint];
	int greatCount = 0;
	int lessCount = 0;
	T * greater = new T[arrLength-1];
	T * lesser = new T[arrLength-1];
	mems.push_back(greater);
	mems.push_back(lesser);
	for(int i = 0; i < arrLength; i++)
	{
		if(pivotPoint != i)
		{
			if(comp(array[i],pivot))
			{
				lesser[lessCount] = array[i];
				lessCount++;
			}
			else
			{
				greater[greatCount] = array[i];
				greatCount++;
			}
		}
	}
	T * returning = combine(randomQuickSort(lesser,lessCount,comp),pivot,randomQuickSort(greater,greatCount,comp),lessCount,greatCount);
	return returning;
}
#endif /* QUICKSORT_H_ */
