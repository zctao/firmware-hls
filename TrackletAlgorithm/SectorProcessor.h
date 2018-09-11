#include "TrackletProjections.hh"
#include "VMProjections.hh"
#include "AllProjections.hh"

#include "Streamer.hh"
#include "ProjectionRouter.hh"

void SectorProcessor(ap_uint<3>,
						hls::stream<TProj>&, hls::stream<TProj>&, hls::stream<TProj>&,
						hls::stream<TProj>&, hls::stream<TProj>&, hls::stream<TProj>&,
						ap_uint<3>,
						hls::stream<AllProj>&,
						hls::stream<VMProj>&, hls::stream<VMProj>&,
						hls::stream<VMProj>&, hls::stream<VMProj>&);
