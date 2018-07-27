
#include "ap_int.h"

static const int TMUX = 6;
static const int nMaxProc = TMUX * 6;
static const int MemDepth = 64;

typedef ap_uint<10> TCID;

//TrackletProjections
typedef ap_uint<14> TProjPHI;
typedef ap_int<12> TProjZ;
typedef ap_int<7> TProjPHIDER;
typedef ap_int<8> TProjZDER;

// AllProjections
typedef ap_uint<14> AProjPHI;
typedef ap_int<12> AProjZ;
typedef ap_int<7> AProjPHIDER;
typedef ap_int<8> AProjZDER;

const int MEBinsBits = 3;

// VMProjections
typedef ap_uint<7> VMPID;
typedef ap_uint<3> VMPPHI;
typedef ap_uint<MEBinsBits+1> VMPZBIN;
