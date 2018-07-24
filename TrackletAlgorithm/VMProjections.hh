#ifndef VMPROJECTIONS_HH
#define VMPROJECTIONS_HH

#include "Constants.hh"

struct VMProjData {
  VMPID   index;
  VMPPHI  vmphi;
  VMPZBIN zbin;
};

class VMProjections
{
public:
  
  VMProjections(){}
  ~VMProjections(){}

  VMProjData* getVMProj() const {return vmproj_;}

  void setVMProj(VMProjData ivmproj, int i) {vmproj_[i] = ivmproj;}

private:

  VMProjData vmproj_[MemDepth];

};

#endif
