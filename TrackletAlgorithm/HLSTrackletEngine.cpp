
#include "HLSTrackletEngine.h"
#include "hls_math.h"
#include <iostream>
#include <fstream>


void readPtTable(bool table[32]){

  bool tmp[]=
#include "TE_L1PHIE18_L2PHIC17_ptcut.txt"
    
  for (int i=0;i<32;i++){
    table[i]=tmp[i];
  }

}


void HLSTrackletEngine(
		       VMStubTEInner instubinnerdata[kMemDepth],
		       VMStubTEOuter instubouterdata[kMemDepth],
		       // more
		       ap_uint<7> instubinnernumber,
		       ap_uint<32> instubouternumber,
		       StubPair outstubpair[kMemDepth],
		       ap_uint<7>& outstubpairhnumber)
{


  std::cout << "In HLSTrackletEngine "<<hex<<instubinnernumber<<
    " "<<instubouternumber<<dec<<std::endl;

  bool pttable[32];

  readPtTable(pttable);

  for (unsigned int istubinner=0;istubinner<instubinnernumber;istubinner++) {
    ap_uint<7> innerstubindex=VMStubTEInner::get_index(instubinnerdata[iproj]);
    int innerstubzbin=VMStubTEInner::get_zbin(instubinnerdata[iproj]);
    int innerstubfinez=VMStubTEInner::get_finez(instubinnerdata[iproj]);
    ap_uint<2> innerstubfinephi=VMStubTEInner::get_finephi(instubinnerdata[iproj]);
    int zdiffmax=VMStubTEInner::get_zdiffmax(instubinnerdata[iproj]);
    int innerstubbend=VMStubTEInner::get_bend(instubinnerdata[iproj]);
    int zfirst=innerstubzbin.range(3,1);
    int zlast=zfirst+innerstubzbin.range(0,0);
    assert(zlast<8);
    for (unsigned int zbin=zfirst;zbin<=zlast;zbin++) {
      nstubs=instubnumber.range((zbin+1)*4-1,zbin*4);
      for (unsigned int istubouter=0;istubouter<nstubs;istubouter++) {
	VMPID outerstubindex=VMStubsTEOuter::get_index(instubouterdata[istubouter+16*zbin]);
	VMPFINEZ outerstubfinez=VMStubsTEOuter::get_finez(instubouterdata[istubouter+16*zbin]);
	ap_uint<2> outerstubfinephi=VMStubsTEOuter::get_finephi(instubouterdata[istubouter+16*zbin]);
	VMPBEND outerstubbend=VMStubsTEOuter::get_bend(instubouterdata[istubouter+16*zbin]);
	if (zbin!=zfirst) outerstubfinez+=8;
	if ((zbin<innerstubfinez)||(zbin-innerstubfinez>zdiffmax)) {
	  continue;
	}
	ap_uint<5> ptindex=innerstubfinephi.concat(outerstubfinephi);
	if (!pttable[ptindex]) {
	  continue;
	}
	outstubpair[outstubpairnumber]=innerstubindex.concat(outerstubindex);
	outstubpairhnumber++;  
      }
    }
  }

}
