// VMRouterDispatcher header file.
#pragma once
#include "Constants.hh"
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "ReducedStubLayer.hh"
#include "VMRouter.hh"


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
                        ReducedIndex (&curnL6)[kNumZRegions][kNumPhiRegions]);

