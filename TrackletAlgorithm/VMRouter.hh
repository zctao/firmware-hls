// VMRouter module
//
//
#pragma once
//#define FAT_CLASS
#include "FullStubLayerPS.hh"
#include "FullStubLayer2S.hh"
#include "Constants.hh"

#ifndef __SYNTHESIS__
#include <iostream>
#include "HelperFunctions.hh"
#endif // SYNTHESIS

#include "ap_int.h"

const int kNumZRegions=2;
const int kNumPhiRegions=4;

template <class T>
class VMRouter
{
private:
  T (&stubsInLayer_)[MAX_nSTUBS];
  T *allStubs_;
  ReducedStubLayer (& rVMStubs_)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS];
  ReducedIndex (& n_)[kNumZRegions][kNumPhiRegions]; // [z region][phi region]
  const int Layer_;
public:
  // constructor; just copy in the pointers to the input and output arrays
  VMRouter(T (&stubsInLayer)[MAX_nSTUBS],
           T *allStubs,
           ReducedStubLayer (&rVMStubs)[kNumZRegions][kNumPhiRegions][MAX_nSTUBS],
	   ReducedIndex (&n)[kNumZRegions][kNumPhiRegions],
	   int layer
	   ):
    stubsInLayer_(stubsInLayer),
    allStubs_(allStubs),
    rVMStubs_(rVMStubs),
    n_(n),
    Layer_(layer)
  {}
  // doesn't this need to know about BX somewhere?
  void execute(const int nStubs)
  {
    ReducedIndex index = 0;
  STUBLOOP: for (int i=0; i<MAX_nSTUBS; ++i) {
#pragma HLS PIPELINE II=1
      if (i < nStubs) {
        // Extract stub parameters
        // Calculate reduced-format parameters.
        // Calculate routing parameters
        ReducedZ_Layer redZ;
        ReducedPhi_Layer redPhi;
        ReducedR_Layer redR;
        ReducedPt_Layer redPt;
        int routePhi;
        int routeZ;
	T currStub(stubsInLayer_[i]); // single read
#ifndef __SYNTHESIS
	std::cout << __func__ << ":" << __LINE__
		  << "-> " << currStub << std::endl;
#endif // SYNTHESIS
        if (Layer_==1 || Layer_==2 || Layer_==3) { // PS layers
          FullZ_Layer_PS curZ = currStub.GetZ();
          FullPhi_Layer_PS curPhi = currStub.GetPhi();
          FullR_Layer_PS curR = currStub.GetR();
          FullPt_Layer_PS curPt = currStub.GetPt();
	  std::cout << "curr values: " << curZ << ", " << curPhi << ", " << curR << ", " << curPt
		    << std::endl;
          redPt = curPt;
          redZ = curZ.range(5+3,5);
          redR = curR.range(5+1,5);
          routeZ = curZ[9];
          if (Layer_==2){
            redPhi = curPhi.range(9+2,9);
            //routePhi = (curPhi >> 12 ) & 0x3U;
            routePhi = curPhi(12+1,12);
          } else {
            redPhi = (curPhi >> 9) ^ 0x4U; // why is this OR'd?
            routePhi = (((curPhi >> 11) - 1) >> 1) & 0x3U;
          }
        }
        else if (Layer_==4 || Layer_==5 || Layer_==6) { // 2S layers
          FullZ_Layer_2S curZ = currStub.GetZ();
          FullPhi_Layer_2S curPhi = currStub.GetPhi();
          FullR_Layer_2S curR = currStub.GetR();
          FullPt_Layer_2S curPt = currStub.GetPt();
          redPt = curPt;
          redZ = curZ.range(3+1,1);
          redR = curR.range(1+6,6);
          routeZ = curZ[5];
          if (Layer_==5){
            redPhi = (curPhi >> 12) ^ 0x4U; // why is this an OR?
            routePhi = (((curPhi >> 14) - 1) >> 1) & 0x3U;
          } else {
            redPhi = curPhi.range(12+2,3);
            routePhi = curPhi.range(15+1,15);
          }
        }

        // Rewrite stub parameters to new stub in allStubs
        allStubs_[i].AddStub(currStub.raw());

	int cnt = n_[routeZ][routePhi];
	rVMStubs_[routeZ][routePhi][cnt].AddStub(redZ, redPhi, redR, redPt, index);
#ifndef __SYNTHESIS__
	std::cout << __func__ << ": " 
		  << "[" << routeZ << "][" << routePhi << "][" << cnt << "]: "
		  <<  rVMStubs_[routeZ][routePhi][cnt] << std::endl;
	n_[routeZ][routePhi] = cnt + 1;
	++index;  // below has protection for this to wrap?
#endif // SYNTHESIS
#if 0
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
#endif // if 0
      } // if nstubs
      else 
        break;
      } // for loop
    //std::cout << __func__ << ": " <<  rVMStubs_[0][0][1] << std::endl;

  } // end void execute()
};




