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

/*
struct TProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  TProjTCID   tracklet_index;
  TProjPHI    phi;
  TProjZ      z;
  TProjPHIDER phider;
  TProjZDER   zder;
};
*/

//template<unsigned int bx=2, unsigned int memdepth=kMemDepth>
class TrackletProjections: public MemoryBase<TProj, 2, kMemDepth>
{
public:

  // getter
  static bool get_plusNeighbor(const TProj data)       {return data.range(61,61);}
  static bool get_minusNeighbor(const TProj data)      {return data.range(60,60);}
  static TProjTCID get_trackletIndex(const TProj data) {return data.range(59,47);}
  static TProjPHI get_phi(const TProj data)            {return data.range(46,33);}
  static TProjZ get_z(const TProj data)                {return data.range(32,21);}
  static TProjPHIDER get_phider(const TProj data)      {return data.range(20,10);}
  static TProjZDER get_zder(const TProj data)          {return data.range(9,0);}

/*
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
*/

#ifndef __SYNTHESIS__
#include <iostream>
/*
  // print memory contents
  void print_data(const TProjData& tprojdata) const
  {
	  TProj tproj =
			  (tprojdata.plusNeighbor,
			  (tprojdata.minusNeighbor,
					  (tprojdata.tracklet_index,
							  (tprojdata.phi,
									  (tprojdata.z,
											  (tprojdata.phider,tprojdata.zder)
			)))));

	  std::cout << std::hex << tproj << std::endl;
  }
*/
/*
  void print_data(const TProjData& tproj) const
  {
	  std::cout << "tproj: " << tproj.plusNeighbor << " " << tproj.minusNeighbor << " "
			  	<< tproj.phi << " " << tproj.z << " " << tproj.phider << " " << tproj.zder << std::endl;
  }
*/
#endif

};

#endif
