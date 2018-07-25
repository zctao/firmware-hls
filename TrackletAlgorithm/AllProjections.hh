#ifndef ALLPROJECTIONS_HH
#define ALLPROJECTIONS_HH

#include "Constants.hh"

struct AllProjData {
  bool        plusNeighbor;
  bool        minusNeighbor;
  TCID        tracklet_index;
  AProjPHI    phi;
  AProjZ      z;
  AProjPHIDER phider;
  AProjZDER   zder;
};

class AllProjections: public MemoryBase<AllProjData, MemDepth>
{
public:

  AllProjections(){}

}

#endif
