#include "Response.h"

using namespace std;

class mastermind {
public:

	code x;
	mastermind();
	vector<int> humanGuess();
	void printCode() const;
	response getResponse();
	bool isSolved(response y);
	void playGame();
private:

};