#include <vector>
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

class code
{
public:

	code();
	int checkCorrect();
	int checkIncorrect();
	vector<int> getSecretCode() const;
	void initializeSecretCode();
	vector<int> getHumanCode() const;
	void initializeHumanCode();

private:
	// Vectors for human input, secret code and a vector to keep track of which index of the guess is already correct.
	vector<int> secretCode;
	vector<int> humanCode;
	vector<int> locationVector;
};