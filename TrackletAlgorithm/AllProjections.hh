#ifndef ALLPROJECTIONS_HH
#define ALLPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<13> AProjTCID;
typedef ap_uint<14> AProjPHI;
typedef ap_int<12> AProjZ;
typedef ap_int<11> AProjPHIDER;
typedef ap_int<10> AProjZDER;

typedef ap_uint<1+1+13+14+12+11+10> AllProjData;

// Data definition
class AllProjection
{
private:
  AllProjData data_;

public:
  AllProjection(AllProjData newdata):
    data_(newdata)
  {}

  AllProjection(bool plusneighbor, bool minusneighbor, AProjTCID tcid,
                AProjPHI phi, AProjZ z, AProjPHIDER phider, AProjZDER zder):
    data_(((((((plusneighbor,minusneighbor),tcid),phi),z),phider),zder))
  {}
  
  AllProjection():
    data_(0)
  {}

  AllProjection(const char* datastr, int base = 16)
  {
    AllProjData newdata(datastr, base);
    data_ = newdata;
  }
  
  // copy constructor
  AllProjection(const AllProjection& rhs):
    data_(rhs.raw())
  {}

  AllProjData raw() const {return data_;}

  // Getter
  bool IsPlusNeighbor() const {return data_.range(61,61);}
  bool IsMinusNeighbor() const {return data_.range(60,60);}
  AProjTCID GetTrackletIndex() const {return data_.range(59,47);}
  AProjPHI GetPhi() const {return data_.range(46,33);}
  AProjZ GetZ() const {return data_.range(32,21);}
  AProjPHIDER GetPhiDer() {return data_.range(20,10);}
  AProjZDER GetZDer() {return data_.range(9,0);}

  // Setter
  void SetIsPlusNeighbor(bool isplusneighbor)
  {
    data_.range(61,61) = isplusneighbor;
  }

  void SetIsMinusNeighbor(bool isminusneighbor)
  {
    data_.range(60,60) = isminusneighbor;
  }

  void SetTrackletIndex(AProjTCID id)
  {
    data_.range(59,47) = id;
  }

  void SetPhi(AProjPHI phi)
  {
    data_.range(46,33) = phi;
  }

  void SetZ(AProjZ z)
  {
    data_.range(32,21) = z;
  }

  void SetPhiDer(AProjPHIDER phider)
  {
    data_.range(20,10) = phider;
  }

  void SetZDer(AProjZDER zder)
  {
    data_.range(9,0) = zder;
  }
  
};

// Memory definition
typedef MemoryBase<AllProjection, 2, kMemDepth> AllProjectionMemory;

/*
//template<unsigned int bx=2, unsigned int memdepth=kMemDepth>
class AllProjections: public MemoryBase<AllProj, 2, kMemDepth>
{
public:

  // getter
  static bool get_plusNeighbor(const AllProj data)       {return data.range(61,61);}
  static bool get_minusNeighbor(const AllProj data)      {return data.range(60,60);}
  static AProjTCID get_trackletIndex(const AllProj data) {return data.range(59,47);}
  static AProjPHI get_phi(const AllProj data)            {return data.range(46,33);}
  static AProjZ get_z(const AllProj data)                {return data.range(32,21);}
  static AProjPHIDER get_phider(const AllProj data)      {return data.range(20,10);}
  static AProjZDER get_zder(const AllProj data)          {return data.range(9,0);}

};
*/

#endif
