#include "InheritanceTest.h"
#include <iostream>

int main() {
	using std::cout;
	using std::endl;
	
	// input arrays
	int inmem1[32] = {1,2,3,4,
					  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem1 = 4;
	
	int inmem2[32] = {5,6,7,8,9,
					  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem2 = 5;
	
	int inmem3[32] =
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem3 = 0;

	int inmem4[32] =
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem4 = 0;

	int inmem5[32] =
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem5 = 0;
	
	int inmem6[32] = {10,11,12,
					  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem6 = 3;
	
	int inmem7[32] =
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem7 = 0;

	int inmem8[32] =
		{13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	ap_uint<5> nmem8 = 2;

	ap_uint<5> numbersin[8] =
		{nmem1, nmem2, nmem3, nmem4, nmem5, nmem6, nmem7, nmem8};

	// declare output arrays
	int outmem1[32], outmem2[32];
	// initialization
	for (int i = 0; i < 32; ++i) {
		outmem1[i] = 0;
		outmem2[i] = 0;
	}

	// Top level function
	InheritanceTest(inmem1,inmem2,inmem3,inmem4,inmem5,inmem6,inmem7,inmem8,
					numbersin, outmem1,outmem2);

	// dump output array contents
	cout << "outmem1" << "\t" << "outmem2" << endl;
	for (int i = 0; i < 32; ++i) {
		cout << outmem1[i] << "\t" << outmem2[i] << endl;
	}

	return 0;
}
