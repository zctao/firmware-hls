#ifndef VMSTUBSMEOUTER_HH
#define VMSTUBSMEOUTER_HH

#include "Constants.hh"
#include "MemoryBaseBinned.hh"

typedef ap_uint<7> VMPID;
typedef ap_uint<4> VMPFINEZ;
typedef ap_uint<3> VMBEND;
typedef ap_uint<7+4+3> VMStubMEOuter;


//template<unsigned int bx=2, unsigned int memdepth=kMemDepth>
class VMStubsMEOuter: public MemoryBaseBinned<VMStubMEOuter, 2, kMemDepth>
{
public:

  static VMPID get_index(const VMStubMEOuter data) {return data.range(13,7);}
  static VMPFINEZ get_finez(const VMStubMEOuter data) {return data.range(3,0);}
  static VMPBEND get_bend(const VMSTubMEOuter data) {return data.range(6,4);}

#ifndef __SYNTHESIS__
#include <iostream>

#endif

};

#endif
