/**
 * This is the top-level function for Vivado HLS compilation. 
 * It is not used by CMSSW.
 * 
 * It is required because HLS does not allow the top-level function to be templated.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KalmanNode_top.h"
#else
#include "KalmanNode_top.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

void kalmanNode_top(const LinkWord& linkIn, LinkWord (&linkOut)[2]) {

#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_hs register port=return
#pragma HLS INTERFACE ap_none port=linkIn register 
#pragma HLS INTERFACE ap_none port=linkOut register 

  static KalmanNode kalmanNode;
  kalmanNode.run(linkIn, linkOut);
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
