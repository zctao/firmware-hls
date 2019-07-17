#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/InputLinkFormatter.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFconstants.h"
#else
#include "InputLinkFormatter.h"
#include "KFconstants.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

using namespace KFstubN;

//=== Initialize

InputLinkFormatter::InputLinkFormatter() : lastLinkValid_(false), eventID_(0), trackID_(0), stubID_(), nStubs_(0) {}


//=== Convert link data to stub.

void InputLinkFormatter::run(const LinkWord& linkIn, KFstub& stubOut) {

  const KFstub nullStub; 

  KFstub        thisStub; 

  // Do we have a valid stub?
  thisStub.coord.valid = false;
  if (linkIn.valid) {
    if (trackID_ < KFstubN::NTRK) { // If too many tracks, ignore excess.
      linkIn.getData<1>(BC + BM + BLAY + BZ + BSEC1 + BR1 + BPHI, thisStub.coord.valid);
    }
  }

  if (thisStub.coord.valid) {

    // Taken from Stubs.vhd function LinkToStub()
    // Documented in https://gitlab.cern.ch/cms-uk-tracktrigger/firmware/l1tf/blob/master/global_formats.docx .

    TR1 rT = 0;
    TSEC1 rawSectID = 0;
    TLAY rawLayerID = 0;
    linkIn.getData<BPHI>(                                    0, thisStub.coord.phiS.range());
    linkIn.getData<BR1>(                                  BPHI, rT.range());
    linkIn.getData<BSEC1>(                          BR1 + BPHI, rawSectID);
    linkIn.getData<BZ>(                     BSEC1 + BR1 + BPHI, thisStub.coord.z.range());
    linkIn.getData<BLAY>(              BZ + BSEC1 + BR1 + BPHI, rawLayerID);
    linkIn.getData<BM>(         BLAY + BZ + BSEC1 + BR1 + BPHI, thisStub.mBin_ht);
    linkIn.getData<BC>(    BM + BLAY + BZ + BSEC1 + BR1 + BPHI, thisStub.cBin_ht);

    thisStub.coord.r = chosenRofPhi + rT;

    if (rawSectID < EtaBoundaries::nSec) {
      thisStub.etaSectZsign = 1;   // -ve z.
      thisStub.etaSectID = EtaBoundaries::nSec - 1 - rawSectID; // Increases as go away from tanL = 0.
    } else {
      thisStub.etaSectZsign = 0;
      thisStub.etaSectID = rawSectID - EtaBoundaries::nSec;
    }

#ifdef CMSSW_GIT_HASH
    TZ absZ = fabs(float(thisStub.coord.z));
#else 
    TZ absZ = hls::abs(thisStub.coord.z);
#endif
    AP_UINT(1) endcap = (absZ > zBarrel);

    // Transform the Layer ID from GP to Kalman
    //
    // GP layer: 1 = b1; 2 = b2; 3 = b6 or e1; 4 = b5 or e2; 5 = b4 or e3; 6 = e4; 7 = b3 or e5. 
    // 
    // ("b3" indicates GP encoded layer ID = 3 in barrel etc).
    // ------------------------------------------------------------------------------------------
    // GP_eta- GP_eta+  bound 1  bound 2  KF layer 0    1    2    3    4    5    6   KF_eta
    // ------------------------------------------------------------------------------------------
    //    8       9       0.00     0.31            b1   b2   b7   b5   b4   b3    -     0
    //    7      10       0.31     0.61            b1   b2   b7   b5   b4   b3    -     1
    //    6      11       0.61     0.89            b1   b2   b7   b5   b4   b3    -     2
    // ------------------------------------------------------------------------------------------
    //    5      12       0.89     1.16            b1   b2   b7   b5   b4   b3   e4     3
    // ------------------------------------------------------------------------------------------
    //    4      13       1.16     1.43            b1   b2   b7  b5/e3  e4  e5   e6     4
    // ------------------------------------------------------------------------------------------
    //    3      14       1.43     1.70            b1   b2  b7/e3 e4   e5   e6   e7     5
    // ------------------------------------------------------------------------------------------
    //    2      15       1.70     1.95            b1   b2   e3   e4   e5   e6   e7     6
    // ------------------------------------------------------------------------------------------
    //    1      16       1.95     2.16            b1   e3   e4   e5   e6   e7          7
    //    0      17       2.16     2.40            b1   e3   e4   e5   e6   e7          8
    // ------------------------------------------------------------------------------------------

    // Taken from LinkFormatter.vhd

    switch (thisStub.etaSectID) {   // This is KF_eta 
    case 0:
    case 1:
    case 2:
      switch (rawLayerID) {
      case 1:  thisStub.addr.layerID = 0; break; 
      case 2:  thisStub.addr.layerID = 1; break;
      case 7:  thisStub.addr.layerID = 2; break;
      case 5:  thisStub.addr.layerID = 3; break;
      case 4:  thisStub.addr.layerID = 4; break;
      case 3:  thisStub.addr.layerID = 5; break;
      default: thisStub.addr.layerID = 7; break;
      }
      break;
    case 3:
      switch (rawLayerID) {
      case 1:  thisStub.addr.layerID = 0; break; 
      case 2:  thisStub.addr.layerID = 1; break;
      case 7:  thisStub.addr.layerID = 2; break;
      case 5:  thisStub.addr.layerID = 3; break;
      case 4:  thisStub.addr.layerID = endcap  ?  5  :  4;  break;
      case 3:  thisStub.addr.layerID = 5; break;
      default: thisStub.addr.layerID = 7; break;
      }
      break;
    case 4:
      switch (rawLayerID) {
      case 1:  thisStub.addr.layerID = 0; break; 
      case 2:  thisStub.addr.layerID = 1; break;
      case 7:  thisStub.addr.layerID = 2; break;
      case 5:  thisStub.addr.layerID = endcap  ?  5  :  3;  break;
      case 4:  thisStub.addr.layerID = 4; break;
      case 3:  thisStub.addr.layerID = 3; break;
      case 6:  thisStub.addr.layerID = 6; break;
      default: thisStub.addr.layerID = 7; break;
      }
      break;
    case 5:
      switch (rawLayerID) {
      case 1:  thisStub.addr.layerID = 0; break; 
      case 2:  thisStub.addr.layerID = 1; break;
      case 7:  thisStub.addr.layerID = endcap  ?  6  :  2;  break;
      case 3:  thisStub.addr.layerID = 2; break;
      case 4:  thisStub.addr.layerID = 3; break;
      case 5:  thisStub.addr.layerID = 4; break;
      case 6:  thisStub.addr.layerID = 5; break;
      default: thisStub.addr.layerID = 7; break;
      }
      break;
    case 6:
      switch (rawLayerID) {
      case 1:  thisStub.addr.layerID = 0; break; 
      case 2:  thisStub.addr.layerID = 1; break;
      case 3:  thisStub.addr.layerID = 2; break;
      case 4:  thisStub.addr.layerID = 3; break;
      case 5:  thisStub.addr.layerID = 4; break;
      case 6:  thisStub.addr.layerID = 5; break;
      case 7:  thisStub.addr.layerID = 5; break;
      default: thisStub.addr.layerID = 7; break;
      }
      break;
    case 7:
      switch (rawLayerID) {
      case 1:  thisStub.addr.layerID = 0; break; 
      case 3:  thisStub.addr.layerID = 1; break;
      case 4:  thisStub.addr.layerID = 2; break;
      case 5:  thisStub.addr.layerID = 3; break;
      case 6:  thisStub.addr.layerID = 4; break;
      case 7:  thisStub.addr.layerID = 5; break;
      default: thisStub.addr.layerID = 7; break;
      }
      break;
    default:
      thisStub.addr.layerID = 7;
    }

    if (thisStub.addr.layerID == 7) {
#ifndef __SYNTHESIS__
      std::cout<<"WARNING: LinkFormatter found stub with illegal LayerID for the given eta sector. (OK if affects <0.1% of stubs). -- endcap="<<endcap<<" sector="<<thisStub.etaSectID<<" layer="<<rawLayerID<<std::endl;
#endif
      thisStub.addr.layerID = 6; // Very rare occurance: just set any allowed value.
    }

  } else {

    thisStub = nullStub; // null
  }

  lastStub_.finalStubInTrk = lastStub_.coord.valid && not ( thisStub.coord.valid  && (thisStub.etaSectID == lastStub_.etaSectID) && (thisStub.etaSectZsign == lastStub_.etaSectZsign) && (thisStub.mBin_ht == lastStub_.mBin_ht) && (thisStub.cBin_ht == lastStub_.cBin_ht));

  if (lastStub_.coord.valid) {
    // Store counters
    lastStub_.addr.eventID = eventID_;
    lastStub_.addr.trackID = trackID_;
    lastStub_.addr.stubID = stubID_[ lastStub_.addr.layerID ];
  }

  if (not linkIn.valid and lastLinkValid_) { // End of last event
    eventID_ = (eventID_ + 1)%KFstubN::NEV; // increment counter
    trackID_ = 0;
    for (AP_UINT(1+BLAY) i = 0; i < NLAY; i++) stubID_[i] = 0;
    nStubs_ = 0;
  } else  if (lastStub_.finalStubInTrk) {
    trackID_++;  // set counters for new track.
    for (AP_UINT(BLAY+1) i = 0; i < NLAY; i++) stubID_[i] = 0;
    nStubs_ = 0;
  } else if (lastStub_.coord.valid) {
    if (stubID_[ lastStub_.addr.layerID ] < maxStubsPerLayPerTrack) {
      stubID_[ lastStub_.addr.layerID ]++; // increment #stub in layer counter. If reaches maxStubsPerLayPerTrack, stub will be rejected by SSA.
    }
    nStubs_++;
  }

  if (nStubs_ <= maxStubsPerTrack) {
    if (nStubs_ == maxStubsPerTrack) lastStub_.finalStubInTrk = true;
    stubOut = lastStub_;
  } else {
    stubOut = nullStub;
  }

  lastStub_ = thisStub;

#ifndef __SYNTHESIS__
  stubOut.print("InputLinkFormatter Stub:");
#endif

  // Store link valid flag data from previous call to this function
  lastLinkValid_ = linkIn.valid;
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
