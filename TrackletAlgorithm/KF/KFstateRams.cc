#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/KFstateRams.h"
#else
#include "KFstateRams.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

//=== Simultaneous write & read

void KFstateRams::writeRead(const KFstate<4> (&writeState)[2], 
			    const AP_UINT(1)& RE, const KFstateN::TEV& readEvent, KFstate<4>& readState) {

  // User guarantees not to read & write to same address in RAM in single clk cycle, to allow pipelining.
#pragma HLS DEPENDENCE variable=ramState0_ intra false
#pragma HLS DEPENDENCE variable=ramState1_ intra false

  static const KFstate<4> nullState;

  TSTATES0 locRamRead0_readEvent  = addrRead0_[ readEvent ];
  TSTATES1 locRamRead1_readEvent  = addrRead1_[ readEvent ];
  TSTATES0 locRamWrite0_readEvent = addrWrite0_[ readEvent ];
  TSTATES1 locRamWrite1_readEvent = addrWrite1_[ readEvent ];

  KFstateN::TEV writeEvent[2];
  writeEvent[0] = writeState[0].eventID;
  writeEvent[1] = writeState[1].eventID;

  TSTATES0 locRamRead0_writeEvent  = addrRead0_[ writeEvent[0] ];
  TSTATES1 locRamRead1_writeEvent  = addrRead1_[ writeEvent[1] ];
  TSTATES0 locRamWrite0_writeEvent = addrWrite0_[ writeEvent[0] ];
  TSTATES1 locRamWrite1_writeEvent = addrWrite1_[ writeEvent[1] ];

  //--- Read operation

  if (RE) {

    AP_UINT(1) canReadRam[2]; // Is unread data is present in RAM?
    canReadRam[0] = (locRamRead0_readEvent != locRamWrite0_readEvent);
    canReadRam[1] = (locRamRead1_readEvent != locRamWrite1_readEvent);

    if (canReadRam[0]) {      

      readState = ramState0_[ (readEvent, locRamRead0_readEvent) ];

#ifndef __SYNTHESIS__
      std::cout<<"KFstateRam::read0: addr="<<std::dec<<(readEvent, locRamRead0_readEvent)<<" valid="<<readState.valid<<" phi0="<<readState.phi0<<std::endl;      
      assert(readState.valid);
#endif
      addrRead0_[ readEvent ] = locRamRead0_readEvent + 1;  // Increment read address

    } else if (canReadRam[1]) {

      readState = ramState1_[ (readEvent, locRamRead1_readEvent) ];

#ifndef __SYNTHESIS__
      std::cout<<"KFstateRam::read1: addr="<<std::dec<<(readEvent, locRamRead1_readEvent)<<" valid="<<readState.valid<<" phi0="<<readState.phi0<<std::endl;      
      assert(readState.valid);
#endif
      addrRead1_[ readEvent ] = locRamRead1_readEvent + 1;  // Increment read address 

    } else {

      readState = nullState;
    }

  } else {

    readState = nullState;

  }

  //--- Write operation

  TSTATES0 nextRamWrite0_writeEvent = locRamWrite0_writeEvent + 1;
  TSTATES1 nextRamWrite1_writeEvent = locRamWrite1_writeEvent + 1;

  AP_UINT(1) ramNotFull[2];
  ramNotFull[0] = (locRamRead0_writeEvent != nextRamWrite0_writeEvent);
  ramNotFull[1] = (locRamRead1_writeEvent != nextRamWrite1_writeEvent);


#ifndef __SYNTHESIS__
  if (not ramNotFull[0]) std::cout<<"KFstateRam:WARNING -- RAM_0 full"<<std::endl;
  if (not ramNotFull[1]) std::cout<<"KFstateRam:WARNING -- RAM_1 full"<<std::endl;
#endif

  if (ramNotFull[0] && writeState[0].valid) {

    ramState0_[ (writeState[0].eventID, locRamWrite0_writeEvent) ] = writeState[0];

#ifndef __SYNTHESIS__
    std::cout<<"KFstateRam:write0: addr="<<std::dec<<(writeState[0].eventID, locRamWrite0_writeEvent)<<" phi0="<<writeState[0].phi0<<std::endl;
#endif

    addrWrite0_[ writeEvent[0] ] = nextRamWrite0_writeEvent; // Increment write address.
  }

  if (ramNotFull[1] && writeState[1].valid) {

    ramState1_[ (writeState[1].eventID, locRamWrite1_writeEvent) ] = writeState[1];

#ifndef __SYNTHESIS__
    std::cout<<"KFstateRam:write1: addr="<<std::dec<<(writeState[1].eventID, locRamWrite1_writeEvent)<<" phi0="<<writeState[1].phi0<<std::endl;
#endif

    addrWrite1_[ writeEvent[1] ] = nextRamWrite1_writeEvent; // Increment write address.
  }
} 

#ifdef CMSSW_GIT_HASH
}

}
#endif
