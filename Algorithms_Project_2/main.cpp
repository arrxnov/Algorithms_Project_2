#include <iostream>

//
//	For all the solution functions, return an int array with
//  [ <len of solution>, solution[0], solution[1] ... solution[n] ]
//

typedef struct CoinPurse_t {
	int count; 
	int* denoms = NULL; 
};

int* bottomUp(int problem, int* denoms, int numDenoms, int* subps = NULL)
{

}

int* recursive(int problem, int* denoms, int numDenoms)
{
	int* remainders = new int[numDenoms];
	int* solution = new int[numDenoms]; // automatically NULL
	for (int i = 0; i < numDenoms; i++)
	{
		remainders[i] = problem - denoms[i];
		int* new_solution = new int[numDenoms];
		new_solution = recursive(problem, denoms, numDenoms);
		if (solution[0] == NULL || new_solution[0] < solution[0])
		{
			// This might be leaky...
			delete solution;
			solution = new_solution;
		}
	}
	return solution;
}

int* memoize(int problem, int* denoms, int numDenoms, int* subps = NULL)
{
	int* remainders = new int[numDenoms];
	for (int i = 0; i < numDenoms; i++) remainders[i] = problem - denoms[i];

	if (subps == NULL) subps = new int[problem];
	for (int i = 0; i < numDenoms; i++)
	{
		
	}
}

int main()
{
	using namespace std;
	int numDenoms, numProblems;
	
	// Read in all coin denominations (smallest to largest)
	cin >> numDenoms;
	int* denoms = new int[numDenoms];
	for (int i = 0; i < numDenoms; i++) cin >> denoms[i];

	// Read in all combinations to determine
	cin >> numProblems;
	int* problems = new int[numProblems];
	for (int i = 0; i < numProblems; i++) cin >> problems[i];

	// Determine combinations for all problems
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