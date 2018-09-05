#include "TrackletProcessing.h"

void TrackletProcessing
(// inputs
 ap_uint<3> bx_in,
 hls::stream<TProj>* (&input_streams)[6],
 // outputs
 ap_uint<3> bx_out,
 hls::stream<AllProj>* output_stream,
 hls::stream<VMProj>* (&output2_streams)[4])
{
#pragma HLS ARRAY_PARTITION variable=input_streams complete
#pragma HLS ARRAY_PARTITION variable=output2_streams complete
  
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

  instreamer1.stream2mem(bx_in, *(input_streams[0]), TPROJ_L3L4C_L1PHI3);
  instreamer2.stream2mem(bx_in, *(input_streams[1]), TPROJ_L3L4D_L1PHI3);
  instreamer3.stream2mem(bx_in, *(input_streams[2]), TPROJ_L3L4E_L1PHI3);
  instreamer4.stream2mem(bx_in, *(input_streams[3]), TPROJ_L3L4F_L1PHI3);
  instreamer5.stream2mem(bx_in, *(input_streams[4]), TPROJ_D1L2B_L1PHI3);
  instreamer6.stream2mem(bx_in, *(input_streams[5]), TPROJ_L3L4_L1PHI3FromPlus);

  /////////////////////////////////////
  // Processing module
  static ProjectionRouter PR_L3L4_L1PHI3;

  TrackletProjections* tprojs_pr_l3l4_l1phi3[8] = {
    &TPROJ_L3L4C_L1PHI3, &TPROJ_L3L4D_L1PHI3, &TPROJ_L3L4E_L1PHI3,
    &TPROJ_L3L4F_L1PHI3, &TPROJ_D1L2B_L1PHI3, &TPROJ_L3L4_L1PHI3FromPlus,
    0, 0
  };

  AllProjections* allproj_pr_l3l4_l1phi3 = &AP_L3L4_L1PHI3;

  VMProjections* vmprojs_pr_l3l4_l1phi3[4] = {
    &VMPROJ_L3L4_L1PHI9, &VMPROJ_L3L4_L1PHI10,
    &VMPROJ_L3L4_L1PHI11, &VMPROJ_L3L4_L1PHI12
  };
  
  PR_L3L4_L1PHI3.process(bx_in, tprojs_pr_l3l4_l1phi3,
                         allproj_pr_l3l4_l1phi3, vmprojs_pr_l3l4_l1phi3);

  /////////////////////////////////////
  
  // Stream out memories
  static Streamer outstreamer_allproj;
  outstreamer_allproj.mem2stream(bx_out, AP_L3L4_L1PHI3, *output_stream);

  static Streamer outstreamer_vmproj1, outstreamer_vmproj2;
  static Streamer outstreamer_vmproj3, outstreamer_vmproj4;
  outstreamer_vmproj1.mem2stream(bx_out, VMPROJ_L3L4_L1PHI9, *(output2_streams[0]));
  outstreamer_vmproj2.mem2stream(bx_out, VMPROJ_L3L4_L1PHI10, *(output2_streams[1]));
  outstreamer_vmproj3.mem2stream(bx_out, VMPROJ_L3L4_L1PHI11, *(output2_streams[2]));
  outstreamer_vmproj4.mem2stream(bx_out, VMPROJ_L3L4_L1PHI12, *(output2_streams[3]));
  
}
