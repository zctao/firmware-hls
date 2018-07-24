#ifndef TRACKLETPROJECTIONS_HH
#define TRACKLETPROJECTIONS_HH

#include "Constants.hh"
//#include "MemoryBase.hh"

struct TProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  TCID        tracklet_index;
  TProjPHI    phi;
  TProjZ      z;
  TProjPHIDER phider;
  TProjZDER   zder;
};

class TrackletProjections //:pulic MemoryBase<TProjData>
{
public:
  
  TrackletProjections(){}
  ~TrackletProjections(){}
  
  TProjData* getTProj() const {return trackletproj_;}
  // or ?
  //TProjData  getTProj(int i) const {return trackletproj_[i];}

  TProjPHI    getphi(int i) const {return trackletproj_[i].phi;}
  TProjZ      getz(int i) const {return trackletproj_[i].z;}
  TProjPHIDER getphider(int i) const {return trackletproj_[i].phider;}
  TProjZDER   getzder(int i) const {return trackletproj_[i].zder;}
  TCID        gettcindex(int i) const {return trackletproj_[i].tracklet_index;}

  void setTProj(TProjData tproj, int i) {trackletproj_[i] = tproj;}
  void setphi(TprojPHI iphi, int i) {trackletproj_[i].phi = iphi;}
  void setz(TProjZ iz, int i) {trackletproj_[i].z = iz;}
  void setphider(TprojPHIDER iphider, int i) {trackletproj_[i].phider = iphider;}
  void setzder(TProjZDER izder, int i) {trackletproj_[i].zder = izder;}
  void settcindex(TCID itcid, int i) {tracklet_[i].tracklet_index = itcid;}
  

private:

  TProjData trackletproj_[MemDepth];

};

#endif
