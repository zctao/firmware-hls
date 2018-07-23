#pragma once

#include "Constants.hh"
#include "FullStubLayerPS.hh"

void 
LayerRouter(
	    FullStubLayerPS StubIn[64],
	    FullStubLayerPS StubOut[6][64]
	    //		FullStubLayerPS *StubOut1,
	    //		FullStubLayerPS *StubOut2,
	    //		FullStubLayerPS *StubOut3,
	    //		FullStubLayerPS *StubOut4,
	    //              FullStubLayerPS *StubOut5,
	    //              FullStubLayerPS *StubOut6
	    );
