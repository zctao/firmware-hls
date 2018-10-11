#include "MergerTest.h"
#include <iostream>

using namespace std;

/*
template<class DataT>
DataT merge(hls::stream<DataT>& input1, hls::stream<DataT>& input2)
{
	
}
*/

void MergerTest(unsigned int inmem1[8], unsigned int inmem2[8],
				unsigned int inmem3[8], unsigned int inmem4[8],
				unsigned int numin1, unsigned int numin2,
				unsigned int numin3, unsigned int numin4, 
				hls::stream<unsigned int>& mergedStream)
{
	unsigned int read_addr1 = 0, read_addr2 = 0, read_addr3 = 0, read_addr4 = 0;

	unsigned int dataout = -1;

	cout << "MergerTest" << endl;
	
	for (int i = 0; i < 36; ++i) { 
		
#pragma HLS PIPELINE II=1

		cout << "loop iteration : " << i << endl;
		cout << "read addresses : " << read_addr1 << " " << read_addr2 << " ";
		cout << read_addr3 << " " << read_addr4 << endl;
		
		unsigned int data1 = (read_addr1 < numin1) ? inmem1[read_addr1] : -1;
		unsigned int data2 = (read_addr2 < numin2) ? inmem2[read_addr2] : -1;
		unsigned int data3 = (read_addr3 < numin3) ? inmem3[read_addr3] : -1;
		unsigned int data4 = (read_addr4 < numin4) ? inmem4[read_addr4] : -1;

		cout << "in data : " << data1 << " " << data2 << " " << data3 << " " << data4 << endl;
		
		if (data1 <= data2 and data1 <= data3 and data1 <= data4) {
			dataout = data1;
			read_addr1++;
		}
		else if (data2 <= data1 and data2 <= data3 and data2 <= data4) {
			dataout = data2;
			read_addr2++;
		}
		else if (data3 <= data1 and data3 <=  data2 and data3 <= data4) {
			dataout = data3;
			read_addr3++;
		}
		else {
			dataout = data4;
			read_addr4++;
		}

		cout << "data out : " << dataout << endl;
		
	    mergedStream.write_nb(dataout); 
	}
}
