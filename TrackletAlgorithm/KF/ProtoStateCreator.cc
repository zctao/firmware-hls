#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/ProtoStateCreator.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/InputLinkFormatter.h"
#else
#include "ProtoStateCreator.h"
#include "InputLinkFormatter.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

//=== Initialize

ProtoStateCreator::ProtoStateCreator() :
  // Protostate covariance matrix, copied from KFParamsComb::seedP().
  c00_( pow(0.0157 * invPtToInv2R * 2 * inv2R_Mult, 2) ),
  c11_( pow(0.0051 * 2 * phiMult, 2) ),
  c22_( pow(0.25 * 2, 2) ),
  c33_( pow(5 * rMult, 2) ),
  // Counters & flags
  hitPattern_(0),
  numStubsPerLay_(),
  numLayers_(0),
  lastFinalStubInTrk_(true)
{}

//=== Convert stubs from HT to initial estimate of track helix params.

void ProtoStateCreator::run(const KFstub& stubIn, KFstate<4>& protoState) {

  static const KFstate<4> nullState;

  enum {BC=KFstateN::BC, BM=KFstateN::BM};

  static const EtaBoundaries etaBounds;

  protoState = nullState;

  if (stubIn.coord.valid) {

    AP_UINT(1) newTrack = lastFinalStubInTrk_; // If last stub was last one on a track, this is 1st stub on new track.

    if (newTrack) {
      hitPattern_ = 0;
      for (AP_UINT(1+KFstateN::BLAY) i = 0; i < KFstateN::NLAY; i++) numStubsPerLay_[i] = 0;
      numLayers_ = 0;
    }      

    if (hitPattern_[ stubIn.addr.layerID ] == 0) {
      hitPattern_[ stubIn.addr.layerID ] = 1;
      numLayers_++; 
    }
    numStubsPerLay_[ stubIn.addr.layerID ]++;

    if (stubIn.finalStubInTrk) {

      if (numLayers_ >= minStubsPerFitTrack) {

	//--- We have a proto-state. Store it.

	protoState.valid = true;
	protoState.hitPattern = 0;
	protoState.eventID = stubIn.addr.eventID;
	protoState.trackID = stubIn.addr.trackID;
	protoState.layerID = 0;
	protoState.etaSectID = stubIn.etaSectID;
	protoState.etaSectZsign = stubIn.etaSectZsign;
	protoState.mBin_ht = stubIn.mBin_ht;
	protoState.cBin_ht = stubIn.cBin_ht;

	// Go to centre of HT (m,c) bin by adding extra '1' bit.
	static const AP_UINT(1) bit1 = 1;
	AP_FIXED(BC+1, BC) cBinEx;
	AP_FIXED(BM+1, BM) mBinEx;  
	cBinEx.range() = (stubIn.cBin_ht, bit1);
	mBinEx.range() = (stubIn.mBin_ht, bit1);

	AP_FIXED(BC+1, BC + phiToCbin_bitShift) phiT = AP_FIXED(BC+1 + phiToCbin_bitShift, BC + phiToCbin_bitShift)(cBinEx) << phiToCbin_bitShift;
	AP_FIXED(BM+1, BM - inv2RToMbin_bitShift) inv2R = AP_FIXED(BM+1 + inv2RToMbin_bitShift, BM)(mBinEx) >> inv2RToMbin_bitShift;

	protoState.inv2R = inv2R;
	protoState.phi0 = phiT + chosenRofPhi * inv2R;
	KFstateN::TT absTanL = etaBounds.tanL_[stubIn.etaSectID]; 
	if (stubIn.etaSectZsign) {
	  protoState.tanL = -absTanL;
	} else {
	  protoState.tanL =  absTanL;
	} 
	protoState.z0 = 0.;

	protoState.cov_00 = c00_;
	protoState.cov_11 = c11_;
	protoState.cov_22 = c22_;
	protoState.cov_33 = c33_;
	for (AP_UINT(1+KFstateN::BLAY) i = 0; i < KFstateN::NLAY; i++) {
	  protoState.protoInfo.numStubsPerLay[i] = numStubsPerLay_[i];
	}
      }
    }
  }

  lastFinalStubInTrk_ = stubIn.finalStubInTrk;
}

#ifdef CMSSW_GIT_HASH
}

}
#endif
