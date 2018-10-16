#ifndef PROCESSDERIVEDTWO_HH
#define PROCESSDERIVEDTWO_HH

class ProcessDerivedTwo : public ProcessBase
{
public:
	// inherit base class constructors
	//using ProcessBase::ProcessBase;

	ProcessDerivedTwo() : ProcessBase() {}
	ProcessDerivedTwo(int nlayer, int ndisk, int phi) : ProcessBase(nlayer, ndisk, phi){}
	~ProcessDerivedTwo(){}

	// redefine init();
	void init()
	{
		sector_ = 0;
		layer_ = 0;
		disk_ = 0;
		
		read_imem_ = 0;
		read_addr_ = 0;
		outcnt_ = 0;
		outcnt2_ = 0;
		mem_hasdata_ = 0;

		// dummy init. should never be called.
		//assert(0);
	}
};

#endif
