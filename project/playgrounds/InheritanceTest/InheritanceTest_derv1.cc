#include "InheritanceTest.h"
#include "SomeWrapper.h"

void InheritanceTest(int inputmem1[32], int inputmem2[32],
					 int inputmem3[32], int inputmem4[32],
					 int inputmem5[32], int inputmem6[32],
					 int inputmem7[32], int inputmem8[32],
					 ap_uint<5> numbersin[8],
					 int outputmem1[32], int outputmem2[32])
{
#pragma HLS ARRAY_PARTITION variable=numbersin complete

	// Test 2: Inheritance
	// Re-implement process function, calling read_input_mems and init defined in the base class
	static ProcessDerived aProcDerv;
	aProcDerv.process(inputmem1, inputmem2, inputmem3, inputmem4,
					  inputmem5, inputmem6, inputmem7, inputmem8,
					  numbersin,
					  outputmem1, outputmem2);
}
