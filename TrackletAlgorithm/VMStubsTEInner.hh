#ifndef VMSTUBSMEINNER_HH
#define VMSTUBSMEINNER_HH

#include "Constants.hh"
#include "MemoryBase.hh"

typedef ap_uint<7> VMPID;
typedef ap_uint<MEBinsBits+1> VMPZBIN;
typedef ap_uint<4> VMPFINEZ;
typedef ap_uint<5> VMPBEND;
typedef ap_uint<7+MEBinsBits+1+4+5+1> VMStubMEInner;

class VMStubsMEInner: public MemoryBase<VMStubMEInner, 2, kMemDepth>
{
public:

  static VMPID get_index(const VMStubMEInner data) {return data.range(20,14);}
  static VMPZBIN get_zbin(const VMStubMEInner data) {return data.range(13,10);}
  static VMPFINEZ get_finez(const VMStubMEInner data) {return data.range(9,6);}
  static VMPBEND get_bend(const VMStubMEInner data) {return data.range(5,1);}
  static bool get_PSseed(const VMStubMEInner data) {return data.range(0,0);}



#ifndef __SYNTHESIS__
#include <iostream>


#endif

};

#endif
