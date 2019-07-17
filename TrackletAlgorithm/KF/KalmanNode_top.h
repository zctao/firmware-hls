#ifndef __KalmanNode_top__
#define __KalmanNode_top__

/**
 * This is the top-level function for Vivado HLS compilation. 
 * It is not used by CMSSW.
 * 
 * It is required because HLS does not allow the top-level function to be templated.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFdataTypes.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KalmanNode.h"
#else
#include "KFdataTypes.h"
#include "KalmanNode.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

void kalmanNode_top(const LinkWord& linkIn, LinkWord (&linkOut)[2]);

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
