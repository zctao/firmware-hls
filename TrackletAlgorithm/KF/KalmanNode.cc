#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KalmanNode.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstub.h"
#else
#include "KalmanNode.h"
#include "KFstub.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

//=== Run KF algo

void KalmanNode::run(const LinkWord& linkIn, LinkWord (&linkOut)[2]) {

  KFstub stub;
  
  KFstate<4> protoState, finalState;
  KFstate<4> stateIn[2];
  AssocKFstate assocStubState;
  KFcuts<4>  stateCuts;

  // Unpack input link data into stub.
  inputLinkFormatter_.run(linkIn, stub);

  // Convert stubs from HT to initial estimate of helix state.
  protoStateCreator_.run(stub, protoState);

  // Associate stubs with states.
  stateIn[0] = protoState;
  stateIn[1] = updatedState_;
  stateStubAssociator_.run(stub, stateIn, assocStubState);

#ifndef __SYNTHESIS__
  assocStubState.kfStub.print("KalmanNode: ASSOC_STUB");
  assocStubState.kfState.print("KalmanNode: ASSOC_STATE");
#endif

  // Update helix params by constraining them with the stub using KF maths.
  //kalmanUpdate_dummy_.run(assocStubState.kfStub.coord, assocStubState.kfState, updatedState_, stateCuts);
  kalmanUpdate_dummy_.run(assocStubState.kfStub.coord, assocStubState.kfState, stateFifo_[0], stateCuts);

  // Without the following FIFO, HLS compiler can't pipeline with interval 1.
  // Reason is that in C++, the output of KalmanUpdate() is available on next call to KalmanNode::run(),
  // so is fed together with fresh input data into StateStubAssociator::run(). This means that if in FW,
  // latency of chain is N, no fresh input data is allowed for a pipline interval of N clocks.
  // The piepline length should roughly equal the latency of the updator.
  for (unsigned int i = lenFifo_-1; i > 0; i--) {
    stateFifo_[i] = stateFifo_[i-1]; 
  }

  updatedState_ = stateFifo_[lenFifo_-1];

  if (updatedState_.layerID < maxStubsPerFitTrack) {
    updatedState_.layerID++; // Prepare to add stubs from another layer to this state
  } else {
    finalState = updatedState_;
    static const KFstate<4> nullState;
    updatedState_ = nullState; // Done with this state.
  }

  // Pack selected fitted track into output link.
  outputLinkFormatter_.run(finalState, linkOut);
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
