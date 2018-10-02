#ifndef TRACKLETPROJECTIONS_HH
#define TRACKLETPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<13> TProjTCID;
typedef ap_uint<14> TProjPHI;
typedef ap_int<12> TProjZ;
typedef ap_int<11> TProjPHIDER;
typedef ap_int<10> TProjZDER;

typedef ap_uint<1+1+13+14+12+11+10> TProjData; // move to Constants.hh?

// Data definition
class TrackletProjection
{
private:
  TProjData data_;
  
public:
  TrackletProjection(TProjData newdata):
    data_(newdata)
  {}

  TrackletProjection(bool plusneighbor, bool minusneighbor, TProjTCID tcid,
                     TProjPHI phi, TProjZ z, TProjPHIDER phider, TProjZDER zder):
    data_( ((((((plusneighbor,minusneighbor),tcid),phi),z),phider),zder) )
  {}
  
  TrackletProjection():
    data_(0)
  {}

  TrackletProjection(const char* datastr, int base = 16)
  {
    TProjData newdata(datastr, base);
    data_ = newdata;
  }
  
  // copy constructor
  TrackletProjection(const TrackletProjection& rhs):
    data_(rhs.raw())
  {}

  TProjData raw() const {return data_;}

  // Getter
  bool IsPlusNeighbor() const {return data_.range(61,61);}
  bool IsMinusNeighbor() const {return data_.range(60,60);}
  TProjTCID GetTrackletIndex() const {return data_.range(59,47);}
  TProjPHI GetPhi() const {return data_.range(46,33);}
  TProjZ GetZ() const {return data_.range(32,21);}
  TProjPHIDER GetPhiDer() {return data_.range(20,10);}
  TProjZDER GetZDer() {return data_.range(9,0);}

  // Setter
  void SetIsPlusNeighbor(bool isplusneighbor)
  {
    data_.range(61,61) = isplusneighbor;
  }

  void SetIsMinusNeighbor(bool isminusneighbor)
  {
    data_.range(60,60) = isminusneighbor;
  }

  void SetTrackletIndex(TProjTCID id)
  {
    data_.range(59,47) = id;
  }

  void SetPhi(TProjPHI phi)
  {
    data_.range(46,33) = phi;
  }

  void SetZ(TProjZ z)
  {
    data_.range(32,21) = z;
  }

  void SetPhiDer(TProjPHIDER phider)
  {
    data_.range(20,10) = phider;
  }

  void SetZDer(TProjZDER zder)
  {
    data_.range(9,0) = zder;
  }
  
};

// Memory definition
typedef MemoryBase<TrackletProjection, 2, kMemDepth> TrackletProjectionMemory;
// TODO: rename MemoryBase to MemoryTemplate

/*
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
*/

#endif
