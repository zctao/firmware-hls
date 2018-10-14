#ifndef HLSMATCHENGINE_H
#define HLSMATCHENGINE_H

#include "Constants.hh"
#include "VMProjections.hh"
#include "VMStubs.hh"
#include "CandidateMatches.hh"

class CandMatch;

void HLSMatchEngine(const ap_uint<3> bx,
		    const VMStubs& instubdata, 
		    const VMProjections& inprojdata,
		    CandidateMatches& outcanddata
		    );

#endif
