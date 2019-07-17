#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/OutputLinkFormatter.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFconstants.h"
#else
#include "OutputLinkFormatter.h"
#include "KFconstants.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

using namespace KFstateN;

//=== Convert fitted track to output link data.

void OutputLinkFormatter::run(const KFstate<4>& stateIn, LinkWord (&linkOut)[2]) {

#ifndef __SYNTHESIS__
  stateIn.print("OutputLinkFormatter state: ");
#endif

  AP_UINT(2*LinkWord::BDATA) linkPair = 0;

  static const AP_UINT(1) bit0 = 0;

  // IRT
  KFcuts<4> dummy; dummy.consistent = 0; dummy.cBin_fit = 0; dummy.mBin_fit = 0;
  TSEC1 htEtaSectID;
  if (stateIn.etaSectZsign) {
    htEtaSectID = EtaBoundaries::nSec - 1 - stateIn.etaSectID;
  } else {
    htEtaSectID = EtaBoundaries::nSec + stateIn.etaSectID;
  }

  // Concatenate bits. -- Can accept int & uint, but bits must be first extracted from ap_fixed.
  // range() function without arguments only available for ap_fixed -- returns all bits in number.
  
  linkPair = 
    (stateIn.valid,
     bit0,
     dummy.consistent,
     dummy.cBin_fit,
     dummy.mBin_fit,
     htEtaSectID,
     stateIn.eventID,
     stateIn.layerID,
     stateIn.cBin_ht,
     stateIn.mBin_ht,
     stateIn.chiSquared.range(),
     stateIn.z0.range(),
     stateIn.tanL.range(),
     stateIn.phi0.range(),
     stateIn.inv2R.range());

  /*
  linkPair.setData<B18> (                   0, stateIn.inv2R.range());
  linkPair.setData<B18> (                 B18, stateIn.phi0.range());
  linkPair.setData<B18> (               2*B18, stateIn.tanL.range());
  linkPair.setData<B18> (               3*B18, stateIn.z0.range());
  linkPair.setData<B17> (               4*B18, stateIn.chiSquared.range());
  linkPair.setData<BM>  (           B17+4*B18, stateIn.mBin_ht);
  linkPair.setData<BC>  (        BM+B17+4*B18, stateIn.cBin_ht);
  linkPair.setData<BLAY>(     BC+BM+B17+4*B18, stateIn.layerID); // Check
  linkPair.setData<BEV> (BLAY+BC+BM+B17+4*B18, stateIn.eventID); // Why output this?
  // + other variables.
  */

  linkOut[0].data = linkPair.range(    LinkWord::BDATA - 1,               0);
  linkOut[1].data = linkPair.range(2 * LinkWord::BDATA - 1, LinkWord::BDATA);

  linkOut[0].valid = true;
  linkOut[1].valid = true;
  linkOut[0].start = false;
  linkOut[1].start = false;
  linkOut[0].strobe = false;
  linkOut[1].strobe = false;
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
