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
  ProjectionRouter(){
	  iAP_ = 0;
	  iVMP1_ = 0;
	  iVMP2_ = 0;
	  iVMP3_ = 0;
	  iVMP4_ = 0;/*
	  iVMP5_ = 0;
	  iVMP6_ = 0;
	  iVMP7_ = 0;
	  iVMP8_ = 0;
	  iVMP9_ = 0;
	  iVMP10_ = 0;
	  iVMP11_ = 0;
	  iVMP12_ = 0;*/
  }
  ~ProjectionRouter(){}

  //
  void execute()
  {
	  // check which input memories are not empty
	  //bool mem_hasdata_arr[nTProjMem];
	  ap_uint<nTProjMem> mem_hasdata = 0;
	  HASDATA_LOOP: for (int imem = 0; imem < nTProjMem; ++imem) {
#pragma HLS unroll
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
#pragma HLS PIPELINE II=1

		  // read inputs
		  unsigned int addr = addr_next;
		  bool validin = get_mem_read_addr<nTProjMem>(imem, addr_next, mem_hasdata, numbersin_);

		  if (not validin) continue;

		  TProjData tproj = read_mem(imem, addr);

		  TProjPHI iphiproj = tproj.phi;
		  TProjZ izproj = tproj.z;
		  TProjPHIDER iphider = tproj.phider;

		  // routing
		  ap_uint<5> iphi5 = iphiproj>>(iphiproj.length()-5);  // top 5 bits of phi

		  // inner barrel non-hourglass for now
		  assert(iphi5>=4 and iphi5<=27);
		  ap_uint<2> iphi = ((iphi5-4)>>1)&3;
		  assert(iphi>=0 and iphi<=3);

		  // vmproj index
		  VMPID index = i;

		  // vmproj z
		  ap_uint<MEBinsBits> zbin1 = (1<<(MEBinsBits-1))+(((izproj>>(izproj.length()-MEBinsBits-2))-2)>>2);
		  ap_uint<MEBinsBits> zbin2 = (1<<(MEBinsBits-1))+(((izproj>>(izproj.length()-MEBinsBits-2))+2)>>2);
		  if (zbin1 >= (1<<MEBinsBits)) zbin1 = 0;
		  if (zbin2 >= (1<<MEBinsBits)) zbin2 = (1<<MEBinsBits)-1;

		  VMPZBIN zbin = (zbin1, zbin2);
		  VMPFINEZ finez = ((1<<(MEBinsBits+2))+(izproj>>(izproj.length()-(MEBinsBits+3))))-(zbin1<<3);

		  // vmproj irinv
		  VMPRINV rinv = 16 + iphider>>(iphider.length()-5);
		  assert(rinv >=0 and rinv < 32);

		  // PS seed
		  bool psseed = false;  // FIXME

		  VMProjData vmproj = {index, zbin, finez, rinv, psseed};

		  // all projections
		  AllProjData allproj = {
		  				  tproj.plusNeighbor,
		  				  tproj.minusNeighbor,
		  				  tproj.phi,
		  				  tproj.z,
		  				  tproj.phider,
		  				  tproj.zder
		  		  };

		  // write outputs
		  //allproj_ -> add_mem(allproj);
		  *(allproj_+i) = allproj;

		  switch (iphi)
		  {
		  case 0:
			  //vmprojphi1_ -> add_mem(vmproj);
			  *(vmprojphi1_+iVMP1_) = vmproj;
			  iVMP1_++;
			  break;
		  case 1:
			  //vmprojphi2_ -> add_mem(vmproj);
			  *(vmprojphi2_+iVMP2_) = vmproj;
			  iVMP2_++;
		  	  break;
		  case 2:
			  //vmprojphi3_ -> add_mem(vmproj);
			  *(vmprojphi3_+iVMP3_) = vmproj;
			  iVMP3_++;
			  break;
		  case 3:
			  //vmprojphi4_ -> add_mem(vmproj);
			  *(vmprojphi4_+iVMP4_) = vmproj;
			  iVMP4_++;
		  	  break;
		  /*case 4:
			  //vmprojphi5_ -> add_mem(vmproj);
			  *(vmprojphi5_+iVMP5_) = vmproj;
			  iVMP5_++;
			  break;
		  case 5:
			  //vmprojphi6_ -> add_mem(vmproj);
			  *(vmprojphi6_+iVMP6_) = vmproj;
			  iVMP6_++;
		  	  break;
		  case 6:
			  //vmprojphi7_ -> add_mem(vmproj);
			  *(vmprojphi7_+iVMP7_) = vmproj;
			  iVMP7_++;
			  break;
		  case 7:
			  //vmprojphi8_ -> add_mem(vmproj);
			  *(vmprojphi8_+iVMP8_) = vmproj;
			  iVMP8_++;
		  	  break;
		  case 8:
			  //vmprojphi9_ -> add_mem(vmproj);
			  *(vmprojphi9_+iVMP9_) = vmproj;
			  iVMP9_++;
			  break;
		  case 9:
			  //vmprojphi10_ -> add_mem(vmproj);
			  *(vmprojphi10_+iVMP10_) = vmproj;
			  iVMP10_++;
		  	  break;
		  case 10:
			  //vmprojphi11_ -> add_mem(vmproj);
			  *(vmprojphi11_+iVMP11_) = vmproj;
			  iVMP11_++;
			  break;
		  case 11:
			  //vmprojphi12_ -> add_mem(vmproj);
			  *(vmprojphi12_+iVMP12_) = vmproj;
			  iVMP12_++;
		  	  break;*/
		  }

	  } // PROC_LOOP
  } // execute()

  // move this to ProcessBase class?
  template<int nMEM>
  bool get_mem_read_addr(unsigned int& imem, unsigned int& addr, ap_uint<nMEM>& mem_hasdata, unsigned int* numbersin)
  {
	  if (mem_hasdata == 0) return false;

	  // priority encoder
	  imem = __builtin_ctz(mem_hasdata);
	  ++addr;

	  if (addr >= *(numbersin+imem)) {  // All entries have been read out in memory[imem]
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
		 VMProjections* vmproj4/*,
		 VMProjections* vmproj5,
		 VMProjections* vmproj6,
		 VMProjections* vmproj7,
		 VMProjections* vmproj8,
		 VMProjections* vmproj9,
		 VMProjections* vmproj10,
		 VMProjections* vmproj11,
		 VMProjections* vmproj12*/
		 )
  {
    allproj_ = allprojection->get_mem();

    vmprojphi1_ = vmproj1->get_mem();
    vmprojphi2_ = vmproj2->get_mem();
    vmprojphi3_ = vmproj3->get_mem();
    vmprojphi4_ = vmproj4->get_mem();/*
    vmprojphi5_ = vmproj5->get_mem();
    vmprojphi6_ = vmproj6->get_mem();
    vmprojphi7_ = vmproj7->get_mem();
    vmprojphi8_ = vmproj8->get_mem();
    vmprojphi9_ = vmproj9->get_mem();
    vmprojphi10_ = vmproj10->get_mem();
    vmprojphi11_ = vmproj11->get_mem();
    vmprojphi12_ = vmproj12->get_mem();*/
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
		 VMProjData* vmproj4/*,
		 VMProjData* vmproj5,
		 VMProjData* vmproj6,
		 VMProjData* vmproj7,
		 VMProjData* vmproj8,
		 VMProjData* vmproj9,
		 VMProjData* vmproj10,
		 VMProjData* vmproj11,
		 VMProjData* vmproj12*/
		 )
  {
    allproj_ = allprojection;

    vmprojphi1_ = vmproj1;
    vmprojphi2_ = vmproj2;
    vmprojphi3_ = vmproj3;
    vmprojphi4_ = vmproj4;/*
    vmprojphi5_ = vmproj5;
    vmprojphi6_ = vmproj6;
    vmprojphi7_ = vmproj7;
    vmprojphi8_ = vmproj8;
    vmprojphi9_ = vmproj9;
    vmprojphi10_ = vmproj10;
    vmprojphi11_ = vmproj11;
    vmprojphi12_ = vmproj12;*/
  }


private:
  
  //int layer_;
  //int disk_;

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
  unsigned int iAP_;

  VMProjData* vmprojphi1_;
  VMProjData* vmprojphi2_;
  VMProjData* vmprojphi3_;
  VMProjData* vmprojphi4_;/*
  VMProjData* vmprojphi5_;
  VMProjData* vmprojphi6_;
  VMProjData* vmprojphi7_;
  VMProjData* vmprojphi8_;
  VMProjData* vmprojphi9_;
  VMProjData* vmprojphi10_;
  VMProjData* vmprojphi11_;
  VMProjData* vmprojphi12_;*/

  // not really necessary if inputproj_ were pointing to class inherited from MemoryBase
  // TODO: reset logic needed
  unsigned int iVMP1_;
  unsigned int iVMP2_;
  unsigned int iVMP3_;
  unsigned int iVMP4_;/*
  unsigned int iVMP5_;
  unsigned int iVMP6_;
  unsigned int iVMP7_;
  unsigned int iVMP8_;
  unsigned int iVMP9_;
  unsigned int iVMP10_;
  unsigned int iVMP11_;
  unsigned int iVMP12_;*/

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
