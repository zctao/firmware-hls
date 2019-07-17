#ifndef __StubsRams__
#define __StubsRams__

/**
 * Associate stubs with states.
 * 
 * Author: Ian Tomalin
 */

#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstub.h"
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFconstants.h"
#else
#include "KFstub.h"
#include "KFconstants.h"
#endif

#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

class StubRams {

public:

  enum {BSTUBS=8, NSTUBS=(1<<BSTUBS), // Allows up to 18TM*(320MHz/40MHz) = 144 stubs/event.
	BADDR=KFstubN::BTRK+KFstubN::BLAY+KFstubN::BID, NADDR=(1<<BADDR)};

  typedef AP_UINT(BSTUBS) TSTUBS;

  // Initialise

  StubRams() : ramStubAddr_(), addrWrite_() { // Initialize to zero
    // Dual-port RAM.
#pragma HLS RESOURCE  variable=ramStub_     core=RAM_S2P_BRAM
#pragma HLS RESOURCE  variable=ramStubAddr_ core=RAM_S2P_BRAM
    // Pack KFstub data members into single bit word, to prevent each being stored in separate RAM.
#pragma HLS DATA_PACK variable=ramStub_     instance=stubPack
  }

  void reset(const KFstubN::TEV& iEvent) {addrWrite_[ iEvent ] = 0;}

  // Simultaneous write & read

  void writeRead(const AP_UINT(1)& WE, const KFstub& writeStub,
   	         const AP_UINT(1)& RE, const KFstubA& readAddr, KFstubR& readStub);

private:

  // RAM: for given stub address (event ID, track ID, layer ID, stub ID) stores location of stub
  // in stubRam,
  TSTUBS ramStubAddr_[NADDR];

  // RAM: Stores stubs.
  KFstubR ramStub_[NSTUBS * numAccEvents];

  // Next write address to ramStub_ for each event;
  TSTUBS addrWrite_[numAccEvents];
};

#ifdef CMSSW_GIT_HASH
}

}
#endif

#endif
