// VMRouter test bench

#include "ap_int.h"
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <bitset>


#include "Constants.hh"
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "ReducedStubLayer.hh"
#include "VMRouterDispatcher.hh"
#include "HelperFunctions.hh"

using namespace std;

// top level test for one sector


int main()
{
  // ****** DECLARE ALL ARRAY VARIABLES ******
//  FullStubLayerPS stubsInLayerPS[MAX_nSTUBS];
//  FullStubLayerPS allStubsPS[MAX_nSTUBS];
//  FullStubLayer2S stubsInLayer2S[MAX_nSTUBS];
//  FullStubLayer2S allStubs2S[MAX_nSTUBS];
  ReducedStubLayer curvmStubsL1[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  ReducedStubLayer curvmStubsL2[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  ReducedStubLayer curvmStubsL3[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  ReducedStubLayer curvmStubsL4[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  ReducedStubLayer curvmStubsL5[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  ReducedStubLayer curvmStubsL6[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  int curnStubs[6] = { 20, 23, 14, 0, 0, 0};
  ReducedIndex curnL1[kNumZRegions][kNumPhiRegions];
  ReducedIndex curnL2[kNumZRegions][kNumPhiRegions];
  ReducedIndex curnL3[kNumZRegions][kNumPhiRegions];
  ReducedIndex curnL4[kNumZRegions][kNumPhiRegions];
  ReducedIndex curnL5[kNumZRegions][kNumPhiRegions];
  ReducedIndex curnL6[kNumZRegions][kNumPhiRegions];

  FullStubLayerPS curStubsInLayerPSL1[MAX_nSTUBS];
  FullStubLayerPS curAllStubsPSL1[MAX_nSTUBS];
  FullStubLayerPS curStubsInLayerPSL2[MAX_nSTUBS];
  FullStubLayerPS curAllStubsPSL2[MAX_nSTUBS];
  FullStubLayerPS curStubsInLayerPSL3[MAX_nSTUBS];
  FullStubLayerPS curAllStubsPSL3[MAX_nSTUBS];
  FullStubLayer2S curStubsInLayer2SL4[MAX_nSTUBS];
  FullStubLayer2S curAllStubs2SL4[MAX_nSTUBS];
  FullStubLayer2S curStubsInLayer2SL5[MAX_nSTUBS];
  FullStubLayer2S curAllStubs2SL5[MAX_nSTUBS];
  FullStubLayer2S curStubsInLayer2SL6[MAX_nSTUBS];
  FullStubLayer2S curAllStubs2SL6[MAX_nSTUBS];
#ifndef __SYNTHESIS__
  for (int i = 0; i < MAX_nSTUBS; ++i) {
	  curStubsInLayerPSL1[i].AddStub(ap_uint<36>(0x123456789ULL));
	  curStubsInLayerPSL2[i].AddStub(ap_uint<36>(0xbabefaceAULL));
	  curStubsInLayerPSL3[i].AddStub(ap_uint<36>(0xbeefbabeAULL));
	  //std::cout << curStubsInLayerPSL1[i] << std::endl;
  }

  std::cout << __func__ << ": before" << std::endl;

#endif // SYNTHESIS
  // ReducedIndex curnL1[kNumZRegions][kNumPhiRegions];
  // ReducedIndex curnL2[kNumZRegions][kNumPhiRegions];
  // ReducedIndex curnL3[kNumZRegions][kNumPhiRegions];
  // ReducedIndex curnL4[kNumZRegions][kNumPhiRegions];
  // ReducedIndex curnL5[kNumZRegions][kNumPhiRegions];
  // ReducedIndex curnL6[kNumZRegions][kNumPhiRegions];

  for (int i=0; i<MAX_nEVENTS; ++i)
  {

    VMRouterDispatcher(
		       curStubsInLayerPSL1,
		       curAllStubsPSL1,
		       curStubsInLayerPSL2,
		       curAllStubsPSL2,
		       curStubsInLayerPSL3,
		       curAllStubsPSL3,
		       curStubsInLayer2SL4,
		       curAllStubs2SL4,
		       curStubsInLayer2SL5,
		       curAllStubs2SL5,
		       curStubsInLayer2SL6,
		       curAllStubs2SL6,
		       curvmStubsL1,
		       curvmStubsL2,
		       curvmStubsL3,
		       curvmStubsL4,
		       curvmStubsL5,
		       curvmStubsL6,
		       curnStubs,
		       curnL1,
		       curnL2,
		       curnL3,
		       curnL4,
		       curnL5,
		       curnL6);
		       // (&curvmStubsL1)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
		       // (&curvmStubsL2)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
		       // (&curvmStubsL3)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
		       // (&curvmStubsL4)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
		       // (&curvmStubsL5)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
		       // (&curvmStubsL6)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
		       // (&curnStubs)[6],
		       // (&curnL1)[kNumZRegions][kNumPhiRegions],
		       // (&curnL2)[kNumZRegions][kNumPhiRegions],
		       // (&curnL3)[kNumZRegions][kNumPhiRegions],
		       // (&curnL4)[kNumZRegions][kNumPhiRegions],
		       // (&curnL5)[kNumZRegions][kNumPhiRegions],
		       // (&curnL6)[kNumZRegions][kNumPhiRegions]);

  }



  return 0;
}




