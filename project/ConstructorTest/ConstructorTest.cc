#include "ConstructorTest.h"

void ConstructorTest(int inmem[32], int outmem11[32], int outmem22[32])
{
	static ProcessModule aPM(inmem, outmem11, outmem22);
	
	aPM.execute();
}
