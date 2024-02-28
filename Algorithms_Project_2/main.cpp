#include <iostream>

//
//	For all the solution functions, return an int array with
//  [ <len of solution>, solution[0], solution[1] ... solution[n] ]
//

class CoinPurse
{
public:
	int count;
	int* denoms;
	CoinPurse()
	{
		count = -1;
		denoms = NULL;
	}
	CoinPurse(int numDenoms)
	{
		count = -1;
		denoms = new int[numDenoms];
	}
};

int* bottomUp(int problem, int* denoms, int numDenoms, CoinPurse* subps = NULL)
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

CoinPurse memoize(int problem, int* denoms, int numDenoms, CoinPurse* subps = NULL)
{
	int* remainders = new int[numDenoms];
	CoinPurse solution = CoinPurse(numDenoms);

	for (int i = 0; i < numDenoms; i++)
	{
		remainders[i] = problem - denoms[i];
	}

	for (int i = 0; i < numDenoms; i++)
	{
		if (subps == NULL)
		{
			subps = new CoinPurse[problem];
			for (int j = 0; j < problem; j++)
			{
				subps[j] = CoinPurse(numDenoms);
			}
		}

		CoinPurse new_solution = CoinPurse(numDenoms);

		if (subps[remainders[i]].count != -1)
		{
			new_solution = subps[remainders[i]];
		}
		else
		{
			new_solution = memoize(remainders[i], denoms, numDenoms, subps);
		}

		new_solution.denoms[i]++;

		if (solution.count == -1 || new_solution.count < solution.count)
		{
			solution = new_solution;
		}
	}

	solution.count++;
	subps[problem] = solution;

	return solution;
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
		
		CoinPurse solution = memoize(problems[i], denoms, numDenoms);

		if (problems[i] < 20)
		{
			int* solution = recursive(problems[i], denoms, numDenoms);
		}
	}

	return 0;
}