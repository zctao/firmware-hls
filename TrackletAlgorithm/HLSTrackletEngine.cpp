
#include "HLSTrackletEngine.h"
#include "hls_math.h"
#include <iostream>
#include <fstream>


void readPtTable(bool table[32]){

  bool tmp[]=
#include "../TestBenches/emData_TE/TE_L1PHIE18_L2PHIC17_ptcut.txt"
    
  for (int i=0;i<32;i++){
    table[i]=tmp[i];
  }

}


void readBendInnerTable(bool table[256]){

  bool tmp[]=
#include "../TestBenches/emData_TE/TE_L1PHIE18_L2PHIC17_stubptinnercut.txt"
    
  for (int i=0;i<256;i++){
    table[i]=tmp[i];
  }

}

void readBendOuterTable(bool table[256]){

  bool tmp[]=
#include "../TestBenches/emData_TE/TE_L1PHIE18_L2PHIC17_stubptoutercut.txt"
    
  for (int i=0;i<256;i++){
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
		       ap_uint<7>& outstubpairnumber)
{


  std::cout << "In HLSTrackletEngine "<<hex<<instubinnernumber<<
    " "<<instubouternumber<<dec<<std::endl;

  bool pttable[32];
  readPtTable(pttable);
  
  bool bendinnertable[256];
  readBendInnerTable(bendinnertable);
  
  bool bendoutertable[256];
  readBendOuterTable(bendoutertable);
  

  for (unsigned int istubinner=0;istubinner<instubinnernumber;istubinner++) {
    VMSTEIID innerstubindex=VMStubsTEInner::get_index(instubinnerdata[istubinner]);
    VMSTEIBEND innerstubbend=VMStubsTEInner::get_bend(instubinnerdata[istubinner]);
    VMSTEIFINEPHI innerstubfinephi=VMStubsTEInner::get_finephi(instubinnerdata[istubinner]);
    VMSTEIZBITS innerstubzbits=VMStubsTEInner::get_zbits(instubinnerdata[istubinner]);
    int zdiffmax=innerstubzbits.range(9,7);
    int zbinfirst=innerstubzbits.range(2,0);
    int start=innerstubzbits.range(6,4);
    int last=start+innerstubzbits.range(3,3);

    assert(last<8);
    for (unsigned int ibin=start;ibin<=last;ibin++) {
      int nstubs=instubouternumber.range((ibin+1)*4-1,ibin*4);
      for (unsigned int istubouter=0;istubouter<nstubs;istubouter++) {
	VMSTEOID outerstubindex=VMStubsTEOuter::get_index(instubouterdata[istubouter+16*ibin]);
	VMSTEOFINEPHI outerstubfinephi=VMStubsTEOuter::get_finephi(instubouterdata[istubouter+16*ibin]);
	VMSTEOBEND outerstubbend=VMStubsTEOuter::get_bend(instubouterdata[istubouter+16*ibin]);
	VMSTEOFINEZ outerstubfinez=VMStubsTEOuter::get_finez(instubouterdata[istubouter+16*ibin]);

	int zbin=outerstubfinez;

	if (start!=ibin) zbin+=8;
	if ((zbin<zbinfirst)||(zbin-zbinfirst>zdiffmax)) {
	  continue;
	}


	ap_uint<5> ptindex=innerstubfinephi.concat(outerstubfinephi);

	if (!pttable[ptindex]) {
	  continue;
	}

	ap_uint<8> bendinnerindex=ptindex.concat(innerstubbend);

	if (!bendinnertable[bendinnerindex]) {
	  continue;
	}

	ap_uint<8> bendouterindex=ptindex.concat(outerstubbend);

	if (!bendoutertable[bendouterindex]) {
	  continue;
	}

	outstubpair[outstubpairnumber]=innerstubindex.concat(outerstubindex);
	outstubpairnumber++;  
      }
    }
  }

  std::cout << "Done in HLSTrackletEngine"<<std::endl;

}
