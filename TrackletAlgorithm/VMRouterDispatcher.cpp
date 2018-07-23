// VMRouterDispatcher module
#include "Constants.hh"
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "ReducedStubLayer.hh"
#include "VMRouter.hh"
#include <vector>

// call for a single sector
void VMRouterDispatcher(FullStubLayerPS curStubsInLayerPS[MAX_nSTUBS*MAX_nINNERRS],
                        FullStubLayerPS curAllStubsPS[MAX_nSTUBS*MAX_nINNERRS],
             			FullStubLayer2S curStubsInLayer2S[MAX_nSTUBS*MAX_nOUTERRS],
                        FullStubLayer2S curAllStubs2S[MAX_nSTUBS*MAX_nOUTERRS],
                        ReducedStubLayer curvmStubsPH1Z1[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH2Z1[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH3Z1[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH4Z1[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH1Z2[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH2Z2[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH3Z2[MAX_nSTUBS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH4Z2[MAX_nSTUBS*MAX_nREGIONS],
                        int curnStubs[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH1Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH2Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH3Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH4Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH1Z2[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH2Z2[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH3Z2[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH4Z2[MAX_nSECTORS*MAX_nREGIONS])
{
  #pragma HLS ARRAY_PARTITION variable=curStubsInLayerPS block factor=MAX_nSECTORS*MAX_nINNERRS
  #pragma HLS DEPENDENCE variable=curStubsInLayerPS inter false
  #pragma HLS ARRAY_PARTITION variable=curAllStubsPS block factor=MAX_nSECTORS*MAX_nINNERRS
  #pragma HLS DEPENDENCE variable=curAllStubsPS inter false
  #pragma HLS ARRAY_PARTITION variable=curStubsInLayer2S block factor=MAX_nSECTORS*MAX_nOUTERRS
  #pragma HLS DEPENDENCE variable=curStubsInLayer2S inter false
  #pragma HLS ARRAY_PARTITION variable=curAllStubs2S block factor=MAX_nSECTORS*MAX_nOUTERRS
  #pragma HLS DEPENDENCE variable=curAllStubs2S inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH1Z1 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH1Z1 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH2Z1 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH2Z1 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH3Z1 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH3Z1 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH4Z1 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH4Z1 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH1Z2 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH1Z2 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH2Z2 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH2Z2 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH3Z2 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH3Z2 inter false
  #pragma HLS ARRAY_PARTITION variable=curvmStubsPH4Z2 block factor=MAX_nSECTORS*MAX_nREGIONS
  #pragma HLS DEPENDENCE variable=curvmStubsPH4Z2 inter false
  #pragma HLS ARRAY_PARTITION variable=curnStubs complete
  #pragma HLS ARRAY_PARTITION variable=curnPH1Z1 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH2Z1 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH3Z1 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH4Z1 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH1Z2 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH2Z2 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH3Z2 complete
  #pragma HLS ARRAY_PARTITION variable=curnPH4Z2 complete

  for (int j=1; j<2; ++j) // HACK
  {
    #pragma HLS UNROLL
    VMRouter<FullStubLayerPS,1>(&curStubsInLayerPS[j*MAX_nSTUBS+0*MAX_nSTUBS], &curAllStubsPS[j*MAX_nSTUBS+0*MAX_nSTUBS],
                &curvmStubsPH1Z1[j*MAX_nSTUBS+0*MAX_nSTUBS], &curvmStubsPH2Z1[j*MAX_nSTUBS+0*MAX_nSTUBS],
                &curvmStubsPH3Z1[j*MAX_nSTUBS+0*MAX_nSTUBS], &curvmStubsPH4Z1[j*MAX_nSTUBS+0*MAX_nSTUBS],
                &curvmStubsPH1Z2[j*MAX_nSTUBS+0*MAX_nSTUBS], &curvmStubsPH2Z2[j*MAX_nSTUBS+0*MAX_nSTUBS],
                &curvmStubsPH3Z2[j*MAX_nSTUBS+0*MAX_nSTUBS], &curvmStubsPH4Z2[j*MAX_nSTUBS+0*MAX_nSTUBS],
                curnStubs[j+0],
                &curnPH1Z1[j+0], &curnPH2Z1[j+0], &curnPH3Z1[j+0], &curnPH4Z1[j+0],
                &curnPH1Z2[j+0], &curnPH2Z2[j+0], &curnPH3Z2[j+0], &curnPH4Z2[j+0]);

    VMRouter<FullStubLayerPS,2>(&curStubsInLayerPS[j*MAX_nSTUBS+1*MAX_nSTUBS], &curAllStubsPS[j*MAX_nSTUBS+1*MAX_nSTUBS],
                &curvmStubsPH1Z1[j*MAX_nSTUBS+1*MAX_nSTUBS], &curvmStubsPH2Z1[j*MAX_nSTUBS+1*MAX_nSTUBS],
                &curvmStubsPH3Z1[j*MAX_nSTUBS+1*MAX_nSTUBS], &curvmStubsPH4Z1[j*MAX_nSTUBS+1*MAX_nSTUBS],
                &curvmStubsPH1Z2[j*MAX_nSTUBS+1*MAX_nSTUBS], &curvmStubsPH2Z2[j*MAX_nSTUBS+1*MAX_nSTUBS],
                &curvmStubsPH3Z2[j*MAX_nSTUBS+1*MAX_nSTUBS], &curvmStubsPH4Z2[j*MAX_nSTUBS+1*MAX_nSTUBS],
                curnStubs[j+1],
                &curnPH1Z1[j+1], &curnPH2Z1[j+1], &curnPH3Z1[j+1], &curnPH4Z1[j+1],
                &curnPH1Z2[j+1], &curnPH2Z2[j+1], &curnPH3Z2[j+1], &curnPH4Z2[j+1]);

    VMRouter<FullStubLayerPS,3>(&curStubsInLayerPS[j*MAX_nSTUBS+2*MAX_nSTUBS], &curAllStubsPS[j*MAX_nSTUBS+2*MAX_nSTUBS],
                &curvmStubsPH1Z1[j*MAX_nSTUBS+2*MAX_nSTUBS], &curvmStubsPH2Z1[j*MAX_nSTUBS+2*MAX_nSTUBS],
                &curvmStubsPH3Z1[j*MAX_nSTUBS+2*MAX_nSTUBS], &curvmStubsPH4Z1[j*MAX_nSTUBS+2*MAX_nSTUBS],
                &curvmStubsPH1Z2[j*MAX_nSTUBS+2*MAX_nSTUBS], &curvmStubsPH2Z2[j*MAX_nSTUBS+2*MAX_nSTUBS],
                &curvmStubsPH3Z2[j*MAX_nSTUBS+2*MAX_nSTUBS], &curvmStubsPH4Z2[j*MAX_nSTUBS+2*MAX_nSTUBS],
                curnStubs[j+2],
                &curnPH1Z1[j+2], &curnPH2Z1[j+2], &curnPH3Z1[j+2], &curnPH4Z1[j+2],
                &curnPH1Z2[j+2], &curnPH2Z2[j+2], &curnPH3Z2[j+2], &curnPH4Z2[j+2]);

    VMRouter<FullStubLayer2S,4>(&curStubsInLayer2S[j*MAX_nSTUBS+0*MAX_nSTUBS], &curAllStubs2S[j*MAX_nSTUBS+0*MAX_nSTUBS],
                &curvmStubsPH1Z1[j*MAX_nSTUBS+3*MAX_nSTUBS], &curvmStubsPH2Z1[j*MAX_nSTUBS+3*MAX_nSTUBS],
                &curvmStubsPH3Z1[j*MAX_nSTUBS+3*MAX_nSTUBS], &curvmStubsPH4Z1[j*MAX_nSTUBS+3*MAX_nSTUBS],
                &curvmStubsPH1Z2[j*MAX_nSTUBS+3*MAX_nSTUBS], &curvmStubsPH2Z2[j*MAX_nSTUBS+3*MAX_nSTUBS],
                &curvmStubsPH3Z2[j*MAX_nSTUBS+3*MAX_nSTUBS], &curvmStubsPH4Z2[j*MAX_nSTUBS+3*MAX_nSTUBS],
                curnStubs[j+3],
                &curnPH1Z1[j+3], &curnPH2Z1[j+3], &curnPH3Z1[j+3], &curnPH4Z1[j+3],
                &curnPH1Z2[j+3], &curnPH2Z2[j+3], &curnPH3Z2[j+3], &curnPH4Z2[j+3]);

    VMRouter<FullStubLayer2S,5>(&curStubsInLayer2S[j*MAX_nSTUBS+1*MAX_nSTUBS], &curAllStubs2S[j*MAX_nSTUBS+1*MAX_nSTUBS],
                &curvmStubsPH1Z1[j*MAX_nSTUBS+4*MAX_nSTUBS], &curvmStubsPH2Z1[j*MAX_nSTUBS+4*MAX_nSTUBS],
                &curvmStubsPH3Z1[j*MAX_nSTUBS+4*MAX_nSTUBS], &curvmStubsPH4Z1[j*MAX_nSTUBS+4*MAX_nSTUBS],
                &curvmStubsPH1Z2[j*MAX_nSTUBS+4*MAX_nSTUBS], &curvmStubsPH2Z2[j*MAX_nSTUBS+4*MAX_nSTUBS],
                &curvmStubsPH3Z2[j*MAX_nSTUBS+4*MAX_nSTUBS], &curvmStubsPH4Z2[j*MAX_nSTUBS+4*MAX_nSTUBS],
                curnStubs[j+4],
                &curnPH1Z1[j+4], &curnPH2Z1[j+4], &curnPH3Z1[j+4], &curnPH4Z1[j+4],
                &curnPH1Z2[j+4], &curnPH2Z2[j+4], &curnPH3Z2[j+4], &curnPH4Z2[j+4]);

    VMRouter<FullStubLayer2S,6>(&curStubsInLayer2S[j*MAX_nSTUBS+2*MAX_nSTUBS], &curAllStubs2S[j*MAX_nSTUBS+2*MAX_nSTUBS],
                &curvmStubsPH1Z1[j*MAX_nSTUBS+5*MAX_nSTUBS], &curvmStubsPH2Z1[j*MAX_nSTUBS+5*MAX_nSTUBS],
                &curvmStubsPH3Z1[j*MAX_nSTUBS+5*MAX_nSTUBS], &curvmStubsPH4Z1[j*MAX_nSTUBS+5*MAX_nSTUBS],
                &curvmStubsPH1Z2[j*MAX_nSTUBS+5*MAX_nSTUBS], &curvmStubsPH2Z2[j*MAX_nSTUBS+5*MAX_nSTUBS],
                &curvmStubsPH3Z2[j*MAX_nSTUBS+5*MAX_nSTUBS], &curvmStubsPH4Z2[j*MAX_nSTUBS+5*MAX_nSTUBS],
                curnStubs[j+5],
                &curnPH1Z1[j+5], &curnPH2Z1[j+5], &curnPH3Z1[j+5], &curnPH4Z1[j+5],
                &curnPH1Z2[j+5], &curnPH2Z2[j+5], &curnPH3Z2[j+5], &curnPH4Z2[j+5]);
  }
}

