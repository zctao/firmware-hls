// This is the ReducedStubLayer class, which contains the 18 bits of a reduced stub
#pragma once

// Define bit widths for reduced stub parameters


// ReducedZ_Layer z; // 4 bits
// ReducedPhi_Layer phi; // 3 bits
// ReducedR_Layer r; // 2 bits
// ReducedPt_Layer pt; // 3 bits
// ReducedIndex index; // 6 bits

namespace ReducedStub {
  // sizes
  constexpr int kZSize = 4;
  constexpr int kPhiSize = 3;
  constexpr int kRSize = 2;
  constexpr int kPtSize = 3;
  constexpr int kIndexSize = 6;
  constexpr int kReducedStubSize = kZSize + kPhiSize + kRSize + kPtSize + kIndexSize;

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
   
};

typedef ap_uint<ReducedStub::kReducedStubSize> ReducedStubData;

typedef ap_uint<ReducedStub::kZSize> ReducedZ_Layer;
typedef ap_uint<ReducedStub::kPhiSize> ReducedPhi_Layer;
typedef ap_uint<ReducedStub::kRSize> ReducedR_Layer;
typedef ap_uint<ReducedStub::kPtSize> ReducedPt_Layer;
typedef ap_uint<ReducedStub::kIndexSize> ReducedIndex;



#include "ap_int.h"
#include "Constants.hh"

//#include "MemoryTemplate.hh"
using namespace ReducedStub;

class ReducedStubLayer
{
private:
  ReducedStubData data_; // 18 bits
public:
  ReducedStubLayer():
    data_(0)
  {
  }
  // default copy, move etc constructor is ok

  ReducedStubLayer(const ReducedZ_Layer newZ, const ReducedPhi_Layer newPhi,
		   const ReducedR_Layer newR, const ReducedPt_Layer newPt,
		   const ReducedIndex newIndex):
    data_((((( newZ, newPhi), newR), newPt), newIndex))
  {
  }
  void AddStub(const ReducedZ_Layer newZ, const ReducedPhi_Layer newPhi,
		   const ReducedR_Layer newR, const ReducedPt_Layer newPt,
		   const ReducedIndex newIndex)
  {
	data_ = (((( newZ, newPhi), newR), newPt), newIndex);

  }

  ReducedStubData raw() const 
  {
    return data_;
  }
  ReducedZ_Layer GetZ() const
  {
    return data_.range(kZLowOff, kZHiOff);
  }
  ReducedPhi_Layer GetPhi() const
  {
    return data_.range(kPhiLowOff, kPhiHiOff);
  }
  ReducedR_Layer GetR() const
  {
    return data_.range(kZLowOff, kZHiOff);
  }
  ReducedPt_Layer GetPt() const
  {
    return data_.range(kPtLowOff, kPtHiOff);
  }
  ReducedIndex GetIndex() const
  {
    return data_.range(kIndexLowOff, kIndexHiOff);
  }
  void SetZ(const ReducedZ_Layer newZ)
  {
    data_.range(kZLowOff, kZHiOff) = newZ;
  }
  void SetPhi(const ReducedPhi_Layer newPhi)
  {
    data_.range(kPhiLowOff, kPhiHiOff) = newPhi;
  }
  void SetR(const ReducedR_Layer newR)
  {
    data_.range(kZLowOff, kZHiOff) = newR;
  }
  void SetPt(const ReducedPt_Layer newPt)
  {
    data_.range(kPtLowOff, kPtHiOff) = newPt;
  } 
  void SetIndex(const ReducedIndex newIndex)
  {
    data_.range(kIndexLowOff, kIndexHiOff) = newIndex;
  }
};

//typedef MemoryTemplate<ReducedStubLayer, 3, kNBits_MemAddr> ReducedStubLayerMemory;
