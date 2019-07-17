#ifndef __KalmanNode__
#define __KalmanNode__

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
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstate.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/InputLinkFormatter.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/OutputLinkFormatter.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/ProtoStateCreator.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/StateStubAssociator.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KalmanUpdate_dummy.h"
#else
#include "KFdataTypes.h"
#include "KFstate.h"
#include "InputLinkFormatter.h"
#include "OutputLinkFormatter.h"
#include "ProtoStateCreator.h"
#include "StateStubAssociator.h"
#include "KalmanUpdate_dummy.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class KalmanNode {
public:

  // Initialize
  KalmanNode() {}

  // Run KF algo
  void run(const LinkWord& linkIn, LinkWord (&linkOut)[2]);

private:

  // Classes containing KF algorithm
  InputLinkFormatter  inputLinkFormatter_;
  OutputLinkFormatter outputLinkFormatter_;
  ProtoStateCreator   protoStateCreator_;
  StateStubAssociator stateStubAssociator_;
  KalmanUpdate_dummy  kalmanUpdate_dummy_;

  // Other stuff
  KFstate<4> updatedState_;
 
  static const unsigned int lenFifo_ = 9; // Increase this if KalmanNode doesn't pipeline or frequency.
  KFstate<4> stateFifo_[lenFifo_];
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
