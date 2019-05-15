#include "topfunction.hh"

#include <algorithm>

int main()
{
  using namespace std;

  // error count
  int err = 0;

  // input array;
  int inarray1[2][16] = {{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53},
                            {3,4,6,8,12,14,18,20,24,30,32,38,42,44,48,54}};
  int inarray2[2][16] = {{1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31},
                           {2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32}};
  
  // output array
  int outarray[2][16];
  
  ap_uint<2> bx_o;

  cout << "Start event loop" << endl;
  for (unsigned int ievt = 0; ievt < 5; ++ievt) {
    cout << "Event: " << ievt << endl;

    // call top function
    topfunction(ievt, bx_o, inarray1, inarray2, outarray);
    //topfunction(ievt, bx_o, inarray1[ievt%2], inarray2[ievt%2], outarray[ievt%2]);
  
    // verify output
    for (int i = 0; i<16; ++i) {
      int din1 = inarray1[ievt%2][i] * 2;
      int din2 = inarray2[ievt%2][i] * 2;
      int outref = (din1 > din2) ? din1 : din2;
      
      int outcal = outarray[ievt%2][i];
      
      if (outref != outcal) err++;
    }
  }

  return err;
}
