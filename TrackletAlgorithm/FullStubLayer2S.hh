// This is the FullStubLayer class, which contains, in essence the 36 bits of a full stub, with few other functions
#pragma once
#include <cstdio>
#include "ap_int.h"
#include "Constants.hh"


class FullStubLayer2S
{
private:
  StubData data_;
public:
  FullStubLayer2S(StubData newdata):
    data_(newdata)
  {}
  FullStubLayer2S():
    data_(0)
  {
  }
  StubData raw() const
  {
    return data_;
  }
  FullStubLayer2S(const FullZ_Layer_2S newZ, const FullPhi_Layer_2S newPhi,
		     const FullR_Layer_2S newR, const FullPt_Layer_2S newPt)
  {
    AddStub(newZ, newPhi, newR, newPt);
  }
  void AddStub(const StubData newStub)
  {
	data_ = newStub;
  }
  void AddStub(const FullZ_Layer_2S newZ, const FullPhi_Layer_2S newPhi,
	       const FullR_Layer_2S newR, const FullPt_Layer_2S newPt)
  {
    // without the to_long these variables truncate at their current bit width.
    data_ = newZ | (newPhi.to_long()<<8) | (newR.to_long()<<(17+8)) | (newPt.to_long()<<(17+8+8));
  }
  FullZ_Layer_2S GetZ() const
  {
    FullZ_Layer_2S tz = (data_&0xFFUL);
    return tz;
  }
  FullPhi_Layer_2S GetPhi()  const
  {
    FullPhi_Layer_2S tPhi = (data_>>8)& 0x1FFFFUL;
    return tPhi;
  }
  FullR_Layer_2S GetR()  const
  {
    FullR_Layer_2S tR = (data_>> (8+17))&0xFFUL;
    return tR;
  }
  FullPt_Layer_2S GetPt()  const
  {
    FullPt_Layer_2S tPt = (data_ >> (8+17+8)) & 0x7UL;
    return tPt;
    //return pt;
  }
  // --------------------------------------------------
  // NOTA BENE -- THESE SETTERS HAVE NOT BEEN DEBUGGED
  // --------------------------------------------------
  void SetZ(const FullZ_Layer_2S newZ)
  {
    // 36 bit mask: 0x3FFFFFFFFU
    const long int maskZ = 0xFFFFFFF00UL; // bottom 8 bits
    const int zShift = 0;
    data_ = (data_ & maskZ) | (newZ.to_long() << zShift);
  }
  void SetPhi(const FullPhi_Layer_2S newPhi)
  {
    const long int maskPhi = 0xFFE0000FFUL; // 17 bits, shifted up 8 bits
    const int phiShift = 8;
    data_ = ( data_ & maskPhi) | ( newPhi.to_long() << phiShift);
  }
  void SetR(const FullR_Layer_2S newR)
  {
    const long int maskR = 0xE01FFFFFFUL;
    const int rShift = 8+17;
    data_ = (data_ & maskR ) | ( newR.to_long() << rShift);
  }
  void SetPt(const FullPt_Layer_2S newPt)
  {
    const long int maskPt = 0x1FFFFFFFFUL;
    const int ptShift = 8+17+8;
    data_ = (data_ & maskPt ) | ( newPt.to_long() << ptShift);
  }
};
