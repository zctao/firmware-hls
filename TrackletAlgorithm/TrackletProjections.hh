#ifndef TRACKLETPROJECTIONS_HH
#define TRACKLETPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<13> TProjTCID;
typedef ap_uint<14> TProjPHI;
typedef ap_int<12> TProjZ;
typedef ap_int<11> TProjPHIDER;
typedef ap_int<10> TProjZDER;
typedef ap_uint<1+1+13+14+12+11+10> TProj;

struct TProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  TProjTCID   tracklet_index;
  TProjPHI    phi;
  TProjZ      z;
  TProjPHIDER phider;
  TProjZDER   zder;
};

class TrackletProjections: public MemoryBase<TProjData, MemDepth>
{
public:
  
  TrackletProjections(){}

#ifndef __SYNTHESIS__
#include <iostream>
  // overload base class add_mem()
  using MemoryBase<TProjData, MemDepth>::add_mem;
  // add memory from data string
  bool add_mem(const char* datastr, int base = 16)
  {
	  TProj data(datastr, base);
	  // convert to struct
	  TProjData tproj = {
			  data.range(61,61), // plusNeighbor
			  data.range(60,60), // minusNeighbor
			  data.range(59,47), // TCID
			  data.range(46,33), // phi
			  data.range(32,21), // z
			  data.range(20,10), // phider
			  data.range(9,0)    // zder
	  };

	  return add_mem(tproj);
  }

  // print memory contents
  void print_entry(int i) const
  {
	  TProj tproj =
			  (dataarray_[i].plusNeighbor,
			  (dataarray_[i].minusNeighbor,
					  (dataarray_[i].tracklet_index,
							  (dataarray_[i].phi,
									  (dataarray_[i].z,
											  (dataarray_[i].phider,dataarray_[i].zder)
			)))));

	  std::cout << std::hex << tproj << std::endl;
  }

#endif

};

#endif
