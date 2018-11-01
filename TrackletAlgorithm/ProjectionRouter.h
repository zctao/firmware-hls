#ifndef PROJECTIONROUTER_H
#define PROJECTIONROUTER_H

#include "Constants.hh"
#include "TrackletProjections.hh"
#include "AllProjections.hh"
#include "VMProjections.hh"

#include <assert.h>

//template<unsigned int nINMEM>
void ProjectionRouter(ap_uint<3>,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  TrackletProjectionMemory *const,
					  ap_uint<3>&,
					  AllProjectionMemory *const,
					  VMProjectionMemory *const,
					  VMProjectionMemory *const,
					  VMProjectionMemory *const,
					  VMProjectionMemory *const);

template<int nbits_nMEM, int nbits_MemAddr>
bool get_mem_read_addr(ap_uint<nbits_nMEM>& imem, ap_uint<nbits_MemAddr>& addr,
					   ap_uint<(1<<nbits_nMEM)>& mem_hasdata, ap_uint<nbits_MemAddr>* numbersin)
{
  if (mem_hasdata == 0) return false;
  
  // priority encoder
  imem = __builtin_ctz(mem_hasdata);
  ++addr;
	  
  if (addr >= *(numbersin+imem)) {  // All entries have been read out in memory[imem]
	// Prepare to read the next non-empty memory
	addr = 0;  // reset read address
	mem_hasdata -= (1<<imem);  // flip the lowest 1 bit to 0
  }
  
  return true;
}

#endif

