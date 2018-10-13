#ifndef TRACKLETENGINEWRAPPER_H
#define TRACKLETENGINEWRAPPER_H

#include "VMStubsTEInner.hh"
#include "VMStubsTEOuter.hh"
#include "StubPairs.hh"

class CandMatch;

void HLSTrackletEngine(
		VMStubTEInner instubinnerdata[kMemDepth], VMStubTEOuter instubouterdata[kMemDepth],
		ap_uint<7>, ap_uint<32>,
	    // more
		StubPair outstubpairdata[kMemDepth], ap_uint<7>&
		);

#endif
