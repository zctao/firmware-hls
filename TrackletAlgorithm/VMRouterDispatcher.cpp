// VMRouterDispatcher module
#include "Constants.hh"
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "ReducedStubLayer.hh"
#include "VMRouter.hh"


#ifndef __SYNTHESIS__
#include <iostream>
#endif // SYNTH

// call for a single sector
void VMRouterDispatcher(
			FullStubLayerPS & curStubsInLayerPSL1[MAX_nSTUBS],
                        FullStubLayerPS & curAllStubsPSL1[MAX_nSTUBS],
			FullStubLayerPS & curStubsInLayerPSL2[MAX_nSTUBS],
                        FullStubLayerPS & curAllStubsPSL2[MAX_nSTUBS],
			FullStubLayerPS & curStubsInLayerPSL3[MAX_nSTUBS],
                        FullStubLayerPS & curAllStubsPSL3[MAX_nSTUBS],
			FullStubLayer2S & curStubsInLayer2SL4[MAX_nSTUBS],
                        FullStubLayer2S & curAllStubs2SL4[MAX_nSTUBS],
			FullStubLayer2S & curStubsInLayer2SL5[MAX_nSTUBS],
                        FullStubLayer2S & curAllStubs2SL5[MAX_nSTUBS],
			FullStubLayer2S & curStubsInLayer2SL6[MAX_nSTUBS],
                        FullStubLayer2S & curAllStubs2SL6[MAX_nSTUBS],
                        ReducedStubLayer (&curvmStubsL1)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
                        ReducedStubLayer (&curvmStubsL2)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
			ReducedStubLayer (&curvmStubsL3)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
			ReducedStubLayer (&curvmStubsL4)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
			ReducedStubLayer (&curvmStubsL5)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
                        ReducedStubLayer (&curvmStubsL6)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
                        int (&curnStubs)[6],
                        ReducedIndex (&curnL1)[kNumZRegions][kNumPhiRegions],
			ReducedIndex (&curnL2)[kNumZRegions][kNumPhiRegions],
			ReducedIndex (&curnL3)[kNumZRegions][kNumPhiRegions],
                        ReducedIndex (&curnL4)[kNumZRegions][kNumPhiRegions],
                        ReducedIndex (&curnL5)[kNumZRegions][kNumPhiRegions],
                        ReducedIndex (&curnL6)[kNumZRegions][kNumPhiRegions])

{


  // PS Layers
  // Layer 1 - L1
  // static ReducedStubLayer curvmStubsL1[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  // static ReducedIndex curnL1[kNumZRegions][kNumPhiRegions];

#ifndef __SYNTHESIS__
  std::cout << "constructor 1" << std::endl;
#endif

   VMRouter<FullStubLayerPS> l1(
				curStubsInLayerPSL1,
				      &curAllStubsPSL1[MAX_nSTUBS],
				      curvmStubsL1,
				      curnL1,
				      1
				      );
#ifndef __SYNTHESIS__
  std::cout << "before execute" << std::endl;
  for ( int i = 0; i < MAX_nSTUBS; ++i ) {
	  std::cout << "input " << i << ": " << curStubsInLayerPSL1[i] << std::endl;
  }
  for ( int i = 0; i < MAX_nSTUBS; ++i ){
    int routeZ = 0; int routePhi = 3;
	std::cout << __func__ << ": " 
		  << "[" << routeZ << "][" << routePhi << "][" << i << "]: "
		  <<  curvmStubsL1[routeZ][routePhi][i] << std::endl;
  }
  std::cout << "execute 1" << std::endl;
#endif
  l1.execute(curnStubs[0]);
#ifndef __SYNTHESIS__
  std::cout << "after execute" << std::endl;
  for ( int i = 0; i < MAX_nSTUBS; ++i ){
    int routeZ = 0; int routePhi = 3;
	std::cout << __func__ << ": " 
		  << "[" << routeZ << "][" << routePhi << "][" << i << "]: "
		  <<  curvmStubsL1[routeZ][routePhi][i] << std::endl;
  }
#endif //SYNTHESIS
  // Layer 2 - L2
  // static ReducedStubLayer curvmStubsL2[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  // static ReducedIndex curnL2[kNumZRegions][kNumPhiRegions];

  static VMRouter<FullStubLayerPS> l2(
				      &curStubsInLayerPSL2[MAX_nSTUBS],
				      &curAllStubsPSL2[MAX_nSTUBS],
				      curvmStubsL2,
				      curnL2,
				      2
				      );
  l2.execute(curnStubs[1]);
  // Layer 3 - L3
  // static ReducedStubLayer curvmStubsL3[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  // static ReducedIndex curnL3[kNumZRegions][kNumPhiRegions];

  static VMRouter<FullStubLayerPS> l3(
				      &curStubsInLayerPSL3[MAX_nSTUBS],
				      &curAllStubsPSL3[MAX_nSTUBS],
				      curvmStubsL3,
				      curnL3,
				      3
				      );
  l3.execute(curnStubs[2]);
  // 2S Layers
  // Layer 4 - L4
  // static ReducedStubLayer curvmStubsL4[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  // static ReducedIndex curnL4[kNumZRegions][kNumPhiRegions];

  static VMRouter<FullStubLayer2S> l4(
				      &curStubsInLayer2SL4[MAX_nSTUBS],
				      &curAllStubs2SL4[MAX_nSTUBS],
				      curvmStubsL4,
				      curnL4,
				      4
				      );

  l4.execute(curnStubs[3]);
  // Layer 5 - L5
  // static ReducedStubLayer curvmStubsL5[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  // static ReducedIndex curnL5[kNumZRegions][kNumPhiRegions];

  static VMRouter<FullStubLayer2S> l5(
				      &curStubsInLayer2SL5[MAX_nSTUBS],
				      &curAllStubs2SL5[MAX_nSTUBS],
				      curvmStubsL5,
				      curnL5,
				      5
				      );

  l5.execute(curnStubs[4]);
  // Layer 6 - L6
  // static ReducedStubLayer curvmStubsL6[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  // static ReducedIndex curnL6[kNumZRegions][kNumPhiRegions];

  static VMRouter<FullStubLayer2S> l6(
				      &curStubsInLayer2SL6[MAX_nSTUBS],
				      &curAllStubs2SL6[MAX_nSTUBS],
				      curvmStubsL6,
				      curnL6,
				      6
				      );

  l6.execute(curnStubs[5]);

  return;
}

