// This is the FullStubLayer class, which contains the 36 bits of a full stub (2S)
#pragma once
#include "ap_int.h"
#include "Constants.hh"

typedef ap_uint<8> FullZ_Layer_2S;
typedef ap_uint<17> FullPhi_Layer_2S;
typedef ap_uint<8>  FullR_Layer_2S;
typedef ap_uint<3>  FullPt_Layer_2S;


namespace FullStub2S {
  // sizes
  constexpr int kZSize = 8;
  constexpr int kPhiSize = 17;
  constexpr int kRSize = 8;
  constexpr int kPtSize = 3;
  constexpr int kFullStubSize = kZSize + kPhiSize + kRSize + kPtSize;

  // offsets
  constexpr int kZLowOff = 0;
  constexpr int kZHiOff = kZLowOff + kZSize - 1;
  constexpr int kPhiLowOff = kZHiOff + 1;
  constexpr int kPhiHiOff = kPhiLowOff + kPhiSize - 1;
  constexpr int kRLowOff = kPhiHiOff + 1;
  constexpr int kRHiOff = kRLowOff + kRSize - 1 ;
  constexpr int kPtLowOff = kRHiOff + 1;
  constexpr int kPtHiOff = kPtLowOff + kPtSize - 1;
  constexpr int kIndexLowOff = kPtHiOff + 1;
  constexpr int kIndexHiOff = kIndexLowOff + kIndexSize -1;
  
}

class FullStubLayer2S
{
private:
  StubData data_;
public:
  FullStubLayer2S(const StubData newdata):
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
    data_ = (((newZ, newPhi),newR),newPt);
  }
  FullZ_Layer_2S GetZ() const
  {
    return data_.range(kZLowOff, kZHiOff);
  }
  FullPhi_Layer_2S GetPhi()  const
  {
    return data_.range(kPhiLowOff, kPhiHiOff);
  }
  FullR_Layer_2S GetR()  const
  {
    return data_.range(kZLowOff, kZHiOff);
  }
  FullPt_Layer_2S GetPt()  const
  {
    return data_.range(kPtLowOff, kPtHiOff);
  }
  // --------------------------------------------------
  // Setters
  // --------------------------------------------------
  void SetZ(const FullZ_Layer_2S newZ)
  {
    data_.range(kZLowOff, kZHiOff) = newZ;
  }
  void SetPhi(const FullPhi_Layer_2S newPhi)
  {
    data_.range(kPhiLowOff, kPhiHiOff) = newPhi;
  }
  void SetR(const FullR_Layer_2S newR)
  {
    data_.range(kZLowOff, kZHiOff) = newR;
  }
  void SetPt(const FullPt_Layer_2S newPt)
  {
    data_.range(kPtLowOff, kPtHiOff) = newPt;
  }
};
