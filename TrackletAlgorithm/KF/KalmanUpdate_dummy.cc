/**
 * Dummy Kalman Update routine to add stub to helix.
 * 
 * Author: Ian Tomalin
 */


#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KalmanUpdate_dummy.h"
#else
#include "KalmanUpdate_dummy.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

void KalmanUpdate_dummy::run(const KFstubC& stub, const KFstate<4>& stateIn, KFstate<4>& stateOut, KFcuts<4>& cutsOut) {
  stateOut = stateIn;
  if (stub.r + stub.z == 0) stateOut.eventID = 3; // IRT play to make output dependent on input stub.
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
