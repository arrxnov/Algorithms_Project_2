#include <iostream>

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

void recursive(
	int problem,
	int* denoms,
	int numDenoms,
	CoinPurse &solution
)
{
	using namespace std;

	// Fill in results from a subtraction with every denomination
	int* remainders = new int[numDenoms];
	for (int i = numDenoms - 1; i >= 0 ; i--)
	{
		remainders[i] = problem - denoms[i];
	}

	CoinPurse current_solution = CoinPurse(numDenoms);

	for (int i = numDenoms - 1; i >= 0; i--)
	{
		// Skip negative results
		if (remainders[i] < 0)
		{
			continue;
		}

		// If we just found the solution return it. 
		if (remainders[i] == 0)
		{
			solution.denoms[i]++;
			solution.count++;
			delete[] remainders;
			return;
		}

		CoinPurse new_solution = CoinPurse(numDenoms);

		recursive(remainders[i], denoms, numDenoms, new_solution);

		new_solution.denoms[i]++;
		new_solution.count++;

		// Find smallest coin count of the different denomination subtractions
		if (current_solution.count == 0 
			|| new_solution.count < current_solution.count)
		{
			current_solution.count = new_solution.count;
			for (int j = 0; j < numDenoms; j++)
			{
				current_solution.denoms[j] = new_solution.denoms[j];
			}
		}
	}

	solution.count = current_solution.count;
	for (int i = 0; i < numDenoms; i++)
	{
		solution.denoms[i] = current_solution.denoms[i];
	}

	delete[] remainders;
}

void memoize(
	int problem,
	int* denoms,
	int numDenoms,
	CoinPurse &solution,
	CoinPurse* subps = NULL
)
{
	using namespace std;
	bool responsibility = false;

	// Initialize our lookup table
	if (subps == NULL)
	{
		subps = new CoinPurse[problem];
		for (int j = 0; j < problem; j++)
		{
			subps[j] = CoinPurse(numDenoms);
		}
		responsibility = true;
	}
	
	// If we find our remainder in the table, return it
	if (subps[problem - 1].count != 0)
	{
		for (int j = 0; j < numDenoms; j++)
		{
			solution.denoms[j] = subps[problem - 1].denoms[j];
		}
		solution.count = subps[problem - 1].count;
		return;
	}

	// Fill in results from a subtraction with every denomination
	int* remainders = new int[numDenoms];
	for (int i = numDenoms - 1; i >= 0; i--)
	{
		remainders[i] = problem - denoms[i];
	}

	CoinPurse current_solution = CoinPurse(numDenoms);

	for (int i = numDenoms - 1; i >= 0; i--)
	{
		if (remainders[i] < 0)
		{
			continue;
		}
		
		// If we just found the solution return it. 
		if (remainders[i] == 0)
		{
			solution.denoms[i]++;
			solution.count++;
			subps[problem - 1].count = solution.count;
			for (int j = 0; j < numDenoms; j++)
			{
				subps[problem - 1].denoms[j] = solution.denoms[j];
			}
			delete[] remainders;
			return;
		}

		CoinPurse new_solution = CoinPurse(numDenoms);
		memoize(remainders[i], denoms, numDenoms, new_solution, subps);
		
		new_solution.denoms[i]++;
		new_solution.count++;

		if (current_solution.count == 0 
			|| new_solution.count <= current_solution.count)
		{
			current_solution.count = new_solution.count;
			for (int j = 0; j < numDenoms; j++)
			{
				current_solution.denoms[j] = new_solution.denoms[j];
			}
		}
	}

	solution.count = current_solution.count;
	for (int i = 0; i < numDenoms; i++)
	{
		solution.denoms[i] = current_solution.denoms[i];
	}
	subps[problem - 1].count = solution.count;
	for (int i = 0; i < numDenoms; i++)
	{
		subps[problem - 1].denoms[i] = solution.denoms[i];
	}

	delete[] remainders;
	if (responsibility)
	{
		delete[] subps;
	}
}

void bottomUp(
	int problem,
	int* denoms,
	int numDenoms,
	CoinPurse &finalSolution,
	CoinPurse* subps = NULL
)
{
	// Since bottomUp is doing the same work as memoize, and 
	// the answers are guaranteed to be pre-computed with 
	// bottomUp, we can use the already-written code in memoize
	// to do the computational work for us with only a non-
	// standard for loop.

	// Initialize our lookup table
	if (subps == NULL)
	{
		subps = new CoinPurse[problem];
		for (int j = 0; j < problem; j++)
		{
			subps[j] = CoinPurse(numDenoms);
		}
	}

	CoinPurse tempSolution = CoinPurse(numDenoms);

	for (int i = 1; i <= problem; i++)
	{
		tempSolution = CoinPurse(numDenoms);
		unsigned int currentBest = -1;
		memoize(i, denoms, numDenoms, tempSolution, subps);
	}
	finalSolution = tempSolution;
	delete[] subps;
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
		// bottomUp(problems[i], denoms, numDenoms, solution);

		memoize(problems[i], denoms, numDenoms, solution);

		// recursive(problems[i], denoms, numDenoms, solution);

		cout << problems[i]
			<< " cents = ";
		int count = 0;
		for (int j = numDenoms - 1; j >= 0; j--)
		{
			if (solution.denoms[j] != 0)
			{
				cout << denoms[j]
					<< ":"
					<< solution.denoms[j];
				count += solution.denoms[j];
				if (count < solution.count) cout << " ";
			}
		}
		cout << endl;
	}

	delete[] denoms;
	delete[] problems;

	return 0;
}