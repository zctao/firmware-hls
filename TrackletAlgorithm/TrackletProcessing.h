#include "TrackletProjections.hh"
#include "VMProjections.hh"
#include "AllProjections.hh"

#include "Streamer.hh"
#include "ProjectionRouter.hh"

void TrackletProcessing(ap_uint<3>, hls::stream<TProj>*(&)[6], ap_uint<3>,
						hls::stream<AllProj>*, hls::stream<VMProj>*(&)[4]);
