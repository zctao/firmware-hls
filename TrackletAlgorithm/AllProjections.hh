#ifndef ALLPROJECTIONS_HH
#define ALLPROJECTIONS_HH

#include "Constants.hh"

struct AllProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  TCID        tracklet_index;
  AProjPHI    phi;
  AProjZ      zder;
  AProjPHIDER phider;
  AProjZDER   zder;
};

class AllProjections
{
public:

  AllProjections(){}
  ~AllProjections(){}

  // getter
  AllProjData* getAllProj() const {return allproj_;}
  //AllProjPHI getphi();

  // setter
  void setAllProj(AllProjData aproj, int i) {allproj_[i] = aproj;}
  //void setAllProj();

private:

  AllProjData allproj_[MemDepth];

}

#endif
