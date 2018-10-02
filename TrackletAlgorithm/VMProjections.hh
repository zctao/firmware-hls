#ifndef VMPROJECTIONS_HH
#define VMPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<7> VMPID;
typedef ap_uint<MEBinsBits+1> VMPZBIN;
typedef ap_int<4> VMPFINEZ;
typedef ap_uint<5> VMPRINV;

typedef ap_uint<7+MEBinsBits+1+4+5+1> VMProjData;

// Data definition
class VMProjection
{
private:
  VMProjData data_;
  
public:
  VMProjection(VMProjData newdata):
    data_(newdata)
  {}

  VMProjection(VMPID id, VMPZBIN zbin, VMPFINEZ finez, VMPRINV rinv, bool ps):
    data_( ((((id,zbin),finez),rinv),ps) )
  {}

  VMProjection():
    data_(0)
  {}

  VMProjection(const char* datastr, int base = 16)
  {
    VMProjData newdata(datastr, base);
    data_ = newdata;
  }
  
  // copy constructor
  VMProjection(const VMProjection& rhs):
    data_(rhs.raw())
  {}

  VMProjData raw() const {return data_;}

  // Getter
  VMPID GetIndex() const {return data_.range(20,14);}
  VMPZBIN GetZBin() const {return data_.range(13,10);}
  VMPFINEZ GetFineZ() const {return data_.range(9,6);}
  VMPRINV GetRInv() const {return data_.range(5,1);}
  bool GetIsPSSeed() const {return data_.range(0,0);}

  // Setter
  void SetIndex(VMPID id)
  {
    data_.range(20,14) = id;
  }

  void SetZBin(VMPZBIN zbin)
  {
    data_.range(13,10) = zbin;
  }

  void SetFineZ(VMPFINEZ finez)
  {
    data_.range(9,6) = finez;
  }

  void SetRInv(VMPRINV rinv)
  {
    data_.range(5,1) = rinv;
  }

  void SetIsPSSeed(bool psseed)
  {
    data_.range(0,0) = psseed;
  }
  
};

// Memory definition
typedef MemoryBase<VMProjection, 2, kMemDepth> VMProjectionMemory;

/*
//template<unsigned int bx=2, unsigned int memdepth=kMemDepth>
class VMProjections: public MemoryBase<VMProj, 2, kMemDepth>
{
public:

  static VMPID get_index(const VMProj data) {return data.range(20,14);}
  static VMPZBIN get_zbin(const VMProj data) {return data.range(13,10);}
  static VMPFINEZ get_finez(const VMProj data) {return data.range(9,6);}
  static VMPRINV get_rinv(const VMProj data) {return data.range(5,1);}
  static bool get_PSseed(const VMProj data) {return data.range(0,0);}
};
*/

#endif
