#ifndef CONSTANTS_HH
#define CONSTANTS_HH

#include "ap_int.h"

//#include <cmath>
//#include "hls_math.h"

static const int TMUX = 6;
static const int nMaxProc = TMUX * 6;

static const int NBits_MemAddr = 6;
static const int MemDepth = (1<<NBits_MemAddr);

const int MEBinsBits = 3;

#endif
