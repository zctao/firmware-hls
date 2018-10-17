#include "HLSProjectionRouter.h"

void HLSProjectionRouter(ap_uint<3> bx_in,
						 TrackletProjectionMemory& inproj1,
						 TrackletProjectionMemory& inproj2,
						 TrackletProjectionMemory& inproj3,
						 TrackletProjectionMemory& inproj4,
						 TrackletProjectionMemory& inproj5,
						 TrackletProjectionMemory& inproj6,
						 TrackletProjectionMemory& inproj7,
						 TrackletProjectionMemory& inproj8,

						 ap_uint<3>& bx_out,
						 AllProjectionMemory& outallproj,
						 VMProjectionMemory& outvmproj1,
						 VMProjectionMemory& outvmproj2,
						 VMProjectionMemory& outvmproj3,
						 VMProjectionMemory& outvmproj4)
{
	/////////////////////////////////////
	// Processing module under test
	static ProjectionRouter aPR;
	aPR.process(bx_in,
				&inproj1, &inproj2, &inproj3, &inproj4,
				&inproj5, &inproj6, &inproj7, &inproj8,
				bx_out,
				&outallproj, &outvmproj1, &outvmproj2, &outvmproj3, &outvmproj4
				);
}
