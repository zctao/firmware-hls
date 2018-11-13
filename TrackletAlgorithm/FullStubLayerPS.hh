// This is the FullStubLayer class, which contains the 36 bits of a full stub (PS)
//using namespace std;
#pragma once
#include "ap_int.h"
#include "Constants.hh"

typedef ap_uint<12> FullZ_Layer_PS;
typedef ap_uint<14> FullPhi_Layer_PS;
typedef ap_uint<7>  FullR_Layer_PS;
typedef ap_uint<3>  FullPt_Layer_PS;
namespace FullStub2S {
  // sizes
  constexpr int kZSize = 12;
  constexpr int kPhiSize = 14;
  constexpr int kRSize = 7;
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



class FullStubLayerPS
{
private:
  StubData data_;
public:
  FullStubLayerPS(const StubData & newdata):
    data_(newdata)
  {}
  FullStubLayerPS():
    data_(0)
  {
  }
  // default copy constructor is ok
  StubData raw() const 
  {
    return data_;
  }
  FullStubLayerPS(const FullZ_Layer_PS newZ, const FullPhi_Layer_PS newPhi,
		  const FullR_Layer_PS newR, const FullPt_Layer_PS newPt)
  {
    AddStub(newZ, newPhi, newR, newPt);
  }
  void AddStub(const StubData newStub)
  {
    data_ = newStub;
  }
  void AddStub(const FullZ_Layer_PS newZ, const FullPhi_Layer_PS newPhi, 
	       const FullR_Layer_PS newR, const FullPt_Layer_PS newPt)
  {
    data_ = (((newZ, newPhi),newR),newPt);
    
  }
  FullZ_Layer_PS GetZ() const
  {
    return data_.range(kZLowOff, kZHiOff);
  }
  FullPhi_Layer_PS GetPhi()  const
  {
    return data_.range(kPhiLowOff, kPhiHiOff);
  }
  FullR_Layer_PS GetR()  const
  {
    return data_.range(kZLowOff, kZHiOff);
  }
  FullPt_Layer_PS GetPt()  const
  {
    return data_.range(kPtLowOff, kPtHiOff);
  }
  // --------------------------------------------------
  // Setters
  // --------------------------------------------------
  void SetZ(const FullZ_Layer_PS newZ)
  {
    data_.range(kZLowOff, kZHiOff) = newZ;
  }
  void SetPhi(const FullPhi_Layer_PS newPhi)
  {
    data_.range(kPhiLowOff, kPhiHiOff) = newPhi;
  }
  void SetR(const FullR_Layer_PS newR)
  {
    data_.range(kZLowOff, kZHiOff) = newR;
  }
  void SetPt(const FullPt_Layer_PS newPt)
  {
    data_.range(kPtLowOff, kPtHiOff) = newPt;
  }
};

