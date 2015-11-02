#include "Code.h"

using namespace std;

class response {
public:
	response();
	void setCorrectResponse(code x);
	void setIncorrectResponse(code x);
	int getCorrectResponse() const;
	int getIncorrectResponse() const;
	void printResponse() const;
private:
	int correctResponse;
	int incorrectResponse;
};