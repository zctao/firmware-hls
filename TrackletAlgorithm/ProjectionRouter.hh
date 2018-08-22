// Projection Router
#ifndef PROJECTIONROUTER_HH
#define PROJECTIONROUTER_HH

#include "Constants.hh"
#include "ProcessBase.hh"
//
#include "TrackletProjections.hh"
#include "AllProjections.hh"
#include "VMProjections.hh"

#include <assert.h>

const int nTProjMem = 8;  // FIXME

class ProjectionRouter //: public ProcessBase<nMaxProc>
{
public:

  // constructor
	ProjectionRouter(){}
	/*
  ProjectionRouter(
		  // inputs
		  TProj* tprojin[nTProjMem],
		  //unsigned int numberin[nTProjMem],
		  // outputs
		  AllProj* allprojout,
		  VMProj* vmprojout[4]
  ){
	  //std::cout << "constructor" << std::endl;
	  // connect input & output memories
	  inputproj1_ = tprojin[0];
	  inputproj2_ = tprojin[1];
	  inputproj3_ = tprojin[2];
	  inputproj4_ = tprojin[3];
	  inputproj5_ = tprojin[4];
	  inputproj6_ = tprojin[5];
	  inputproj7_ = tprojin[6];
	  inputproj8_ = tprojin[7];

	  //numbersin_ = numberin;
	  //for (int i=0; i<nTProjMem; i++) {
//#pragma HLS unroll
	//	  numbersin_[i] = numberin[i];
	  //}

	  allproj_ = allprojout;
	  vmprojphi1_ = vmprojout[0];
	  vmprojphi2_ = vmprojout[1];
	  vmprojphi3_ = vmprojout[2];
	  vmprojphi4_ = vmprojout[3];

	  // initialize counters
	  iAP_ = 0;

	  for (int i=0; i<4; ++i) {  // FIXME?
#pragma HLS unroll
		  std::cout << "i = " << i << std::endl;
		  iVMP_[i] = 0;
	  }
	  //std::cout << "end of constructor" << std::endl;
  }
*/
  ~ProjectionRouter(){}

  // called for every event
  //void execute(ap_uint<NBits_MemAddr> numbersin[nTProjMem])
  void execute(TProj* tprojin[nTProjMem], ap_uint<NBits_MemAddr> numbersin[nTProjMem],
		  	  AllProj* allprojout, VMProj* vmprojout[4])
  {
	  //std::cout << "execute" << std::endl;
	  // check which input memories are not empty
	  //bool mem_hasdata_arr[nTProjMem];
	  ap_uint<nTProjMem> mem_hasdata = 0;
	  HASDATA_LOOP: for (int imem = 0; imem < nTProjMem; ++imem) {
#pragma HLS unroll
		  if (numbersin[imem] > 0) {
			  //mem_hasdata_arr[imem] = 1;
			  mem_hasdata += (1<<imem);
		  }
		  //else {
			  //mem_hasdata_arr[imem] = 0;
		  //}
	  }

	  // FIXME: nbits for imem depends on nTProjMem. Hard coded 3 here for nTProjMem=8
	  ap_uint<3> imem = 0;
	  ap_uint<NBits_MemAddr> addr_next = 0;
	  PROC_LOOP: for (int i = 0; i < nMaxProc; ++i) {
#pragma HLS PIPELINE II=1
		  // read inputs
		  ap_uint<NBits_MemAddr> addr = addr_next;
		  bool validin = get_mem_read_addr<3, NBits_MemAddr>(imem, addr_next, mem_hasdata, numbersin);

		  if (not validin) continue;

		  //TProj tproj = read_mem<NBits_MemAddr>(imem, addr);
		  TProj tproj = *(tprojin[imem]+addr);
		  //std::cout << "tproj " << tproj << std::endl;

		  TProjPHI iphiproj = TrackletProjections::get_phi(tproj);
		  TProjZ izproj = TrackletProjections::get_z(tproj);
		  TProjPHIDER iphider = TrackletProjections::get_phider(tproj);

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

		  if (zbin1>=(1<<MEBinsBits)) zbin1=0; //note that zbin1 is unsigned
		  if (zbin2>=(1<<MEBinsBits)) zbin2=(1<<MEBinsBits)-1;
		  assert(zbin1<=zbin2);
		  assert(zbin2-zbin1<=1);

		  VMPZBIN zbin = (zbin1, zbin2!=zbin1);
		  //fine vm z bits. Use 4 bits for fine position. starting at zbin 1
		  // need to be careful about left shift of ap_(u)int
		  VMPFINEZ finez = ((1<<(MEBinsBits+2))+(izproj>>(izproj.length()-(MEBinsBits+3))))-(zbin1,ap_uint<3>(0));

		  // vmproj irinv
		  VMPRINV rinv = 16 + (iphider>>(iphider.length()-5));
		  assert(rinv >=0 and rinv < 32);

		  // PS seed
		  bool psseed = false;  // FIXME

		  // Concatenation
		  VMProj vmproj = ((((index, zbin), finez), rinv), psseed);

		  // FIXME?
		  AllProj aproj = tproj;

		  // write outputs
		  //*(allproj_+i) = aproj;
		  allprojout[i] = aproj;

		  //std::cout << "iphi: " << iphi << std::endl;
		  assert(iphi>=0 and iphi<4);

		  *(vmprojout[iphi]+iVMP_[iphi]++) = vmproj;

		  //*(vmprojphi_[iphi]+iVMP_[iphi]++) = vmproj;
		  /*
		  switch (iphi)
		  {
		  case 0:
			  *(vmprojout[0]+iVMP_[0]++) = vmproj;
			  break;
		  case 1:
			  *(vmprojout[1]+iVMP_[1]++) = vmproj;
			  break;
		  case 2:
			  *(vmprojout[2]+iVMP_[2]++) = vmproj;
			  break;
		  case 3:
			  *(vmprojout[3]+iVMP_[3]++) = vmproj;
			  break;
		  }
		  */

	  } // PROC_LOOP
  } // execute()

  // move this to ProcessBase class?
  template<int nbits_nMEM, int nbits_MemAddr>
  bool get_mem_read_addr(ap_uint<nbits_nMEM>& imem, ap_uint<nbits_MemAddr>& addr,
		  ap_uint<(1<<nbits_nMEM)>& mem_hasdata, ap_uint<nbits_MemAddr>* numbersin)
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
/*
  template<int nbits_MemAddr>
  TProj read_mem(ap_uint<3> imem, ap_uint<nbits_MemAddr> addr)
  {
	  //return *(inputproj_[imem]+addr);
	  //return inputproj_[imem][addr];

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
	  default:
		  return *(inputproj1_+addr);
	  }
  }
*/
  
private:

  //int layer_;
  //int disk_;


  // inputs
  //TProj* inputproj1_;
  //TProj* inputproj2_;
  //TProj* inputproj3_;
  //TProj* inputproj4_;
  //TProj* inputproj5_;
  //TProj* inputproj6_;
  //TProj* inputproj7_;
  //TProj* inputproj8_;
  // more

  //unsigned int* numbersin_;
  //unsigned int numbersin_[nTProjMem];

  // outputs
  //AllProj* allproj_;
  //AllProj allproj_[MemDepth];
  unsigned int iAP_;

  //VMProj* vmprojphi1_;
  //VMProj* vmprojphi2_;
  //VMProj* vmprojphi3_;
  //VMProj* vmprojphi4_;

  unsigned int iVMP_[4];
};

#endif
