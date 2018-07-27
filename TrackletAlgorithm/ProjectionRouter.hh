// Projection Router
#ifndef PROJECTIONROUTER_HH
#define PROJECTIONROUTER_HH

#include "Constants.hh"
#include "ProcessBase.hh"

#include "TrackletProjections.hh"
#include "AllProjections.hh"
#include "VMProjections.hh"

const int nTProjMem = 8;  // FIXME

class ProjectionRouter //: public ProcessBase<nMaxProc>
{
public:

  // constructor
  ProjectionRouter(){}
  ~ProjectionRouter(){}

  //
  void execute()
  {
	  // check which input memories are not empty
	  //bool mem_hasdata_arr[nTProjMem];
	  ap_uint<nTProjMem> mem_hasdata = 0;
	  // need to unroll the loop
	  HASDATA_LOOP: for (int imem = 0; imem < nTProjMem; ++imem) {
		  if (numbersin_[imem > 0]) {
			  //mem_hasdata_arr[imem] = 1;
			  mem_hasdata += (1<<imem);
		  }
		  //else {
			  //mem_hasdata_arr[imem] = 0;
		  //}
	  }

	  unsigned int imem = 0;
	  unsigned int addr_next = 0;
	  PROC_LOOP: for (int i = 0; i < nMaxProc; ++i) {

		  // read inputs
		  unsigned int addr = addr_next;
		  bool validin = get_mem_read_addr<nTProjMem>(imem, addr_next, mem_hasdata, numbersin_);

		  if (not validin) continue;

		  TProjData tproj = read_mem(imem, addr);

		  // routing


		  // write outputs

	  }
  }

  // move this to ProcessBase class?
  template<int nMEM>
  bool get_mem_read_addr(unsigned int& imem, unsigned int& addr, ap_uint<nMEM>& mem_hasdata, unsigned int* numbersin)
  {
	  if (mem_hasdata == 0) return false;

	  // priority encoder
	  imem = __builtin_ctz(mem_hasdata);
	  ++addr;

	  if (add >= *(numbersin+imem)) {  // All entries have been read out in memory[imem]
		  // Prepare to read the next non-empty memory
		  addr = 0;  // reset read address
		  mem_hasdata -= (1<<imem);  // flip the lowest 1 bit to 0
	  }

	  return true;
  }

  TProjData read_mem(int imem, int addr)
  {
	  switch (imem)
	  {
	  case 0:
		  return *(inputproj1_+addr);
	  case 1:
		  return *(inputproj2_+addr);
	  case 2:
		  return *(inputproj3_+addr);
	  case 3:
	  	  return *(inputproj4_+addr);
	  case 4:
		  return *(inputproj5_+addr);
	  case 5:
		  return *(inputproj6_+addr);
	  case 6:
		  return *(inputproj7_+addr);
	  case 7:
		  return *(inputproj8_+addr);
	  }
  }

  // connect input & output memory modules
  void addInputs(TrackletProjections* trackletproj1,
		TrackletProjections* trackletproj2,
		TrackletProjections* trackletproj3,
		TrackletProjections* trackletproj4,
		TrackletProjections* trackletproj5,
		TrackletProjections* trackletproj6,
		TrackletProjections* trackletproj7,
		TrackletProjections* trackletproj8
		// more
		)
  {
    inputproj1_ = trackletproj1->get_mem();
    inputproj2_ = trackletproj2->get_mem();
    inputproj3_ = trackletproj3->get_mem();
    inputproj4_ = trackletproj4->get_mem();
    inputproj5_ = trackletproj5->get_mem();
    inputproj6_ = trackletproj6->get_mem();
    inputproj7_ = trackletproj7->get_mem();
    inputproj8_ = trackletproj8->get_mem();

    numbersin_[0] = trackletproj1->getEntries();
    numbersin_[1] = trackletproj2->getEntries();
    numbersin_[2] = trackletproj3->getEntries();
    numbersin_[3] = trackletproj4->getEntries();
    numbersin_[4] = trackletproj5->getEntries();
    numbersin_[5] = trackletproj6->getEntries();
    numbersin_[6] = trackletproj7->getEntries();
    numbersin_[7] = trackletproj8->getEntries();
  }

  void addOutputs(AllProjections* allprojection,
		 VMProjections* vmproj1,
		 VMProjections* vmproj2,
		 VMProjections* vmproj3,
		 VMProjections* vmproj4,
		 VMProjections* vmproj5,
		 VMProjections* vmproj6,
		 VMProjections* vmproj7,
		 VMProjections* vmproj8,
		 VMProjections* vmproj9,
		 VMProjections* vmproj10,
		 VMProjections* vmproj11,
		 VMProjections* vmproj12
		 )
  {
    allproj_ = allprojection->get_mem();

    vmprojphi1_ = vmproj1->get_mem();
    vmprojphi2_ = vmproj2->get_mem();
    vmprojphi3_ = vmproj3->get_mem();
    vmprojphi4_ = vmproj4->get_mem();
    vmprojphi5_ = vmproj5->get_mem();
    vmprojphi6_ = vmproj6->get_mem();
    vmprojphi7_ = vmproj7->get_mem();
    vmprojphi8_ = vmproj8->get_mem();
    vmprojphi9_ = vmproj9->get_mem();
    vmprojphi10_ = vmproj10->get_mem();
    vmprojphi11_ = vmproj11->get_mem();
    vmprojphi12_ = vmproj12->get_mem();
  }
  
  // overload 
  void addInputs(TProjData* trackletproj1,
		TProjData* trackletproj2,
		TProjData* trackletproj3,
		TProjData* trackletproj4,
		TProjData* trackletproj5,
		TProjData* trackletproj6,
		TProjData* trackletproj7,
		TProjData* trackletproj8,
		// more
		unsigned int numberin1,
		unsigned int numberin2,
		unsigned int numberin3,
		unsigned int numberin4,
		unsigned int numberin5,
		unsigned int numberin6,
		unsigned int numberin7,
		unsigned int numberin8
		)
  {
    inputproj1_ = trackletproj1;
    inputproj2_ = trackletproj2;
    inputproj3_ = trackletproj3;
    inputproj4_ = trackletproj4;
    inputproj5_ = trackletproj5;
    inputproj6_ = trackletproj6;
    inputproj7_ = trackletproj7;
    inputproj8_ = trackletproj8;

    numbersin_[0] = numberin1;
    numbersin_[1] = numberin2;
    numbersin_[2] = numberin3;
    numbersin_[3] = numberin4;
    numbersin_[4] = numberin5;
    numbersin_[5] = numberin6;
    numbersin_[6] = numberin7;
    numbersin_[7] = numberin8;
  }

  void addOutputs(AllProjData* allprojection,
		 VMProjData* vmproj1,
		 VMProjData* vmproj2,
		 VMProjData* vmproj3,
		 VMProjData* vmproj4,
		 VMProjData* vmproj5,
		 VMProjData* vmproj6,
		 VMProjData* vmproj7,
		 VMProjData* vmproj8,
		 VMProjData* vmproj9,
		 VMProjData* vmproj10,
		 VMProjData* vmproj11,
		 VMProjData* vmproj12
		 )
  {
    allproj_ = allprojection;

    vmprojphi1_ = vmproj1;
    vmprojphi2_ = vmproj2;
    vmprojphi3_ = vmproj3;
    vmprojphi4_ = vmproj4;
    vmprojphi5_ = vmproj5;
    vmprojphi6_ = vmproj6;
    vmprojphi7_ = vmproj7;
    vmprojphi8_ = vmproj8;
    vmprojphi9_ = vmproj9;
    vmprojphi10_ = vmproj10;
    vmprojphi11_ = vmproj11;
    vmprojphi12_ = vmproj12;
  }


private:
  
  // inputs
  TProjData* inputproj1_;
  TProjData* inputproj2_;
  TProjData* inputproj3_;
  TProjData* inputproj4_;
  TProjData* inputproj5_;
  TProjData* inputproj6_;
  TProjData* inputproj7_;
  TProjData* inputproj8_;
  // more

  unsigned int numbersin_[8];

  // outputs
  AllProjData* allproj_;

  VMProjData* vmprojphi1_;
  VMProjData* vmprojphi2_;
  VMProjData* vmprojphi3_;
  VMProjData* vmprojphi4_;
  VMProjData* vmprojphi5_;
  VMProjData* vmprojphi6_;
  VMProjData* vmprojphi7_;
  VMProjData* vmprojphi8_;
  VMProjData* vmprojphi9_;
  VMProjData* vmprojphi10_;
  VMProjData* vmprojphi11_;
  VMProjData* vmprojphi12_;

  /*
  // inputs
  TrackletProjections* inputproj1_;
  TrackletProjections* inputproj2_;
  TrackletProjections* inputproj3_;
  TrackletProjections* inputproj4_;
  TrackletProjections* inputproj5_;
  TrackletProjections* inputproj6_;
  TrackletProjections* inputproj7_;
  TrackletProjections* inputproj8_;
  // more

  // outputs
  AllProjections* allproj_;

  VMProjections* vmprojphi1_;
  VMProjections* vmprojphi2_;
  VMProjections* vmprojphi3_;
  VMProjections* vmprojphi4_;
  VMProjections* vmprojphi5_;
  VMProjections* vmprojphi6_;
  VMProjections* vmprojphi7_;
  VMProjections* vmprojphi8_;
  VMProjections* vmprojphi9_;
  VMProjections* vmprojphi10_;
  VMProjections* vmprojphi11_;
  VMProjections* vmprojphi12_;
  */
};

#endif
