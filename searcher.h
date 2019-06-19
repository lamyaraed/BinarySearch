/**
 *  @file    searcher.h
 *  @author  Mahmoud Ahmed Tawfik (20160227) - Sara Zakareia Adam (20170384) - Lamya Raed Aly (20170339)
 *  @date    30/03/2019
 *  @version 1.0
 *
 *  @Problem Searcher(P3)
 *
 */

#ifndef SEARCHER_H_INCLUDED
#define SEARCHER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>
#include <limits>

using namespace std;

template <class T>
class Searcher
{
private:
	fstream file1;
	fstream file2;
	vector<T> v1;
	vector<T> v2;
	string fileName1;
	string fileName2;
	int numberOfComparisons;
	
public:
	Searcher(string, string);
	void loadData();                    // Loads required num of words from file 
	int binarySearch(int, int, T);		// Looks for a given item in the data & return its index or -1  
	int testPerformance (int);			// Gets time & num of comparisons
	string getRandomWord(int, bool);				

	~Searcher();
};

template <class T>
Searcher<T>::Searcher(string _fileName1, string _fileName2)
{
	this->fileName1 = _fileName1;
	this->fileName2 = _fileName2;
	this->numberOfComparisons = 0;

	file1.open(this->fileName1.c_str(), ios::in | ios::out);
	file2.open(this->fileName2.c_str(), ios::in | ios::out);

	if(!file1)
	{
		cerr << "Searcher<T>::Searcher(string, string): ERROR - " << this->fileName1 << " Not Found."  << endl;
		exit(0);
	}

	if(!file2)
	{
		cerr << "Searcher<T>::Searcher(string, string): ERROR - " << this->fileName2 << " Not Found."  << endl;
		exit(0);
	}

	cout << "Please Wait A Moment While Get Data From File (" << this->fileName1 << ")...";
	
	while(!file1.eof())
	{
		string tString;
		this->file1 >> tString;
		this->v1.push_back(tString);
	}

	cout << "\nPlease Wait A Moment While Get Data From File (" << this->fileName2 << ")...";
	
	while(!file2.eof())
	{
		string tString;
		this->file2 >> tString;
		this->v2.push_back(tString);
	}
	
	sort(this->v1.begin(), this->v1.end());
	sort(this->v2.begin(), this->v2.end());

	system("CLS");
	cout << "Done!" << endl;
	cout << "Data Size(v1) = " << this->v1.size() << " Words." << endl; // 109581 Words
	cout << "Data Size(v2) = " << this->v2.size() << " Words." << endl; // 109581 Words

	cout << endl;
}

template <class T>
int Searcher<T>::binarySearch(int _r, int _l, T _value)
{
	int r = _r;
	int l = _l;
	int mid = (l + r) / 2;

	while(r <= l)
	{
		if(_value == this->v1[mid])
		{
			this->numberOfComparisons++;
			return mid;
		}
		else if(_value < this->v1[mid])
		{
			this->numberOfComparisons++;
			l = mid - 1;
			mid = (l + r) / 2;
		}
		else
		{
			this->numberOfComparisons++;
			r = mid + 1;
			mid = (l + r) / 2;
		}
	}
	return -1;
}

template <class T>
int Searcher<T>::testPerformance(int _i)
{
	double time_taken1, time_taken2;
	clock_t start1, start2, end1, end2;

	cout << "Using " << _i << " words." << endl << endl;

	start1 = clock();
	for(int j = 0 ; j < 100 ; j++)
	{
		string t = this->getRandomWord(_i, 1);
		this->binarySearch(0, _i, t);
	}
	end1 = clock(); 
  
	// Calculating average time.
	time_taken1 = double(end1 - start1) / double(CLOCKS_PER_SEC); 
	cout << "1) Average time = " << fixed << setprecision(8) << time_taken1 / 100.0 << "s" << endl;
	cout << "1) Average number of comparison = " << this->numberOfComparisons / 100 << endl << endl;

	this->numberOfComparisons = 0;

	start2 = clock();
	for(int j = 0 ; j < 100 ; j++)
	{
		string t = this->getRandomWord(_i, 0);
		this->binarySearch(0, _i, t);
	}
	end2 = clock(); 
  
	// Calculating average time.
	time_taken2 = double(end2 - start2) / double(CLOCKS_PER_SEC); 
	cout << "2) Average time = " << fixed << setprecision(8) << time_taken2 / 100.0 << "s" << endl;
	cout << "2) Average number of comparison = " << this->numberOfComparisons / 100 << endl << endl;

	this->numberOfComparisons = 0;
	return 0;
}

template <class T>
string Searcher<T>::getRandomWord(int _max, bool isExisted)
{
	int x = this->v1.size();
	int y = _max;
	int r = rand() % min(x, y) ; // min(x, y)

	if(isExisted)
		return this->v1[r];
	else
		return this->v2[r];
}		

template <class T>
Searcher<T>::~Searcher()
{
	this->file1.close();
	this->file2.close();
}

#endif // SEARCHER_H_INCLUDED
