#ifndef PROCESSMODULE_HH
#define PROCESSMODULE_HH

class ProcessModule
{
public:

	ProcessModule(int inmem[32], int outmem1[32], int outmem2[32]):
		inputarr_(inmem),
		outputarr_(outmem1),
		outputarr2_(outmem2),
		cnt_(0),
		cnt2_(0)
{}

	~ProcessModule(){}

	void execute() {
		unsigned int cnttmp = 0;
		unsigned int cnt2tmp = 0;

		for (int i = 0; i < 32; ++i) {
#pragma HLS PIPELINE II=1

			// read inputs
			int foo = inputarr_[i];
			
			// do something
			foo++;
			int bar = foo*3;

			// write outputs
			cnt_ = cnttmp;
			outputarr_[cnt_] = foo;
			cnttmp++;

			cnt2_ = cnt2tmp;
			outputarr2_[cnt2_] = bar;
			cnt2tmp++;

/*
			switch (foo%2)
			{
			case 0:
				outputarr_[cnttmp++] = bar;
				break;
			case 1:
				outputarr2_[cnt2tmp++] = bar;
				break;
			}
*/
		}
	}

protected:

	int *inputarr_;
	int *outputarr_;
	int *outputarr2_;

	unsigned int cnt_;
	unsigned int cnt2_;
};

#endif
