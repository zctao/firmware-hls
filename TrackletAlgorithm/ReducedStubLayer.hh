// This is the ReducedStubLayer class, which contains, in essence the 18 bits of a reduced stub, after it has been routed
#pragma once

// ReducedZ_Layer z; // 4 bits
// ReducedPhi_Layer phi; // 3 bits
// ReducedR_Layer r; // 2 bits
// ReducedPt_Layer pt; // 3 bits
// ReducedIndex index; // 6 bits



#include "ap_int.h"
#include "Constants.hh"
class ReducedStubLayer
{
private:
  ReducedStubData data_; // 18 bits
public:
  ReducedStubLayer():
    data_(0)
  {
  }
  // default copy constructor is ok

  void AddStub(ReducedZ_Layer newZ, ReducedPhi_Layer newPhi, ReducedR_Layer newR, ReducedPt_Layer newPt, ReducedIndex newIndex)
  {
    data_ = newZ | (newPhi.to_long()<< 4) | (newR.to_long() << (4+3)) | 
      (newPt.to_long() << (4+3+2)) | (newIndex.to_long() << (4+3+2+3));
  }
  ReducedStubData raw() const 
  {
    return data_;
  }
  ReducedZ_Layer GetZ() const
  {
    ReducedZ_Layer tz = data_ & 0xFUL;
    return tz;
  }
  ReducedPhi_Layer GetPhi() const
  {
    ReducedPhi_Layer tphi = ( data_>> 4 ) & 0x7UL;
    return tphi;
  }
  ReducedR_Layer GetR() const
  {
    ReducedR_Layer tr = (data_ >> (4+3)) & 0x3UL;
    return tr;
  }
  ReducedPt_Layer GetPt() const
  {
    ReducedPt_Layer tpt = (data_ >> (4+3+2) ) & 0x7UL;
    return tpt;
  }
  ReducedIndex GetIndex() const
  {
    ReducedIndex tindex = ( data_ >> (4+3+2+3) ) & 0x3FUL;
    return tindex;
  }
  // void SetZ(const ReducedZ_Layer newZ)
  // {
  //   z = newZ;
  // }
  // void SetPhi(const ReducedPhi_Layer newPhi)
  // {
  //   phi = newPhi;
  // }
  // void SetR(const ReducedR_Layer newR)
  // {
  //   r = newR;
  // }
  // void SetPt(const ReducedPt_Layer newPt)
  // {
  //   pt = newPt;
  // }
  // void SetIndex(const ReducedIndex newIndex)
  // {
  //   index = newIndex;
  // }
};

