#ifndef __OutputLinkFormatter__
#define __OutputLinkFormatter__

/**
 * Pack fitted tracks to output opto-link data.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFdataTypes.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstate.h"
#else
#include "KFdataTypes.h"
#include "KFstate.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class OutputLinkFormatter {
 public:

  // Initialize
  OutputLinkFormatter() {}

  // Convert fitted track to output link data.
  void run(const KFstate<4>& stateIn, LinkWord (&linkOut)[2]);
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
