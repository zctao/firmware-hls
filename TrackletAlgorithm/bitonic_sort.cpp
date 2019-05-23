#include "bitonic_sort.hpp"
#include "sorting_network.hpp"

#include "VMStubTEInnerMemory.hh"
#include "VMStubTEOuterMemory.hh"
#include "StubPairMemory.hh"

void bitonic_sort_array(ap_uint<14> (&data)[8]) {

#pragma HLS pipeline

	sorting_network(data);


}
