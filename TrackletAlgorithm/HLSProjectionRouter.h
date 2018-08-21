#ifndef PROJECTIONROUTERWRAPPER_H
#define PROJECTIONROUTERWRAPPER_H

#include "ProjectionRouter.hh"

void HLSProjectionRouter(
		TProj*, TProj*, TProj*, TProj*, TProj*, TProj*, TProj*, TProj*,
		ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>, ap_uint<NBits_MemAddr>,
	    // more
		AllProj*,
	    VMProj*, VMProj*, VMProj*, VMProj*
		);

#endif
