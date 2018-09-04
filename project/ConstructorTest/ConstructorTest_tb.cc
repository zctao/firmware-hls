#include "ConstructorTest.h"
#include <iostream>

int main()
{
	using std::cout;
	using std::endl;

	// declare input and output arrays
	int arrayin[32];
	int arrayout[32];
	int arrayout2[32];

	// initialization
	for (int i=0; i < 32; ++i) {
		arrayin[i] = i;

		arrayout[i] = -99;
		arrayout2[i] = -99;
	}

	// start processing
	ConstructorTest(arrayin, arrayout, arrayout2);

	// check outputs
	cout << "arrayout arrayout2" << endl;
	for (int i=0; i < 32; ++i) {
		cout << arrayout[i] << " " << arrayout2[i] << endl;
	}

	return 0;
}
