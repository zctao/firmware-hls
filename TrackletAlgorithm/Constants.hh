// This header file defines the Global constants used in VMRouter
#pragma once
#include "ap_int.h"


// Define max number of stubs an individual module can take
constexpr int MAX_nSTUBS = 64;
constexpr int MAX_nSECTORS = 1;
constexpr int MAX_nINNERRS = 3;
constexpr int MAX_nOUTERRS = 3;
constexpr int MAX_nREGIONS = 6;
constexpr int MAX_nEVENTS = 100;

// Raw Stub Data
typedef ap_uint<36> StubData;




