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
    // reset memory first
    memory.clear(bx);
    
    for (int i = 0; i < kMaxProc; ++i) {
#pragma HLS PIPELINE II = 1 enable_flush
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
    for (int i = 0; i < kMaxProc; ++i) {
#pragma HLS PIPELINE II = 1 enable_flush
      if (i < memory.getEntries(bx)) {
        DataType dout = memory.read_mem(bx, i);
        //sdataout << dout;
        bool success = sdataout.write_nb(dout);
        assert(success);
      }
    }
  }
  
};

#endif
