#ifndef __ProtoStateCreator__
#define __ProtoStateCreator__

/**
 * Create an initiql helix state from the HT output.
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

class ProtoStateCreator {
public:

  // Initialize
  ProtoStateCreator();

  // Convert stubs from HT to initial estimate of track helix params.
  void run(const KFstub& stubIn, KFstate<4>& protoState);

private:

  const KFstateN::TC00 c00_;
  const KFstateN::TC11 c11_;
  const KFstateN::TC22 c22_;
  const KFstateN::TC33 c33_;

  KFstateN::TNLAY hitPattern_;
  KFstateN::TID   numStubsPerLay_[KFstateN::NLAY];
  KFstateN::TLAY  numLayers_;


  AP_UINT(1) lastFinalStubInTrk_;
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
