#ifndef STREAMER_HH
#define STREAMER_HH

#include <assert.h>

#include "hls_stream.h"
#include "Constants.hh"

class Streamer
{
public:

  Streamer(){}
  ~Streamer(){}

  template<class DataType, class MemType>
  void stream2mem(ap_uint<3> bx, hls::stream<DataType>& sdatain, MemType& memory)
  {
#pragma HLS inline off
    
    // reset memory first
    memory.clear(bx);
    
  S2M_LOOP: for (int i = 0; i < kMaxProc; ++i) {
#pragma HLS PIPELINE II = 1
      DataType din;
      if (sdatain.read_nb(din)) {
        bool success = memory.write_mem(bx, din);
        assert(success);
      }
	}
  }

  template<class MemType, class DataType>
  void mem2stream(ap_uint<3> bx, MemType& memory, hls::stream<DataType>& sdataout)
  {
#pragma HLS inline off
    
    unsigned int mem_entries = memory.getEntries(bx);
    
  M2S_LOOP: for (int i = 0; i < kMaxProc; ++i) {
#pragma HLS PIPELINE II = 1
      if (i < mem_entries) {
        DataType dout = memory.read_mem(bx, i).raw();
        //sdataout << dout;
        bool success = sdataout.write_nb(dout);
        assert(success);
      }
    }
  }
  
};

#endif
