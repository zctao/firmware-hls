#ifndef PROCESSBASE_HH
#define PROCESSBASE_HH

class ProcessBase
{
protected:

	ap_uint<3> read_imem_;
	ap_uint<5> read_addr_;
	ap_uint<8> mem_hasdata_;
	
	int outcnt_;
	int outcnt2_;

	int layer_;
	int disk_;
	int sector_;
	
public:

	ProcessBase():
		outcnt_(0),
		outcnt2_(0),
		layer_(0),
		disk_(0),
		sector_(0),
		read_imem_(0),
		read_addr_(0),
		mem_hasdata_(0)
	{}

	ProcessBase(int nlayer, int ndisk, int phi):
	    outcnt_(0),
		outcnt2_(0),
		layer_(nlayer),
		disk_(ndisk),
		sector_(phi),
		read_imem_(0),
		read_addr_(0),
		mem_hasdata_(0)
	{}
	
	virtual ~ProcessBase(){};

	virtual void process(// input memories
						 int inmem1[32], int inmem2[32],
						 int inmem3[32], int inmem4[32],
						 int inmem5[32], int inmem6[32],
						 int inmem7[32], int inmem8[32],
						 ap_uint<5> numbersin[8],
						 // output memories
						 int outmem1[32], int outmem2[32])
	{	
#pragma HLS ARRAY_PARTITION variable=numbersin complete

		std::cout << "ProcessBase::process" << std::endl;
		
		init(numbersin);
		
		// processing loop: 32 steps
		for (int i = 0; i < 32; ++i) {
#pragma HLS PIPELINE II=1

			///////////////////
			// read input data
			int inputdata;
			bool validin = read_input_mems(inputdata,
										   inmem1, inmem2, inmem3, inmem4,
										   inmem5, inmem6, inmem7, inmem8,
										   numbersin);
			if (not validin) continue;

			///////////////////
			// do something 
			int foo = inputdata;
			int bar = foo * 5;

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

	void init(ap_uint<5> numbersin[8])
	{
		read_imem_ = 0;
		read_addr_ = 0;
		outcnt_ = 0;
		outcnt2_ = 0;

		// bitmask to indicate if memories are empty
		mem_hasdata_ = 0;
		for (int im = 0; im < 8; ++im) {
#pragma HLS UNROLL
			mem_hasdata_ += ( (numbersin[im]>0) << im );
		}
	}
	
	// priority encoder for reading the 8 input memories
	bool read_input_mems(int &datain,
						 int mem1[32], int mem2[32],
						 int mem3[32], int mem4[32],
						 int mem5[32], int mem6[32],
						 int mem7[32], int mem8[32],
						 ap_uint<5> nentries[8])
	{
		if (mem_hasdata_ == 0) return false;

		read_imem_ = __builtin_ctz(mem_hasdata_);

		// read memory "read_imem_" with reading address "read_addr_"
		switch (read_imem_) {
		case 0:
			datain = mem1[read_addr_]; break;
		case 1:
			datain = mem2[read_addr_]; break;
		case 2:
			datain = mem3[read_addr_]; break;
		case 3:
			datain = mem4[read_addr_]; break;
		case 4:
			datain = mem5[read_addr_]; break;
		case 5:
			datain = mem6[read_addr_]; break;
		case 6:
			datain = mem7[read_addr_]; break;
		case 7:
			datain = mem8[read_addr_]; break;
		default:
			datain = -1;
		}

		++read_addr_;
		if (read_addr_ >= nentries[read_imem_]) {
			// All entries in memory[read_imem_] have been read out
			// Prepare to move to the next non-empty memory
			read_addr_ = 0;
			mem_hasdata_ -= (1<<read_imem_); // flip the lowest 1 bit to 0
		}

		return true;
	}
	
};

#endif
