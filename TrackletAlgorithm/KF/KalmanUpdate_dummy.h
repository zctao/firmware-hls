#ifndef __KalmanUpdate_dummy__
#define __KalmanUpdate_dummy__

/**
 * Dummy Kalman Update routine to add stub to helix.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstub.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstate.h"
#else
#include "KFstub.h"
#include "KFstate.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class KalmanUpdate_dummy {

public:

void run(const KFstubC& stub, const KFstate<4>& stateIn, KFstate<4>& stateOut, KFcuts<4>& cutsOut);

};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
