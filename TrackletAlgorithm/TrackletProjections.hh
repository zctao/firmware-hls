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
};

#endif
