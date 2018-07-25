#ifndef VMPROJECTIONS_HH
#define VMPROJECTIONS_HH

#include "Constants.hh"
#include "MemoryBase.hh"

struct VMProjData {
  VMPID   index;
  VMPPHI  vmphi;
  VMPZBIN zbin;
};

class VMProjections: public MemoryBase<VMProjData, MemDepth>
{
public:
  
  VMProjections(){}

};

#endif
