#ifndef ALLPROJECTIONS_HH
#define ALLPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<13> AProjTCID;
typedef ap_uint<14> AProjPHI;
typedef ap_int<12> AProjZ;
typedef ap_int<11> AProjPHIDER;
typedef ap_int<10> AProjZDER;
typedef ap_uint<1+1+13+14+12+11+10> AllProj;

struct AllProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  AProjTCID   tracklet_index;
  AProjPHI    phi;
  AProjZ      z;
  AProjPHIDER phider;
  AProjZDER   zder;
};

class AllProjections: public MemoryBase<AllProjData, MemDepth>
{
public:

  AllProjections(){}

#ifndef __SYNTHESIS__
#include <iostream>
  // overload base class add_mem()
  using MemoryBase<AllProjData, MemDepth>::add_mem;
  // add memory from data string
  bool add_mem(const char* datastr, int base = 16)
  {
	  AllProj data(datastr, base);
	  // convert to struct
	  AllProjData aproj = {
			  data.range(61,61), // plusNeighbor
			  data.range(60,60), // minusNeighbor
			  data.range(59,47), // TCID
			  data.range(46,33), // phi
			  data.range(32,21), // z
			  data.range(20,10), // phider
			  data.range(9,0)    // zder
	  };

	  return add_mem(aproj);
  }

  // print memory contents
  void print_entry(int i) const
  {
	  AllProj aproj =
			  (dataarray_[i].plusNeighbor,
			  (dataarray_[i].minusNeighbor,
					  (dataarray_[i].tracklet_index,
							  (dataarray_[i].phi,
									  (dataarray_[i].z,
											  (dataarray_[i].phider,dataarray_[i].zder)
			)))));

	  std::cout << std::hex << aproj << std::endl;
  }

#endif

};

#endif
