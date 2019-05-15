#include "topfunction.hh"

void processA(ap_uint<2> bx, ap_uint<2>& bx_o, int in1[2][16], int in2[2][16], int out1[2][16], int out2[2][16]);
void processB(ap_uint<2> bx, ap_uint<2>& bx_o, int in[2][16], int out[2][16]);
void processC(ap_uint<2> bx, ap_uint<2>& bx_o, int in1[2][16], int in2[4][16], int out[2][16]);

void topfunction(ap_uint<2> bx, ap_uint<2>& bx_o,
                 int inputmem1[2][16], int inputmem2[2][16],
                 int outputmem[2][16])
{
//#pragma HLS DATAFLOW
#pragma HLS pipeline II=16

#pragma HLS RESOURCE variable=inputmem1 core=RAM_S2P_BRAM
#pragma HLS RESOURCE variable=inputmem2 core=RAM_S2P_BRAM
#pragma HLS RESOURCE variable=outputmem core=RAM_S2P_BRAM
  //std::cout << "bx " << bx << std::endl;

  //#pragma HLS function_instantiate variable=bx

  int memoryAB[2][16];
#pragma HLS RESOURCE variable=memoryAB core=RAM_S2P_BRAM
#pragma HLS DEPENDENCE variable=memoryAB array false

  int memoryAC[4][16];
#pragma HLS RESOURCE variable=memoryAC core=RAM_S2P_BRAM
#pragma HLS DEPENDENCE variable=memoryAC array false

  int memoryBC[2][16];
#pragma HLS RESOURCE variable=memoryBC core=RAM_S2P_BRAM
#pragma HLS DEPENDENCE variable=memoryBC array false
  //int memoryBC2[2][16];
//#pragma HLS RESOURCE variable=memoryBC2 core=RAM_S2P_BRAM

  ap_uint<2> bx_AB;
//#pragma HLS STREAM variable=bx_AB dim=1
  ap_uint<2> bx_BC;
//#pragma HLS STREAM variable=bx_BC dim=1

  processA(bx, bx_AB, inputmem1, inputmem2, memoryAB, memoryAC);

  processB(bx_AB, bx_BC, memoryAB, memoryBC);
  //processB(bx_AB, bx_BC, memoryAB2, memoryBC2);

  processC(bx_BC, bx_o, memoryBC, memoryAC, outputmem);

}

void processA(ap_uint<2> bx, ap_uint<2>& bx_o,
              int inmem1[2][16], int inmem2[2][16],
              int outmem1[2][16], int outmem2[4][16])
{
#pragma HLS inline off
#pragma HLS interface register port=bx_o

  for (int i = 0; i < 16; ++i) {
#pragma HLS pipeline II=1 rewind
    // read input memories
    int indata1 = inmem1[bx(0,0)][i];
    int indata2 = inmem2[bx(0,0)][i];

    // copy data
    int outdataA = indata1;

    int outdataB = indata2 * 2;

    // write to output
    outmem1[bx(0,0)][i] = outdataA;
    outmem2[bx][i] = outdataB;

    bx_o = bx;
  }
}

void processB(ap_uint<2> bx, ap_uint<2>& bx_o,
              int inmem[2][16], int outmem[2][16])
{
#pragma HLS inline off
#pragma HLS interface register port=bx_o

  for (int i = 0; i < 16; ++i) {
#pragma HLS pipeline II=1 rewind
    // read input memories
    int indata = inmem[bx(0,0)][i];

    // multiple by 2
    int outdata = indata * 2;

    // write to output
    outmem[bx(0,0)][i] = outdata;

    bx_o = bx;
  }
}

void processC(ap_uint<2> bx, ap_uint<2>& bx_o,
              int inmem1[2][16], int inmem2[4][16],
              int outmem[2][16])
{
#pragma HLS inline off
#pragma HLS interface register port=bx_o

  for (int i = 0; i < 16; ++i) {
#pragma HLS pipeline II=1 rewind
    // read input memories
    int indata1 = inmem1[bx(0,0)][i];
    int indata2 = inmem2[bx][i];

    // compare data and store the larger one
    bool islarger = indata1 > indata2;
    int outdata = islarger ? indata1 : indata2;

    // write to output memory
    outmem[bx(0,0)][i] = outdata;

    bx_o = bx;
  }
}

/*
void processA(ap_uint<2> bx, ap_uint<2>& bx_o, int in1[16], int in2[16], int out1[16], int out2[16]);
void processB(ap_uint<2> bx, ap_uint<2>& bx_o, int in[16], int out[16]);
void processC(ap_uint<2> bx, ap_uint<2>& bx_o, int in1[16], int in2[16], int out[16]);

void topfunction(ap_uint<2> bx, ap_uint<2>& bx_o,
                 int inputmem1[16], int inputmem2[16],
                 int outputmem[16])
{
#pragma HLS DATAFLOW
//#pragma HLS pipeline II=16

#pragma HLS RESOURCE variable=inputmem1 core=RAM_S2P_BRAM
#pragma HLS RESOURCE variable=inputmem2 core=RAM_S2P_BRAM
#pragma HLS RESOURCE variable=outputmem core=RAM_S2P_BRAM
  //std::cout << "bx " << bx << std::endl;
  
  //#pragma HLS function_instantiate variable=bx

  int memoryAB[16];
#pragma HLS RESOURCE variable=memoryAB1 core=RAM_S2P_BRAM
  int memoryAC[16];
#pragma HLS RESOURCE variable=memoryAB2 core=RAM_S2P_BRAM

  int memoryBC[16];
#pragma HLS RESOURCE variable=memoryBC1 core=RAM_S2P_BRAM
  //int memoryBC2[16];
//#pragma HLS RESOURCE variable=memoryBC2 core=RAM_S2P_BRAM

  ap_uint<2> bx_AB;
  ap_uint<2> bx_BC;

  processA(bx, bx_AB, inputmem1, inputmem2, memoryAB, memoryAC);
  
  processB(bx_AB, bx_BC, memoryAB, memoryBC);
  //processB(bx_AB, bx_BC, memoryAB2, memoryBC2);
  
  processC(bx_BC, bx_o, memoryBC, memoryAC, outputmem);
  
}

void processA(ap_uint<2> bx, ap_uint<2>& bx_o,
              int inmem1[16], int inmem2[16],
              int outmem1[16], int outmem2[16])
{
#pragma HLS inline off
  for (int i = 0; i < 16; ++i) {
#pragma HLS pipeline II=1 rewind
    // read input memories
    int indata1 = inmem1[i];
    int indata2 = inmem2[i];
    
    // copy data
    int outdataA = indata1;

    int outdataB = indata2 * 2;

    // write to output
    outmem1[i] = outdataA;
    outmem2[i] = outdataB;

    bx_o = bx;
  }
}

void processB(ap_uint<2> bx, ap_uint<2>& bx_o,
              int inmem[16], int outmem[16])
{
#pragma HLS inline off
  for (int i = 0; i < 16; ++i) {
#pragma HLS pipeline II=1 rewind
    // read input memories
    int indata = inmem[i];

    // multiple by 2
    int outdata = indata * 2;

    // write to output
    outmem[i] = outdata;

    bx_o = bx;
  }
}

void processC(ap_uint<2> bx, ap_uint<2>& bx_o,
              int inmem1[16], int inmem2[16],
              int outmem[16])
{
#pragma HLS inline off
  for (int i = 0; i < 16; ++i) {
#pragma HLS pipeline II=1 rewind
    // read input memories
    int indata1 = inmem1[i];
    int indata2 = inmem2[i];

    // compare data and store the larger one
    bool islarger = indata1 > indata2;
    int outdata = islarger ? indata1 : indata2;

    // write to output memory
    outmem[i] = outdata;

    bx_o = bx;
  }
}
*/
