#include <iostream>

//
//	For all the solution functions, return an int array with
//  [ <len of solution>, solution[0], solution[1] ... solution[n] ]
//

int* bottomUp(int problem, int* denoms, int numDenoms, int* subps = NULL)
{

}

int* recursive(int problem, int* denoms, int numDenoms, int* subps = NULL)
{

}

int* memoize(int problem, int* denoms, int numDenoms, int* subps = NULL)
{

}

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

	for (int i = 0; i < numProblems; i++)
	{
		int* solution = bottomUp(problems[i], denoms, numDenoms);
		
		int* solution = memoize(problems[i], denoms, numDenoms);

		if (problems[i] < 20)
		{
			int* solution = recursive(problems[i], denoms, numDenoms);
		}
	}


	return 0;
}