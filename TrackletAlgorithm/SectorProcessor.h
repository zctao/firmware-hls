#include "TrackletProjections.hh"
#include "VMProjections.hh"
#include "AllProjections.hh"

#include "Streamer.hh"
#include "ProjectionRouter.hh"

void SectorProcessor(ap_uint<3>,
						hls::stream<TProjData>&, hls::stream<TProjData>&, hls::stream<TProjData>&,
						hls::stream<TProjData>&, hls::stream<TProjData>&, hls::stream<TProjData>&,
						ap_uint<3>,
						hls::stream<AllProjData>&,
						hls::stream<VMProjData>&, hls::stream<VMProjData>&,
						hls::stream<VMProjData>&, hls::stream<VMProjData>&);
