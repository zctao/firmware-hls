
#include "HLSMatchEngine.h"
#include "hls_math.h"
#include <iostream>
#include <fstream>


void readTable(bool table[256]){

  //ifstream in;
  //in.open("emData_ME/METable_ME_L1PHIE20.dat");
  for (int i=0;i<256;i++){
    table[i]=true;
    //in >> table[i];
  }

}


void HLSMatchEngine(
			     VMStub instubdata[kMemDepth],
			     VMProj inprojdata[kMemDepth],
			     // more
			     ap_uint<32> instubnumber,
			     ap_uint<7> inprojnumber,
			     CandidateMatch outcandmatch[kMemDepth],
			     ap_uint<7>& outcandmatchnumber)
{


  std::cout << "In HLSMatchEngine "<<hex<<instubnumber<<
    " "<<inprojnumber<<dec<<std::endl;

  bool table[256];

  readTable(table);

  outcandmatchnumber=0;
  unsigned int iproj=0;
  int istub=0;
  int zbin=0;
  VMPID projindex;
  VMPZBIN projzbin;
  VMPFINEZ projfinez;
  VMPBEND projbend;
  bool isPSseed;
  int zfirst;
  int zlast;
  int nstubs;

  for (unsigned int istep=0;istep<108;istep++) {
#pragma HLS PIPELINE II=1
    if (istep==0||(istep>0&&zbin>zlast)) {
      if (istep>0&&zbin>zlast) {
	iproj++;
	if (iproj>=inprojnumber) continue;
      }
      projindex=VMProjections::get_index(inprojdata[iproj]);
      projzbin=VMProjections::get_zbin(inprojdata[iproj]);
      projfinez=VMProjections::get_finez(inprojdata[iproj]);
      projbend=VMProjections::get_bend(inprojdata[iproj]);
      isPSseed=VMProjections::get_PSseed(inprojdata[iproj]);
      //std::cout << "proj : "<<inprojdata[iproj]<<" "<<projindex<<" "<<projzbin 
    //      <<" "<<projfinez<<" "<<projbend<<" "<<isPSseed<< std::endl;
      zfirst=projzbin.range(3,1);
      zlast=zfirst+projzbin.range(0,0);
      assert(zlast<8);
      zbin=zfirst;
      nstubs=instubnumber.range((zbin+1)*4-1,zbin*4);
    }
    if (nstubs>0) {
      //std::cout << "zbin nstubs "<<zbin<<" "<<nstubs<<std::endl;
      VMPID stubindex=VMStubs::get_index(instubdata[istub+16*zbin]);
      VMPFINEZ stubfinez=VMStubs::get_finez(instubdata[istub+16*zbin]);
      VMPBEND stubbend=VMStubs::get_bend(instubdata[istub+16*zbin]);
      //std::cout << "stub : "<<instubdata[istub+16*zbin]
      //	  <<" "<<stubindex 
      //	  <<" "<<stubfinez 
      //	  <<" "<<stubbend 
      //	  <<endl;
      int idz=stubfinez-projfinez;
      if (zbin!=zfirst) idz+=8;
      bool pass=hls::abs(idz)<=5;
      if (isPSseed) {
	pass=hls::abs(idz)<=2;
      }
      int index=stubbend+projbend*8;
      
      if (pass&&table[index]) {
	CandidateMatch cmatch=projindex;
	cmatch=(cmatch<<7)+stubindex;
	outcandmatch[outcandmatchnumber++]=cmatch;
      }

      //std::cout << "Cand match "<<projindex<<" "<<stubindex<<" "
      //	  <<pass<<" "<<table[index]<<" "<<projbend<<std::endl;
      //std::cout << "stubfinez projfinez "<<stubfinez<<" "<<projfinez<<endl;
    }
    if ((istub++)>=nstubs) {
      istub=0;
      if ((zbin++)<=zlast) {
	nstubs=instubnumber.range((zbin+1)*4-1,zbin*4);
      }
    }
  }

}
