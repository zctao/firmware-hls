#ifndef __BITONIC_SORT_HPP__
#define __BITONIC_SORT_HPP__

// avoid Cosim Error
//#include "/opt/Xilinx/Vivado/2018.2/include/gmp.h"
//#include "/opt/Xilinx/Vivado/2018.2/include/mpfr.h"
#include "/home/xilinx/Vivado/2018.2/include/gmp.h"
#include "/home/xilinx/Vivado/2018.2/include/mpfr.h"

#include "ap_int.h"
#include "hls_stream.h"


#define DATA_SIZE 8
#define DATA_W 14

//void bitonic_sort(hls::stream<ap_int<DATA_W> > axis_in[], hls::stream<ap_int<DATA_W> > axis_out[]);
void bitonic_sort_array(ap_uint<14>  (&data)[8]);


#endif
