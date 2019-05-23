#include "swap.hpp"



void swap1(ap_uint<14> &data1, ap_uint<14> &data2) {
  //	if (data1 < data2) {
  if (data1 > data2) {
    std::swap(data1, data2);
	}
}

void swap2(ap_uint<14> &data1, ap_uint<14> &data2) {
  //	if (data1 > data2) {
  if (data1 < data2) {
    std::swap(data1, data2);
	}
}
