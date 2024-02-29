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

int* recursive(int problem, int* denoms, int numDenoms)
{
	int* remainders = new int[numDenoms];
	int* solution = new int[numDenoms];
	for (int i = 0; i < numDenoms; i++) solution[i] = NULL;

	for (int i = 0; i < numDenoms; i++)
	{
		remainders[i] = problem - denoms[i];
		int* new_solution = new int[numDenoms];
		new_solution = recursive(problem, denoms, numDenoms);

		if (solution[0] == NULL || new_solution[0] < solution[0])
		{
			delete[] solution;
			solution = new_solution;
		}
	}

	return solution;
}

void memoize(int problem, int* denoms, int numDenoms, CoinPurse &solution, CoinPurse* subps = NULL)
{
	int* remainders = new int[numDenoms];

	for (int i = 0; i < numDenoms; i++)
	{
		remainders[i] = problem - denoms[i];
	}

	for (int i = 0; i < numDenoms; i++)
	{
		if (remainders[i] < 0) continue;
		
		// If we just found the solution return it. 
		if (remainders[i] == 0)
		{
			solution.denoms[i]++;
			solution.count++;
			subps[problem - 1] = solution;
			return;
		}

		// Initialize our lookup table
		if (subps == NULL)
		{
			subps = new CoinPurse[problem];
			for (int j = 0; j < problem; j++)
			{
				subps[j] = CoinPurse(numDenoms);
			}
		}

		CoinPurse new_solution = solution;

		if (subps[remainders[i] - 1].count != -1)
		{
			new_solution = subps[remainders[i] - 1];
		}
		else
		{
			memoize(remainders[i], denoms, numDenoms, new_solution, subps);
		}

		new_solution.denoms[i] = new_solution.denoms[i] + 1;

		if (solution.count == -1 || new_solution.count < solution.count)
		{
			solution = new_solution;
		}
	}

	solution.count++;
	subps[problem-1] = solution;

	return;
}

void bottomUp(int problem, int* denoms, int numDenoms, CoinPurse &finalSolution, CoinPurse* subps = NULL)
{
	// Since bottomUp is doing the same work as memoize, and 
	// the answers are guaranteed to be pre-computed with 
	// bottomUp, we can use the already-written code in memoize
	// to do the compoutational work for us with only a non-
	// standard for loop.

	for (int i = 1; i <= problem; i++)
	{
		memoize(i, denoms, numDenoms, finalSolution, subps);
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
		CoinPurse solution = CoinPurse(numDenoms);
		bottomUp(problems[i], denoms, numDenoms, solution);
		
		// CoinPurse solution = memoize(problems[i], denoms, numDenoms);

		// int* solution = recursive(problems[i], denoms, numDenoms, solution);
		
		for (int j = numDenoms - 1; j != 0; j++)
		{
			if (solution.denoms[j] != 0)
			{
				cout << problems[i]
					<< " cents  = "
					<< denoms[j]
					<< ":"
					<< solution.denoms[j]
					<< endl;
			}
		}
	}

	return 0;
}