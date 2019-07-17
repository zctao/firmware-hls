#ifndef __KFstateRams__
#define __KFstateRams__

/**
 * Associate stubs with states.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstate.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFconstants.h"
#else
#include "KFstate.h"
#include "KFconstants.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class KFstateRams {

public:

  enum {BSTATES0=4, NSTATES0=(1<<BSTATES0),  // Allows to buffer 16 proto-states per event
	BSTATES1=8, NSTATES1=(1<<BSTATES1)}; // Allows to buffer 256 updated states per event

  typedef AP_UINT(BSTATES0) TSTATES0;
  typedef AP_UINT(BSTATES1) TSTATES1;

  // Initialise

  KFstateRams() : addrWrite0_(), addrWrite1_(), addrRead0_(), addrRead1_() { // Initialize to zero
    // Dual-port RAM.
#pragma HLS RESOURCE  variable=ramState0_   core=RAM_S2P_LUTRAM
#pragma HLS RESOURCE  variable=ramState1_   core=RAM_S2P_BRAM
    // Pack KFstate data members into single bit word, to prevent each being stored in separate RAM.
#pragma HLS DATA_PACK variable=ramState0_   instance=statePack0
#pragma HLS DATA_PACK variable=ramState1_   instance=statePack1
  }

  void reset(const KFstateN::TEV& iEvent) {addrWrite0_[ iEvent ] = 0; addrWrite1_[ iEvent ] = 0;}

  // Simultaneous write & read

  void writeRead(const KFstate<4> (&writeState)[2], 
		 const AP_UINT(1)& RE, const KFstateN::TEV& readEvent, KFstate<4>& readState);

private:

  // RAMs: stores states.
  KFstate<4> ramState0_[NSTATES0 * numAccEvents];  // Proto-states
  KFstate<4> ramState1_[NSTATES1 * numAccEvents];  // Updated states

  // Next write address to ramState0/1_ for each event;
  TSTATES0 addrWrite0_[numAccEvents];
  TSTATES1 addrWrite1_[numAccEvents];
  // Current read address to ramState0/1_ for each event;
  TSTATES0 addrRead0_[numAccEvents];
  TSTATES1 addrRead1_[numAccEvents];
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
