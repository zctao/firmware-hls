#include "InheritanceTest.h"
#include "SomeWrapper.h"

void InheritanceTest(int (&inputmem1)[32], int (&inputmem2)[32],
					 int (&inputmem3)[32], int (&inputmem4)[32],
					 int (&inputmem5)[32], int (&inputmem6)[32],
					 int (&inputmem7)[32], int (&inputmem8)[32],
					 ap_uint<5> (&numbersin)[8],
					 int (&outputmem1)[32], int (&outputmem2)[32])
{
	
	// Test 1: Base class
	static ProcessBase aProcBase;
	//aProcBase.process_virtual(
	aProcBase.process(
					  inputmem1, inputmem2, inputmem3, inputmem4,
					  inputmem5, inputmem6, inputmem7, inputmem8,
					  numbersin,
					  outputmem1, outputmem2);
	
	/*
	// Test 2: Inheritance
	// Re-implement process function, calling read_input_mems and init defined in the base class
	static ProcessDerived aProcDerv;
	aProcDerv.process(inputmem1, inputmem2, inputmem3, inputmem4,
					  inputmem5, inputmem6, inputmem7, inputmem8,
					  numbersin,
					  outputmem1, outputmem2);
	*/
	/*
	// Test 3: Inheritance (2)
	// A dummy inheritance. Call process defined in the base class
	static ProcessDerivedTwo aProcDerv2;
	//aProcDerv2.process_virtual(   // unsynthesizable
	aProcDerv2.process(				   
					   inputmem1, inputmem2, inputmem3, inputmem4,
					   inputmem5, inputmem6, inputmem7, inputmem8,
					   numbersin,
					   outputmem1, outputmem2);
	*/
	//
	// Test 4: Polymorphsim
	/* 
	static ProcessDerived aProcDerv;
	ProcessBase* procPtr = &aProcDerv;
	
	//static ProcessDerivedTwo aProcDerv2;
	//ProcessBase* procPtr = &aProcDerv2;
	
	procPtr->process_virtual(inputmem1, inputmem2, inputmem3, inputmem4,
							 inputmem5, inputmem6, inputmem7, inputmem8,
							 numbersin,
							 outputmem1, outputmem2);
	*/
	// another try
	/*
	static ProcessDerived aProcDerv;
	SomeWrapper(&aProcDerv,
				inputmem1, inputmem2, inputmem3, inputmem4,
				inputmem5, inputmem6, inputmem7, inputmem8,
				numbersin,
				outputmem1, outputmem2);
	*/
}
