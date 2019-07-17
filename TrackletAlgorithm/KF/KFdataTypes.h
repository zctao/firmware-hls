#ifndef __KFdataTypes__
#define __KFdataTypes__

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFpragmaOpts.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFconstants.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/HLSutilities.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstate.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstub.h"
#else
#include "KFpragmaOpts.h"
#include "KFconstants.h"
#include "HLSutilities.h"
#include "KFstate.h"
#include "KFstub.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

// Opto-link data format (from "lword" in emp_data_types.vhd).

class LinkWord {
public:

  template <unsigned int N, class T> 
  void getData(const int& LSB, T&& valueOut) const {valueOut = data.range(LSB + N - 1, LSB);}

  template <unsigned int N, class T> 
  void setData(const int& LSB, const T& valueIn) {data.range(LSB + N - 1, LSB) = valueIn;}

public:
  enum {BDATA=64};
  AP_UINT(BDATA) data;
  AP_UINT(1)     valid;
  AP_UINT(1)     start;
  AP_UINT(1)     strobe;
};

// Association of a helix state with a stub.

struct AssocKFstate {
  KFstate<4> kfState;
  KFstubR    kfStub;
};

#ifdef CMSSW_GIT_HASH
}
}
#endif

#endif
