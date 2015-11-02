#include "Response.h"

// Constructor
response::response() {}

// Setters for two responses
void response::setCorrectResponse(code x)
{
	correctResponse = x.checkCorrect();
}
void response::setIncorrectResponse(code x)
{
	incorrectResponse = x.checkIncorrect();
}

// Getters for two responses
int response::getCorrectResponse() const
{
	return correctResponse;
}
int response::getIncorrectResponse() const
{
	return incorrectResponse;
}

// Prints response
void response::printResponse() const
{
	cout << "(Correct digit,Correct digit but in wrong position): " << "(" << correctResponse << "," << incorrectResponse << ")" << endl;
}