#ifndef MATCHENGINEWRAPPER_H
#define MATCHENGINEWRAPPER_H

#include "MatchEngine.hh"

class CandMatch;

void HLSMatchEngine(
		VMStub instubdata[kMemDepth], VMProj inprojdata[kMemDepth],
		ap_uint<4> stubentries[8], ap_uint<7> nproj,
	    // more
		CandidateMatch outcanddata[kMemDepth], ap_uint<7>&
		);

#endif
