#ifndef TRACKLETPROJECTIONS_HH
#define TRACKLETPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

struct TProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  TCID        tracklet_index;
  TProjPHI    phi;
  TProjZ      z;
  TProjPHIDER phider;
  TProjZDER   zder;
};

class TrackletProjections: public MemoryBase<TProjData, MemDepth>
{
public:
  
  TrackletProjections(){}

  TProjPHI    getphi(int i) const {return dataarray_[i].phi;}
  TProjZ      getz(int i) const {return dataarray_[i].z;}
  TProjPHIDER getphider(int i) const {return dataarray_[i].phider;}
  TProjZDER   getzder(int i) const {return dataarray_[i].zder;}
  TCID        gettcindex(int i) const {return dataarray_[i].tracklet_index;}

  void setphi(TProjPHI iphi, int i) {dataarray_[i].phi = iphi;}
  void setz(TProjZ iz, int i) {dataarray_[i].z = iz;}
  void setphider(TProjPHIDER iphider, int i) {dataarray_[i].phider = iphider;}
  void setzder(TProjZDER izder, int i) {dataarray_[i].zder = izder;}
  void settcindex(TCID itcid, int i) {dataarray_[i].tracklet_index = itcid;}
};

#endif
