#include "Code.h"

// Constructor
code::code()
{
}

// Sets & get secret code
void code::initializeSecretCode() {
	// Establishes seed for generating time
	srand((unsigned)time(0));
	secretCode.clear();
	for (int i = 0; i < 4; i++)
	{
		int temp = rand() % 6;
		secretCode.push_back(temp);

	}

}
vector<int> code::getSecretCode() const
{
	return secretCode;
}

// Set & get human code
void code::initializeHumanCode()
{
	humanCode.clear();
	cout << "Guess the secret code. To add a number, type the number then press enter." << endl; // For the input please enter in 1 number then press enter, must repeat this 4 times
	for (int n = 0; n < 4; n++) {
		int humanInput;
		cin >> humanInput;
		humanCode.push_back(humanInput);
		if (humanCode[n] > 5 || humanCode[n] < 0)
		{
			cout << "You did not follow the guidelines. Please enter in a new number." << endl;
			cin >> humanInput;
			humanCode.push_back(humanInput);
		}
	}
}
vector<int> code::getHumanCode() const
{
	return humanCode;
}

// Checks for how many numbers are in the correct location
int code::checkCorrect()
{
	int correctCounter = 0;
	int x = 1;
	int y = 0;
	for (int r = 0; r < 4; r++)
	{
		if (secretCode[r] == humanCode[r])
		{

			locationVector.push_back(x);
			correctCounter++;
		}
		else
		{
			locationVector.push_back(y);
		}
	}
	return correctCounter;
}

// Checks for how many numbers are correct but in the wrong location
int code::checkIncorrect()
{
	checkCorrect();
	int incorrectCounter = 0;
	for (int i = 0; i < 4; i++) {
		for (int x = 0; x < 4; x++)
		{

			if (locationVector[i] == 1)
			{
				break;
			}
			if (secretCode[i] == humanCode[x] && i != x)
			{
				incorrectCounter++;
				break;
			}

		}
	}
	return incorrectCounter;
}