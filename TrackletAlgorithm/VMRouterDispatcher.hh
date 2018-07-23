// VMRouterDispatcher header file.
#pragma once
#include "Constants.hh"
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "ReducedStubLayer.hh"
#include <vector>

using namespace std;

void VMRouterDispatcher(FullStubLayerPS curStubsInLayerPS[MAX_nSTUBS*MAX_nSECTORS*MAX_nINNERRS],
                        FullStubLayerPS curAllStubsPS[MAX_nSTUBS*MAX_nSECTORS*MAX_nINNERRS],
			FullStubLayer2S curStubsInLayer2S[MAX_nSTUBS*MAX_nSECTORS*MAX_nOUTERRS],
                        FullStubLayer2S curAllStubs2S[MAX_nSTUBS*MAX_nSECTORS*MAX_nOUTERRS],
                        ReducedStubLayer curvmStubsPH1Z1[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH2Z1[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH3Z1[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH4Z1[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH1Z2[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH2Z2[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH3Z2[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        ReducedStubLayer curvmStubsPH4Z2[MAX_nSTUBS*MAX_nSECTORS*MAX_nREGIONS],
                        int curnStubs[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH1Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH2Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH3Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH4Z1[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH1Z2[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH2Z2[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH3Z2[MAX_nSECTORS*MAX_nREGIONS],
                        ReducedIndex curnPH4Z2[MAX_nSECTORS*MAX_nREGIONS]);
