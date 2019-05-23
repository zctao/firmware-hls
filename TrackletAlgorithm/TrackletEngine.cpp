
#include "TrackletEngine.h"
#include "hls_math.h"
#include <iostream>
#include <fstream>
#include <string.h>

#include "bitonic_sort.hpp"

void  write_sorted( const ap_uint<14> (&tmpout)[16],
		    StubPair (&out)[128],
		    unsigned length,
		    int iteration) {
#pragma HLS PIPELINE
  static unsigned offset = 0;
    if( !iteration ) offset=0;
 writeloop : for( int i=0; i<16; i++ ) { 
    //    if( i == length ) break;
    out[offset+i].data_ = tmpout[i];
  }
  
  offset += length;
}


void  write_sorted( const ap_uint<14> (&tmpout)[8],
		    StubPair (&out)[128],
		    unsigned length,
		    unsigned &offset,
		    int iteration) {
  //#pragma HLS PIPELINE
  //  static unsigned offset = 0;
    if( !iteration ) offset=0;
 writeloop : for( int i=0; i<8; i++ ) { 
    //    if( i == length ) break;
    out[offset+i].data_ = tmpout[i];
    // if( tmpout[i] != 0 )
    //   std::cout << "out["<< offset+i << "].data_ = "
    // 		<<  std::hex << out[offset+i].data_ 
    // 		<< std::dec << std::endl;
    }
  
  offset += length;
}


void readPtTable(ap_uint<1> table[32]){

  ap_uint<1> tmp[]=
#include "TE_L1PHIE18_L2PHIC17_ptcut.tab"//"../emData/TE/TE_L1PHIE18_L2PHIC17/TE_L1PHIE18_L2PHIC17_ptcut.tab"

    PTtableloop: for (unsigned int i=0;i<32;i++){
#pragma HLS PIPELINE
    table[i]=tmp[i];
  }

}


void readBendInnerTable(ap_uint<1> table[256]){

  ap_uint<1> tmp[]=
#include "TE_L1PHIE18_L2PHIC17_stubptinnercut.tab"//"../emData/TE/TE_L1PHIE18_L2PHIC17/TE_L1PHIE18_L2PHIC17_stubptinnercut.tab"

    BItableloop: for (unsigned int i=0;i<256;i++){
#pragma HLS PIPELINE
    table[i]=tmp[i];
  }

}

void readBendOuterTable(ap_uint<1> table[256]){

  ap_uint<1> tmp[]=
#include "TE_L1PHIE18_L2PHIC17_stubptoutercut.tab"//"../emData/TE/TE_L1PHIE18_L2PHIC17/TE_L1PHIE18_L2PHIC17_stubptoutercut.tab"

    BOtableloop: for (int i=0;i<256;i++){
#pragma HLS PIPELINE
    table[i]=tmp[i];
  }

}


void TrackletEngine(
		    ap_uint<3> bx,
		    VMStubTEInnerMemory<BARRELPS>& instubinnerdata,
		    VMStubTEOuterMemory<BARRELPS>& instubouterdata,
		    //		    ap_uint<14> (&tmpoutstubpair)[16],
		    //ap_uint<14> (&tmpoutstubpair)[8],
		    TmpData &tmpoutstubpair,
		    StubPair (&outstubpair)[128]) {
		    
		      //StubPairMemory& outstubpair) {


  //  #pragma HLS dependence variable=outstubpair intra false
  // #pragma HLS dependence variable=outstubpair inter false

#pragma HLS ARRAY_PARTITION variable=tmpoutstubpair.data_ complete dim=0

  // KH for array ...
  //  #pragma HLS ARRAY_PARTITION variable=outstubpair block factor=32 dim=1
  // KH for object?
  #pragma HLS ARRAY_PARTITION variable=instubouterdata complete dim=0
  //  #pragma HLS ARRAY_PARTITION variable=outstubpair complete dim=1
  #pragma HLS ARRAY_PARTITION variable=outstubpair cyclic factor=8 dim=1


  /*
  std::cout << "In TrackletEngine yo "<<instubinnerdata.getEntries(bx);
  for (unsigned int zbin=0;zbin<8;zbin++){
    std::cout<<" "<<instubouterdata.getEntries(bx,zbin);
  }
  std::cout<<std::dec<<std::endl;
  */

  ap_uint<1> pttable[32];
  readPtTable(pttable);

  ap_uint<1> bendinnertable[256];
  readBendInnerTable(bendinnertable);

  ap_uint<1> bendoutertable[256];
  readBendOuterTable(bendoutertable);

  //outstubpair.clear(bx);


  //
  // main loop
  //
  unsigned offset=0;
 innerstubloop:  for (unsigned int i=0; i<16; i++) {
	  // #pragma HLS loop_tripcount min=10 max=50 avg=30
    //#pragma HLS pipeline II=1

  // zeroloop:      for (unsigned int j=0; j<16; j++) {
  //     tmpoutstubpair[j] = 0;
  //   }
    
  binloop:    for (unsigned int k=0; k<2; k++) {
#pragma HLS pipeline II=1
    zeroloop:      for (unsigned int j=0; j<8; j++) {
	tmpoutstubpair.data_[j] = 0;
      }
     
    unsigned length=0;	  
    outerstubloop:      for (unsigned int j=0; j<8; j++) {

	//#pragma HLS UNROLL

	// variables for inner stubs info
	unsigned int nstubinner = instubinnerdata.getEntries(bx);
	VMStubTEInner<BARRELPS>                innerstubdata;
	VMStubTEInner<BARRELPS>::VMSTEIID      innerstubindex;
	VMStubTEInner<BARRELPS>::VMSTEIBEND    innerstubbend;
	VMStubTEInner<BARRELPS>::VMSTEIFINEPHI innerstubfinephi;
	VMStubTEInner<BARRELPS>::VMSTEIZBITS   innerstubzbits;
 

	int zdiffmax, zbinfirst;
	      
	innerstubdata    = instubinnerdata.read_mem(bx,i);
	innerstubindex   = innerstubdata.getIndex();
	innerstubbend    = innerstubdata.getBend();
	innerstubfinephi = innerstubdata.getFinePhi();
	innerstubzbits   = innerstubdata.getZBits();
	
	      
	zdiffmax  = innerstubzbits.range(9,7);
	zbinfirst = innerstubzbits.range(2,0);

	unsigned int ibin  = innerstubzbits.range(6,4) + k;

	
	VMStubTEOuter<BARRELPS>                outerstubdata;
	VMStubTEOuter<BARRELPS>::VMSTEOID      outerstubindex;
	VMStubTEOuter<BARRELPS>::VMSTEOFINEPHI outerstubfinephi;
	VMStubTEOuter<BARRELPS>::VMSTEOBEND    outerstubbend;
	VMStubTEOuter<BARRELPS>::VMSTEOFINEZ   outerstubfinez;

	outerstubdata    = instubouterdata.read_mem(bx,j+16*ibin);
	outerstubindex   = outerstubdata.getIndex();
	outerstubfinephi = outerstubdata.getFinePhi();
	outerstubbend    = outerstubdata.getBend();
	outerstubfinez   = outerstubdata.getFineZ();
	      
	      
	      unsigned int nstubouter = instubouterdata.getEntries(bx,ibin);
	      
	      // adjust z-bin index for the 2nd z-bin
	      // Note: these statements are sort of awkwardly placed here, but the counters need
	      //       to be updated before performing cuts because any failed cut will advance the
	      //       loop to the next iteration...
	      int zbin=outerstubfinez + k*8;
	      	      
	      ap_uint<5> ptindex=innerstubfinephi.concat(outerstubfinephi);
	      ap_uint<8> bendinnerindex=ptindex.concat(innerstubbend);
	      ap_uint<8> bendouterindex=ptindex.concat(outerstubbend);

	      int val0 = (i >= nstubinner || j >= nstubouter); 	      
	      int val1 = ((zbin<zbinfirst)||(zbin-zbinfirst>zdiffmax)) || (!pttable[ptindex]);
	      int val2 = (!bendinnertable[bendinnerindex])  || (!bendoutertable[bendouterindex]) ;
	      int val3 = val0 + val1 + val2;

	      if (!val3 ) {
		// good stub pair, so write it!
		StubPair spair(innerstubindex.concat(outerstubindex));
		//		const int index =  k*8+j;
		const int index =  j;

		if( spair.raw() > 0 ) { 
		  tmpoutstubpair.data_[index] = spair.raw();
		  length++;
		  std::cout << "sp: " << std::hex << spair.raw() << std::dec << std::endl;
		}
	      }

      } // outerstubloop

      bitonic_sort_array(tmpoutstubpair.data_);
      write_sorted( tmpoutstubpair.data_, outstubpair, length, offset, i+k );
      
    } // binloop
  } // innerstubloop
	
	




  std::cout << "Done in TrackletEngine"<<std::endl;

}
