#include "MergerTest.h"
#include <iostream>

int main()
{
	using std::cout;
	using std::endl;

	unsigned int sortedArray1[8] = {1,3,5,16,18,25,30,32};
	unsigned int numvalid1 = 8;
	
	unsigned int sortedArray2[8] = {2,4,10,12,22,23,29,31};
	unsigned int numvalid2 = 8;
	
	unsigned int sortedArray3[8] = {6,8,10,11,17,21,26,27};
	unsigned int numvalid3 = 8;
	
	unsigned int sortedArray4[8] = {7,9,13,14,15,19,20,24};
	unsigned int numvalid4 = 8;
	
	hls::stream<unsigned int> outStream;

	MergerTest(sortedArray1, sortedArray2, sortedArray3, sortedArray4,
			   numvalid1, numvalid2, numvalid3, numvalid4,
			   outStream);

	// check outputs
	cout << "Output" << endl;
	for (int i = 0; i < 36; ++i) {
		unsigned int out;
		outStream.read_nb(out);
		cout << out << endl;
	}

	return 0;
}
