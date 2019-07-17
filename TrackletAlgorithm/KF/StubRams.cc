#ifdef CMSSW_GIT_HASH
#include "L1Trigger/TrackFindingTMTT/interface/HLS/StubRams.h"
#else
#include "StubRams.h"
#endif
 
#ifdef CMSSW_GIT_HASH
namespace TMTT {

namespace KalmanHLS {
#endif

//=== Simultaneous write & read

void StubRams::writeRead(const AP_UINT(1)& WE, const KFstub& writeStub,
			 const AP_UINT(1)& RE, const KFstubA& readAddr, KFstubR& readStub) {

  // User guarantees not to read & write to same address in RAM in single clk cycle, to allow pipelining.
#pragma HLS DEPENDENCE variable=ramStub_     intra false
#pragma HLS DEPENDENCE variable=ramStubAddr_ intra false

  static const KFstub nullStub;

  //--- Read operation

  if (RE) {
    const TSTUBS  locAddrRamRead = (readAddr.trackID, readAddr.layerID, readAddr.stubID);

    const TSTUBS& locRamRead = ramStubAddr_[locAddrRamRead];

    readStub = ramStub_[ (readAddr.eventID, locRamRead) ];

#ifndef __SYNTHESIS__
    std::cout<<"StubRam::read: "<<std::dec<<(readAddr.eventID, locRamRead)<<" "<<locAddrRamRead<<" "<<readStub.coord.r<<" "<<ramStubAddr_[ locAddrRamRead ]<<std::endl;      
    assert(readStub.coord.valid);
#endif

  } else {

    readStub = nullStub;
    
  }

  //--- Write operation

  AP_UINT(1) ramFull = false;

#ifndef __SYNTHESIS__
  if (ramFull) std::cout<<"StubRam::WARNING -- Ram full"<<std::endl;
#endif


  if (WE && writeStub.coord.valid) {

    const KFstubA& writeAddr = writeStub.addr;
    TSTUBS& locRamWrite = addrWrite_[ writeAddr.eventID ];

    ramFull = (locRamWrite >= NSTUBS);

    if (not ramFull) { 

      TSTUBS locAddrRamWrite = (writeAddr.trackID, writeAddr.layerID, writeAddr.stubID);
      ramStubAddr_[ locAddrRamWrite ] = locRamWrite;

      ramStub_[ (writeAddr.eventID, locRamWrite) ] = KFstubR( writeStub );

#ifndef __SYNTHESIS__
      std::cout<<"StubRam::write: addr(Ram)="<<std::dec<<"("<<writeAddr.eventID<<","<<locRamWrite<<")"<<" addr(AddrRam)="<<locAddrRamWrite<<" r="<<KFstubR( writeStub ).coord.r<<std::endl;
#endif

      locRamWrite++; // Increment write address
    }
  }
} 

#ifdef CMSSW_GIT_HASH
}

}
#endif
