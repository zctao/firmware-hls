#include "SectorProcessor.h"

void SectorProcessor
(// inputs
 ap_uint<3> bx_in,
 hls::stream<TProj>& input_stream1,
 hls::stream<TProj>& input_stream2,
 hls::stream<TProj>& input_stream3,
 hls::stream<TProj>& input_stream4,
 hls::stream<TProj>& input_stream5,
 hls::stream<TProj>& input_stream6,
 // outputs
 ap_uint<3> bx_out,
 hls::stream<AllProj>& output_stream,
 hls::stream<VMProj>& output2_stream1,
 hls::stream<VMProj>& output2_stream2,
 hls::stream<VMProj>& output2_stream3,
 hls::stream<VMProj>& output2_stream4
)
{
  // Memory modules
  static TrackletProjections TPROJ_L3L4C_L1PHI3;
  static TrackletProjections TPROJ_L3L4D_L1PHI3;
  static TrackletProjections TPROJ_L3L4E_L1PHI3;
  static TrackletProjections TPROJ_L3L4F_L1PHI3;
  static TrackletProjections TPROJ_D1L2B_L1PHI3;
  static TrackletProjections TPROJ_L3L4_L1PHI3FromPlus;

  static AllProjections AP_L3L4_L1PHI3;

  static VMProjections VMPROJ_L3L4_L1PHI9;
  static VMProjections VMPROJ_L3L4_L1PHI10;
  static VMProjections VMPROJ_L3L4_L1PHI11;
  static VMProjections VMPROJ_L3L4_L1PHI12;

  // Fill memories from input stream
  static Streamer instreamer1, instreamer2, instreamer3, instreamer4;
  static Streamer instreamer5, instreamer6;

  instreamer1.stream2mem(bx_in, input_stream1, TPROJ_L3L4C_L1PHI3);
  instreamer2.stream2mem(bx_in, input_stream2, TPROJ_L3L4D_L1PHI3);
  instreamer3.stream2mem(bx_in, input_stream3, TPROJ_L3L4E_L1PHI3);
  instreamer4.stream2mem(bx_in, input_stream4, TPROJ_L3L4F_L1PHI3);
  instreamer5.stream2mem(bx_in, input_stream5, TPROJ_D1L2B_L1PHI3);
  instreamer6.stream2mem(bx_in, input_stream6, TPROJ_L3L4_L1PHI3FromPlus);

  /////////////////////////////////////
  // Processing module
  static ProjectionRouter PR_L3L4_L1PHI3;

  PR_L3L4_L1PHI3.process(bx_in,
		  &TPROJ_L3L4C_L1PHI3, &TPROJ_L3L4D_L1PHI3, &TPROJ_L3L4E_L1PHI3, &TPROJ_L3L4F_L1PHI3,
		  &TPROJ_D1L2B_L1PHI3, &TPROJ_L3L4_L1PHI3FromPlus, 0, 0,
		  bx_out, &AP_L3L4_L1PHI3,
		  &VMPROJ_L3L4_L1PHI9, &VMPROJ_L3L4_L1PHI10,
		  &VMPROJ_L3L4_L1PHI11, &VMPROJ_L3L4_L1PHI12
		  );

  /////////////////////////////////////
  
  // Stream out memories
  static Streamer outstreamer_allproj;
  static Streamer outstreamer_vmproj1, outstreamer_vmproj2;
  static Streamer outstreamer_vmproj3, outstreamer_vmproj4;

  outstreamer_allproj.mem2stream(bx_out, AP_L3L4_L1PHI3, output_stream);
  
  outstreamer_vmproj1.mem2stream(bx_out, VMPROJ_L3L4_L1PHI9, output2_stream1);
  outstreamer_vmproj2.mem2stream(bx_out, VMPROJ_L3L4_L1PHI10, output2_stream2);
  outstreamer_vmproj3.mem2stream(bx_out, VMPROJ_L3L4_L1PHI11, output2_stream3);
  outstreamer_vmproj4.mem2stream(bx_out, VMPROJ_L3L4_L1PHI12, output2_stream4);
}
