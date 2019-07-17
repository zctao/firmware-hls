#ifndef __StateStubAssociator__
#define __StateStubAssociator__

/**
 * Associate stubs with states.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFdataTypes.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstub.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstate.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/StubRams.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstateRams.h"
#else
#include "KFdataTypes.h"
#include "KFstub.h"
#include "KFstate.h"
#include "StubRams.h"
#include "KFstateRams.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class StateStubAssociator {
public:

  // Initialize
  StateStubAssociator() : numStubsReg_(0), numStubsReg2_(0), stubID_(0) {}

  // Associate stubs with states.
  void run(const KFstub& stubIn, const KFstate<4> (& stateIn)[2], 
	   AssocKFstate& assocStubStateOut);

private:

  // RAMs
  StubRams    stubRams_;
  KFstateRams stateRams_;

  // Other stuff
  KFstate<4>    stateOutReg_, stateOutReg2_, stateOutReg3_;
  KFstateN::TID numStubsReg_, numStubsReg2_;
  KFstateN::TID stubID_;
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
