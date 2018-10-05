// Match Engine
#ifndef MATCHENGINE_HH
#define MATCHENGINE_HH

#include "Constants.hh"
//#include "ProcessBase.hh"
//
//#include "TrackletProjections.hh"
//#include "AllProjections.hh"
#include "VMProjections.hh"
#include "VMStubs.hh"
#include "CandidateMatches.hh"

#include <assert.h>

class MatchEngine //: public ProcessBase<nMaxProc>
{
public:

  // constructor
	MatchEngine(){
	  //#pragma HLS ARRAY_PARTITION variable=iVMP_ complete dim=1
	  //bx_ = 0;
	}

  ~MatchEngine(){}

  // called for every event
  void process(ap_uint<3> bx,
	       VMProjections *const vmproj	       ,
	       VMStubs *const vmstub,
	       ap_uint<3>& bx_o,
	       CandidateMatch *const candmatches
  )
  {
	// reset
	//candmatches->clear();
	
	/*
	// logic for reading inputs
	// check the number of entries in the input memories
	ap_uint<8> mem_hasdata = 0;
	ap_uint<kNBits_MemAddr> numbersin[8] = {0,0,0,0,0,0,0,0};
#pragma HLS ARRAY_PARTITION variable=numbersin complete
	
	if (tproj1) {
		ap_uint<kNBits_MemAddr> num1 = tproj1->getEntries(bx);
		numbersin[0] = num1;
		if (num1 > 0) mem_hasdata += (1<<0);
	}
	if (tproj2) {
		ap_uint<kNBits_MemAddr> num2 = tproj2->getEntries(bx);
		numbersin[1] = num2;
		if (num2 > 0) mem_hasdata += (1<<1);
	}
	if (tproj3) {
		ap_uint<kNBits_MemAddr> num3 = tproj3->getEntries(bx);
		numbersin[2] = num3;
		if (num3 > 0) mem_hasdata += (1<<2);
	}
	if (tproj4) {
		ap_uint<kNBits_MemAddr> num4 = tproj4->getEntries(bx);
		numbersin[3] = num4;
		if (num4 > 0) mem_hasdata += (1<<3);
	}
	if (tproj5) {
		ap_uint<kNBits_MemAddr> num5 = tproj5->getEntries(bx);
		numbersin[4] = num5;
		if (num5 > 0) mem_hasdata += (1<<4);
	}
	if (tproj6) {
		ap_uint<kNBits_MemAddr> num6 = tproj6->getEntries(bx);
		numbersin[5] = num6;
		if (num6 > 0) mem_hasdata += (1<<5);
	}
	if (tproj7) {
		ap_uint<kNBits_MemAddr> num7 = tproj7->getEntries(bx);
		numbersin[6] = num7;
		if (num7 > 0) mem_hasdata += (1<<6);
	}
	if (tproj8) {
		ap_uint<kNBits_MemAddr> num8 = tproj8->getEntries(bx);
		numbersin[7] = num8;
		if (num8 > 0) mem_hasdata += (1<<7);
	}

// FIXME: nbits for imem depends on nTProjMem. Hard coded 3 here for nTProjMem=8
	ap_uint<3> imem = 0;
	ap_uint<kNBits_MemAddr> addr_next = 0;
	
  PROC_LOOP: for (int i = 0; i < kMaxProc; ++i) {
#pragma HLS PIPELINE II=1
	  // read inputs
	  ap_uint<kNBits_MemAddr> addr = addr_next;
	  bool validin = get_mem_read_addr<3, kNBits_MemAddr>(imem, addr_next, mem_hasdata, numbersin);

	  if (not validin) continue;

	  // read input memories
	  TProj tproj = 0;

	  switch (imem)
	  {
	  case 0:
	  	  tproj = tproj1->read_mem(bx, addr);
	  	  break;
	  case 1:
		  tproj = tproj2->read_mem(bx, addr);
		  break;
	  case 2:
		  tproj = tproj3->read_mem(bx, addr);
		  break;
	  case 3:
	  	  tproj = tproj4->read_mem(bx, addr);
	  	  break;
	  case 4:
		  tproj = tproj5->read_mem(bx, addr);
		  break;
	  case 5:
	  	  tproj = tproj6->read_mem(bx, addr);
	  	  break;
	  case 6:
	  	  tproj = tproj7->read_mem(bx, addr);
	  	  break;
	  case 7:
	  	  tproj = tproj8->read_mem(bx, addr);
	  	  break;
	  }

	  //std::cout << "tproj " << std::hex << tproj << std::endl;

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
	  allproj->write_mem(bx, aproj);

	  assert(iphi>=0 and iphi<4);
	  switch(iphi) {
	  case 0:
		  vmproj1->write_mem(bx, vmproj);
		  break;
	  case 1:
		  vmproj2->write_mem(bx, vmproj);
		  break;
	  case 2:
		  vmproj3->write_mem(bx, vmproj);
		  break;
	  case 3:
		  vmproj4->write_mem(bx, vmproj);
		  break;
	  }

	  bx_o = bx;
	  
	} // PROC_LOOP
	*/
  } // process
  
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
  
private:


};

#endif
