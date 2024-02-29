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
			count = 0;
			denoms = NULL;
		}
		CoinPurse(int numDenoms)
		{
			count = 0;
			denoms = new int[numDenoms];
			for (int i = 0; i < numDenoms; i++) denoms[i] = 0;
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
	using namespace std;
	
	// Fill in results from a subtraction with every denomination
	int* remainders = new int[numDenoms];
	for (int i = 0; i < numDenoms; i++)
	{
		remainders[i] = problem - denoms[i];
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

	CoinPurse current_solution = CoinPurse(numDenoms);

	for (int i = 0; i < numDenoms; i++)
	{
		if (remainders[i] < 0)
		{
			break;
		}
		
		// If we just found the solution return it. 
		if (remainders[i] == 0)
		{
			solution.denoms[i]++;
			solution.count++;
			subps[problem - 1] = solution;
			delete[] remainders;
			return;
		}

		if (subps[remainders[i] - 1].count != 0)
		{
			solution = subps[remainders[i] - 1];
			delete[] remainders;
			return;
		}

		CoinPurse new_solution = CoinPurse(numDenoms);
		
		memoize(remainders[i], denoms, numDenoms, new_solution, subps);
		
		new_solution.denoms[i]++;
		new_solution.count++;

		if (current_solution.count == 0 || new_solution.count < current_solution.count)
		{
			current_solution = new_solution;
		}
	}

	solution = current_solution;
	subps[problem-1] = solution;
	delete[] remainders;
}

void bottomUp(int problem, int* denoms, int numDenoms, CoinPurse &finalSolution, CoinPurse* subps = NULL)
{
	// Since bottomUp is doing the same work as memoize, and 
	// the answers are guaranteed to be pre-computed with 
	// bottomUp, we can use the already-written code in memoize
	// to do the computational work for us with only a non-
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
		
		cout << problems[i]
			<< " cents = ";

		for (int j = numDenoms - 1; j >= 0; j--)
		{
			if (solution.denoms[j] != 0)
			{
				cout << denoms[j]
					<< ":"
					<< solution.denoms[j]
					<< " ";
			}
		}
		cout << endl;
	}
	delete[] denoms;
	delete[] problems;

	return 0;
}