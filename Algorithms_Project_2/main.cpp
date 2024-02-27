#include <iostream>

int main()
{
	using namespace std;
	int numDenoms, numProblems;
	
	cin >> numDenoms;
	int* denoms = new int[numDenoms];
	for (int i = 0; i < numDenoms; i++) cin >> denoms[i];

	cin >> numProblems;
	int* problems = new int[numProblems];
	for (int i = 0; i < numProblems; i++) cin >> problems[i];




	return 0;
}