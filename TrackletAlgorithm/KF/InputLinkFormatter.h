#ifndef __InputLinkFormatter__
#define __InputLinkFormatter__

/**
 * Unpack input opto-link data into stubs.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFdataTypes.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstub.h"
#else
#include "KFdataTypes.h"
#include "KFstub.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class InputLinkFormatter {
public:

  // Initialize.
  InputLinkFormatter();

  // Convert link data to stub.
  void run(const LinkWord& linkIn, KFstub& stubOut);

private:

  AP_UINT(1) lastLinkValid_;
  KFstubN::TEV  eventID_;
  KFstubN::TTRK trackID_;  
  KFstubN::TID stubID_[KFstubN::NLAY];
  AP_UINT(8) nStubs_;
  KFstub lastStub_; 
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
