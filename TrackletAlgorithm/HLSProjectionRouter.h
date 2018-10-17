#ifndef PROJECTIONROUTERWRAPPER_H
#define PROJECTIONROUTERWRAPPER_H

#include "ProjectionRouter.hh"

void HLSProjectionRouter(ap_uint<3>,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 TrackletProjectionMemory&,
						 ap_uint<3>&,
						 AllProjectionMemory&,
						 VMProjectionMemory&,
						 VMProjectionMemory&,
						 VMProjectionMemory&,
						 VMProjectionMemory&);

#endif
