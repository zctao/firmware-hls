#include "VMStubs.h"
#include "VMProjections.hh"
#include "HLSCandidateMatches.hh"

#include "Streamer.hh"

void SectorProcessor(ap_uint<3>,
		     hls::stream<VMStub>&, hls::stream<VMProj>&,
		     ap_uint<3>,
		     hls::stream<CandMatch>&);
