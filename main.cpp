#include <iostream>
#include "searcher.h"

using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	Searcher<string> s("words1.txt", "words2.txt");

	for(int i = 10000 ; i <= 80000 ; i += 10000)
	{
		cout << "------------------------------------" << endl;
		s.testPerformance(i);
		cout << "------------------------------------" << endl;
	}
	
	return 0;
}	