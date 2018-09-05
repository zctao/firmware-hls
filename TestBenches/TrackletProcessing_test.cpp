// test bench
#include "TrackletProcessing.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

const int nevents = 20;  // number of events to run

using namespace std;

vector<string> split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream sstream(s);
	while (getline(sstream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

template<class T>
T parseLineMemPrints(const string& line, int base)
{
    const string datastr = split(line, ' ').back();
	// cout << datastr << endl;
	T data(datastr.c_str(), base);

	return data;
}

bool openFile(ifstream& file, const char* filename)
{
	file.open(filename);
	if (!file) {
		cerr << "Cannot open " << filename << ". Abort." << endl;
		return false;
	}

	return true;
}

template<class T>
void fillStreamFromFile(hls::stream<T> (&streams)[nevents], const char* filename,
						int base = 16)
{
	ifstream fin;
	bool validin = openFile(fin, filename);
	assert(validin);

	string line;
	int ievent = -1;

	while (getline(fin, line)) {
		//cout << line << endl;
		if (line.find("Event") != string::npos)
			ievent++;
		else {
			assert(ievent >= 0);
			T data = parseLineMemPrints<T>(line, base);
			streams[ievent].write(data);
		}

		if (ievent >= nevents) break;
	} // end of while

	fin.close();
}


template<class T>
int compareStreamWithFile(hls::stream<T> (&streams)[nevents], const char* filename,
						  int base = 16)
{
	int err_cnt = 0;
	
	ifstream fin;
	bool validin = openFile(fin, filename);
	assert(validin);

	string line;
	int ievent = -1;

	while(getline(fin, line)) {
		//cout << line << endl;
		if (line.find("Event") != string::npos)
			ievent++;
		else {
			assert(ievent >= 0);
			// compare data read from file with that in stream
			T data_expected = parseLineMemPrints<T>(line, base);	
			T data_computed = streams[ievent].read();

			cout << data_expected << " " << data_computed << endl;
			
			if (data_expected != data_computed) {
				cout << "ERROR! Expected and computed results are different!" << endl;
				err_cnt++;
			}
		}
	} // end of while

	fin.close();

	return err_cnt;
}

int main()
{
	/////////////////////////////////////
	// Containers for inputs
	hls::stream<TProj> inputtproj1[nevents];
	hls::stream<TProj> inputtproj2[nevents];
	hls::stream<TProj> inputtproj3[nevents];
	hls::stream<TProj> inputtproj4[nevents];
	hls::stream<TProj> inputtproj5[nevents];
	hls::stream<TProj> inputtproj6[nevents];
	
	// read input files and fill input streams
	fillStreamFromFile<TProj>(inputtproj1, "emData_PR/TrackletProjections_TPROJ_L3L4C_L1PHI3_04.dat");
	fillStreamFromFile<TProj>(inputtproj2, "emData_PR/TrackletProjections_TPROJ_L3L4D_L1PHI3_04.dat");
	fillStreamFromFile<TProj>(inputtproj3, "emData_PR/TrackletProjections_TPROJ_L3L4E_L1PHI3_04.dat");
	fillStreamFromFile<TProj>(inputtproj4, "emData_PR/TrackletProjections_TPROJ_L3L4F_L1PHI3_04.dat");
	fillStreamFromFile<TProj>(inputtproj5, "emData_PR/TrackletProjections_TPROJ_D1L2B_L1PHI3_04.dat");
	fillStreamFromFile<TProj>(inputtproj6, "emData_PR/TrackletProjections_TPROJ_L3L4_L1PHI3FromPlus_04.dat");

	/////////////////////////////////////
	// Containers for outputs
	hls::stream<AllProj> outputallproj[nevents];
	hls::stream<VMProj> outputvmproj9[nevents];
	hls::stream<VMProj> outputvmproj10[nevents];
	hls::stream<VMProj> outputvmproj11[nevents];
	hls::stream<VMProj> outputvmproj12[nevents];

	/////////////////////////////////////
	// loop over events
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Event: " << dec << ievt << endl;

		ap_uint<3> ibx = ievt;
		ap_uint<3> obx;
		
		hls::stream<TProj>* inprojs[6] = {
			inputtproj1+ievt, inputtproj2+ievt, inputtproj3+ievt,
			inputtproj4+ievt, inputtproj5+ievt, inputtproj6+ievt
		};

		hls::stream<VMProj>* outvmprojs[4] = {
			outputvmproj9+ievt, outputvmproj10+ievt,
			outputvmproj11+ievt, outputvmproj12+ievt
		};
		
		// Unit Under Test
		// PR_L3L4_L1PHI3
		TrackletProcessing(ibx, inprojs,
						   obx, outputallproj+ievt, outvmprojs);

	}  // end of event loop

	// Compare calculated outputs with those read from emulation printout
	// error counter
	int err_count = 0;
	
    cout << "allprojections: " << endl;
	err_count += compareStreamWithFile<AllProj>(outputallproj, "emData_PR/AllProj_AP_L3L4_L1PHI3_04.dat");

	cout << "vmproj9: " << endl;
	err_count += compareStreamWithFile<VMProj>(outputvmproj9, "emData_PR/VMProjections_VMPROJ_L3L4_L1PHI9_04.dat");

	cout << "vmproj10: " << endl;
	err_count += compareStreamWithFile<VMProj>(outputvmproj10, "emData_PR/VMProjections_VMPROJ_L3L4_L1PHI10_04.dat");

	cout << "vmproj11: " << endl;
	err_count += compareStreamWithFile<VMProj>(outputvmproj11, "emData_PR/VMProjections_VMPROJ_L3L4_L1PHI11_04.dat");

	cout << "vmproj12: " << endl;
	err_count += compareStreamWithFile<VMProj>(outputvmproj12, "emData_PR/VMProjections_VMPROJ_L3L4_L1PHI12_04.dat");

	return err_count;
}
