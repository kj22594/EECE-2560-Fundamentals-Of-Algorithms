#include "Mastermind.h"

// Constructor
mastermind::mastermind()
{
}

// Prints secret code
void mastermind::printCode() const
{
	vector<int> tempCode = x.getSecretCode();
	cout << "The secret code is: " << endl;
	for (int f = 0; f < 4; f++)
	{
		cout << tempCode[f] << ",";
	}
	cout << endl;
}

// Initializes a human guess and then returns that guess
vector<int> mastermind::humanGuess()
{
	vector<int> tempHumanCode;
	x.initializeHumanCode();
	tempHumanCode = x.getHumanCode();
	return tempHumanCode;
}

// Initialize and returns a response that has a correct & incorrect response
response mastermind::getResponse()
{
	response y;
	y.setCorrectResponse(x);
	y.setIncorrectResponse(x);
	return y;
}

// Checks to see if the entire code has been solve and if so returns true and displays a congrats message
bool mastermind::isSolved(response y)
{
	int totalCorrect = y.getCorrectResponse();
	if (totalCorrect == 4)
	{
		return true;
	}
	else
		return false;
}

void mastermind::playGame()
{
	
	response y;
	x.initializeSecretCode();
	printCode();
	int gameCounter = 0;
	while (isSolved(y) == false || gameCounter < 10)
	{
		x.initializeHumanCode();
		y = getResponse();
		isSolved(y);
		y.printResponse();
		gameCounter++;
		if (isSolved(y) == true)
		{
			cout << "You win" << endl;
			system("pause");
			break;
		}
		if (gameCounter == 10)
		{
			cout << "You lose" << endl;
			system("pause");
			break;
		}
	}
}