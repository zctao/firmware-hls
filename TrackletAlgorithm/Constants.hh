
#include "ap_int.h"

static const int MemDepth = 64;

typedef ap_uint<10> TCID;

//TrackletProjections
typedef ap_uint<14> TProjPHI;
typedef ap_uint<12> TProjZ;
typedef ap_uint<7> TProjPHIDER;
typedef ap_uint<8> TProjZDER;

// AllProjections
typedef ap_uint<14> AProjPHI;
typedef ap_uint<12> AProjZ;
typedef ap_uint<7> AProjPHIDER;
typedef ap_uint<8> AProjZDER;

// VMProjections
typedef ap_uint<7> VMPID;
typedef ap_uint<3> VMPPHI;
typedef ap_uint<4> VMPZBIN;
