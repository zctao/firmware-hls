#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/StateStubAssociator.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/InputLinkFormatter.h"
#else
#include "StateStubAssociator.h"
#include "InputLinkFormatter.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

//== Associate stubs with states.

void StateStubAssociator::run(const KFstub& stubIn, const KFstate<4> (& stateIn)[2], 
			      AssocKFstate& assocStubStateOut) {

  //--- State RAM access

  // Store incoming states in state-RAM & read a state from RAM if requested.
  AP_UINT(1) stateRamRE = (stubID_ == 0);  // Read a new state?
  const KFstateN::TEV eventID = 0;
  KFstate<4> stateOut;
  stateRams_.writeRead(stateIn, 
		       stateRamRE, eventID, stateOut);
  AP_UINT(1) seekStub;
  if (stateRamRE) {
    stateOutReg3_ = stateOutReg2_;
    KFstateN::TID numStubs = numStubsReg2_;
    stateOutReg2_ = stateOutReg_; // Fifo is failed attempt to solve pipelining issue.
    numStubsReg2_ = numStubsReg_;
    stateOutReg_ = stateOut;
    numStubsReg_ = stateOut.protoInfo.numStubsPerLay[stateOut.layerID];
    if (stateOutReg3_.valid && numStubs > 0) {
      seekStub = true;
      stubID_ = numStubs - 1;
    } else {
      seekStub = false;
      stubID_ = 0;
    }
  } else {
    seekStub = true;
    stubID_--;
  }

#ifndef __SYNTHESIS__
  std::cout<<"RATS "<<stateRamRE<<" "<<stateOutReg3_.valid<<" "<<seekStub<<std::endl;
#endif

  //--- Stub RAM access

  // Use state read from RAM to determine address in stub-RAM where desired associated stub can be found.  

  const AP_UINT(1)& stubRamRE = seekStub;
  KFstubA readAddr = KFstubA(stateOutReg3_.eventID, stateOutReg3_.trackID, stateOutReg3_.layerID, stubID_);

  // Store incoming stubs in stub-RAM too, if not too many per layer.
  AP_UINT(1) stubRamWE = (stubIn.addr.stubID < maxStubsPerLayPerTrack);

  KFstubR stubOut;
  stubRams_.writeRead(stubRamWE, stubIn, 
		      stubRamRE, readAddr, stubOut);

#ifndef __SYNTHESIS__
  stubIn.print("SSA: stored to STUB RAM");
  if (stubRamRE) std::cout<<"reading StubRam addr (lay,stub)=("<<readAddr.layerID<<" "<<readAddr.stubID<<")"<<std::endl;
  stubOut.print("SSA: read from STUB RAM");

  stateIn[0].print("Store to STATE RAM");
  //  if (found) std::cout<<"reading address "<<readAddr.layerID<<std::endl;
  stateOutReg3_.print("SSA: read from STATE RAM");
#endif

  // Create output.
  assocStubStateOut.kfState = stateOutReg3_;
  assocStubStateOut.kfStub  = stubOut;
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
