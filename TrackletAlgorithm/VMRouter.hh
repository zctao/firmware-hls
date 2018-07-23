// First attempt at the VMRouter module
//
// Assumptions:
// Must be even-number layer
// Must be PS-layer
//
#pragma once
#define FAT_CLASS
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "Constants.hh"
#include "ap_int.h"
#include <vector>
#include <stdio.h>
#include <bitset>


template <class T, int N>
class VMRouter
{
private:
  T *stubsInLayer_;
  T *allStubs_;
  ReducedStubLayer *vmStubsPH1Z1_;
  ReducedStubLayer *vmStubsPH2Z1_;
  ReducedStubLayer *vmStubsPH3Z1_;
  ReducedStubLayer *vmStubsPH4Z1_;
  ReducedStubLayer *vmStubsPH1Z2_;
  ReducedStubLayer *vmStubsPH2Z2_;
  ReducedStubLayer *vmStubsPH3Z2_;
  ReducedStubLayer *vmStubsPH4Z2_;
  const int nStubs_;
  ReducedIndex *nPH1Z1_; ReducedIndex *nPH2Z1_;
  ReducedIndex *nPH3Z1_; ReducedIndex *nPH4Z1_;
  ReducedIndex *nPH1Z2_; ReducedIndex *nPH2Z2_;
  ReducedIndex *nPH3Z2_; ReducedIndex *nPH4Z2_;
public:
  // constructor; just copy in the pointers to the input and output arrays
  VMRouter(T *stubsInLayer,
           T *allStubs,
           ReducedStubLayer *vmStubsPH1Z1,
           ReducedStubLayer *vmStubsPH2Z1,
           ReducedStubLayer *vmStubsPH3Z1,
           ReducedStubLayer *vmStubsPH4Z1,
           ReducedStubLayer *vmStubsPH1Z2,
           ReducedStubLayer *vmStubsPH2Z2,
           ReducedStubLayer *vmStubsPH3Z2,
           ReducedStubLayer *vmStubsPH4Z2,
           const int nStubs,
           ReducedIndex *nPH1Z1, ReducedIndex *nPH2Z1,
           ReducedIndex *nPH3Z1, ReducedIndex *nPH4Z1,
           ReducedIndex *nPH1Z2, ReducedIndex *nPH2Z2,
           ReducedIndex *nPH3Z2, ReducedIndex *nPH4Z2
	   ):
  stubsInLayer_(stubsInLayer),
    allStubs_(allStubs),
    vmStubsPH1Z1_(vmStubsPH1Z1),
    vmStubsPH2Z1_(vmStubsPH2Z1),
    vmStubsPH3Z1_(vmStubsPH3Z1),
    vmStubsPH4Z1_(vmStubsPH4Z1),
    vmStubsPH1Z2_(vmStubsPH1Z2),
    vmStubsPH2Z2_(vmStubsPH2Z2),
    vmStubsPH3Z2_(vmStubsPH3Z2),
    vmStubsPH4Z2_(vmStubsPH4Z2),
    nStubs_(nStubs),
    nPH1Z1_(nPH1Z1),
    nPH2Z1_(nPH2Z1),
    nPH3Z1_(nPH3Z1),
    nPH4Z1_(nPH4Z1),
    nPH1Z2_(nPH1Z2),
    nPH2Z2_(nPH2Z2),
    nPH3Z2_(nPH3Z2),
    nPH4Z2_(nPH4Z2)
  {}
  // doesn't this need to know about BX somewhere?
  void execute()
  {
    ReducedIndex index = 0;
  STUBLOOP: for (int i=0; i<MAX_nSTUBS; ++i) {
#pragma HLS PIPELINE II=1
      if (i < nStubs_) {
        // Extract stub parameters
        // Calculate reduced-format parameters.
        // Calculate routing parameters
        ReducedZ_Layer redZ;
        ReducedPhi_Layer redPhi;
        ReducedR_Layer redR;
        ReducedPt_Layer redPt;
        ap_uint<2> routePhi;
        ap_uint<1> routeZ;
        if (N==1 || N==2 || N==3) { // PS layers
          FullZ_Layer_PS curZ = stubsInLayer_[i].GetZ();
          FullPhi_Layer_PS curPhi = stubsInLayer_[i].GetPhi();
          FullR_Layer_PS curR = stubsInLayer_[i].GetR();
          FullPt_Layer_PS curPt = stubsInLayer_[i].GetPt();
          redPt = curPt;
          redZ = curZ.range(5+4,5);
          redR = curR.range(5+3,5);
          routeZ = curZ[9];
          if (N==2){
            redPhi = curPhi(9+6,9);
            routePhi = (curPhi >> 12 ) & 0x3U;
            routePhi = curPhi(12+2,2);
          } else {
            redPhi = (curPhi >> 9) ^ 0x4U; // why is this OR'd?
            routePhi = (((curPhi >> 11) - 1) >> 1) & 0x3U;
          }
        }
        else if (N==4 || N==5 || N==6) { // 2S layers
          FullZ_Layer_2S curZ = stubsInLayer_[i].GetZ();
          FullPhi_Layer_2S curPhi = stubsInLayer_[i].GetPhi();
          FullR_Layer_2S curR = stubsInLayer_[i].GetR();
          FullPt_Layer_2S curPt = stubsInLayer_[i].GetPt();
          redPt = curPt;
          redZ = curZ.range(4+1,1);
          redR = curR.range(2+6,2);
          routeZ = curZ[5];
          if (N==5){
            redPhi = (curPhi >> 12) ^ 0x4U; // why is this an OR?
            routePhi = (((curPhi >> 14) - 1) >> 1) & 0x3U;
          } else {
            redPhi = curPhi.range(12+3,3);
            routePhi = curPhi.range(15+2,15);
          }
        }

        // Rewrite stub parameters to new stub in allStubs
        allStubs_[i].AddStub(stubsInLayer_[i].raw());

        // Route stubs
        switch (routeZ) {
        case 0:
          switch (routePhi) { 
          case 0:
            vmStubsPH1Z1_[nPH1Z1_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH1Z1_);
            break;
          case 1:
            vmStubsPH2Z1_[nPH2Z1_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH2Z1_);
            break;
          case 2:
            vmStubsPH3Z1_[nPH3Z1_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH3Z1_);
            break;
          case 3:
            vmStubsPH4Z1_[nPH4Z1_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH4Z1_);
            break;
          }
          break;
        case 1:
          switch (routePhi) {
          case 0:
            vmStubsPH1Z2_[nPH1Z2_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH1Z2_);
            break;
          case 1:
            vmStubsPH2Z2_[nPH2Z2_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH2Z2_);
            break;
          case 2:
            vmStubsPH3Z2_[nPH3Z2_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH3Z2_);
            break;
          case 3:
            vmStubsPH4Z2_[nPH4Z2_->to_int()].AddStub(redZ, redPhi, redR, redPt, index);
            ++(*nPH4Z2_);
            break;
          }
          break;
        }
        if (index==63)  
          index--;  // what vodoo is this?
        ++index;
      } 
      else 
        break;
    }
  } // end void execute()
};




