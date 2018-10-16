#ifndef PROCESSDERIVED_HH
#define PROCESSDERIVED_HH

class ProcessDerived : public ProcessBase
{
public:
	// inherit base class constructors
	
	// Seems Vivado HLS (2018.2) does not support the syntax below in synthesis
	//using ProcessBase::ProcessBase;
	
	// Have to do it the old way...
	ProcessDerived() : ProcessBase(){}
	ProcessDerived(int nlayer, int ndisk, int phi) : ProcessBase(nlayer, ndisk, phi){}
	~ProcessDerived(){}
	
	// redefine process()
	void process(// input memories
				 int (&inmem1)[32], int (&inmem2)[32],
				 int (&inmem3)[32], int (&inmem4)[32],
				 int (&inmem5)[32], int (&inmem6)[32],
				 int (&inmem7)[32], int (&inmem8)[32],
				 ap_uint<5> (&numbersin)[8],
				 // output memories
				 int (&outmem1)[32], int (&outmem2)[32])
	{
#pragma HLS ARRAY_PARTITION variable=numbersin complete
		
		std::cout << "ProcessDerived::process" << std::endl;
		
		init(numbersin); // defined in base class

		// processing loop: 32 steps
		for (int i = 0; i < 32; ++i) {
#pragma HLS PIPELINE II=1

			/////////
			// read input data
			int inputdata;
			bool validin = read_input_mems(inputdata,
										   inmem1, inmem2, inmem3, inmem4,
										   inmem5, inmem6, inmem7, inmem8,
										   numbersin); // defined in base class
			if (not validin) continue;

			///////////////////
			// do something 
			int foo = inputdata;
			int bar = foo * 3; // only difference w.r.t. base class definition

			///////////////////
			// write to output
			switch (foo%2) {
			case 0:
				outmem1[outcnt_++] = bar;
				break;
			case 1:
				outmem2[outcnt2_++] = bar;
				break;			
			}
			
		} // end of processing loop
	}

	// redefine process_virtual
	// exactly the same as process
	void process_virtual(// input memories
				 int (&inmem1)[32], int (&inmem2)[32],
				 int (&inmem3)[32], int (&inmem4)[32],
				 int (&inmem5)[32], int (&inmem6)[32],
				 int (&inmem7)[32], int (&inmem8)[32],
				 ap_uint<5> (&numbersin)[8],
				 // output memories
				 int (&outmem1)[32], int (&outmem2)[32])
	{
		process(inmem1, inmem2, inmem3, inmem4, inmem5, inmem6, inmem7, inmem8,
				numbersin, outmem1, outmem2);
	}
};

#endif
