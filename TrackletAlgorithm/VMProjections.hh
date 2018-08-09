#ifndef VMPROJECTIONS_HH
#define VMPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<7> VMPID;
typedef ap_uint<MEBinsBits+1> VMPZBIN;
typedef ap_int<4> VMPFINEZ;
typedef ap_uint<5> VMPRINV;
typedef ap_uint<7+MEBinsBits+1+4+5+1> VMProj;

struct VMProjData {
  VMPID   index;
  VMPZBIN zbin;
  VMPFINEZ finez;
  VMPRINV rinv;
  bool PSseed;
};

class VMProjections: public MemoryBase<VMProjData, MemDepth>
{
public:
  
  VMProjections(){}

#ifndef __SYNTHESIS__
#include <iostream>
  // overload base class add_mem()
  using MemoryBase<VMProjData, MemDepth>::add_mem;
  // add memory from data string
  bool add_mem(const char* datastr, int base = 16)
  {
	  VMProj data(datastr, base);
	  // convert to struct
	  VMProjData vmproj = {
			  data.range(20,14), // index
			  data.range(13,10), // zbin
			  data.range(9,6),   // finez
			  data.range(5,1),   // rinv
			  data.range(0,0)    // PSseed
	  };

	  return add_mem(vmproj);
  }

  // print memory contents
  void print_entry(int i) const
  {
	  VMProj vmproj =
			  (dataarray_[i].index,
					  (dataarray_[i].zbin,
							  (dataarray_[i].finez,
									  (dataarray_[i].rinv,dataarray_[i].PSseed)
			)));

	  std::cout << std::hex << vmproj << std::endl;
  }
#endif

};

#endif
