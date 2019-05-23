#include "swap.hpp"

void block2_step1_net(ap_uint<14> datas[8]) {
#pragma HLS PIPELINE
	swap2(datas[0], datas[1]);
	swap1(datas[2], datas[3]);
	swap2(datas[4], datas[5]);
	swap1(datas[6], datas[7]);
}

void block4_step2_net(ap_uint<14> datas[8]) {
#pragma HLS PIPELINE
	swap2(datas[0], datas[2]);
	swap2(datas[1], datas[3]);
	swap1(datas[4], datas[6]);
	swap1(datas[5], datas[7]);
}

void block4_step1_net(ap_uint<14> datas[8]) {
#pragma HLS PIPELINE
	swap2(datas[0], datas[1]);
	swap2(datas[2], datas[3]);
	swap1(datas[4], datas[5]);
	swap1(datas[6], datas[7]);
}

void block8_step4_net(ap_uint<14> datas[8]) {
#pragma HLS PIPELINE
	swap2(datas[0], datas[4]);
	swap2(datas[1], datas[5]);
	swap2(datas[2], datas[6]);
	swap2(datas[3], datas[7]);
}

void block8_step2_net(ap_uint<14> datas[8]) {
#pragma HLS PIPELINE
	swap2(datas[0], datas[2]);
	swap2(datas[1], datas[3]);
	swap2(datas[4], datas[6]);
	swap2(datas[5], datas[7]);
}

void block8_step1_net(ap_uint<14> datas[8]) {
#pragma HLS PIPELINE
	swap2(datas[0], datas[1]);
	swap2(datas[2], datas[3]);
	swap2(datas[4], datas[5]);
	swap2(datas[6], datas[7]);
}


void sorting_network(ap_uint<14> datas[8]) {
#pragma HLS pipeline II=1 

	block2_step1_net(datas);
	block4_step2_net(datas);
	block4_step1_net(datas);
	block8_step4_net(datas);
	block8_step2_net(datas);
	block8_step1_net(datas);
}
