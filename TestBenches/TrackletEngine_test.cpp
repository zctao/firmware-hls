// ProjectionRouter test bench
#include "HLSTrackletEngine.h"
#include "StubPairs.hh"
#include "VMStubsTEInner.hh"
#include "VMStubsTEOuter.hh"
#include "hls_math.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

const int nevents = 1;  // number of events to run

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

template<class DataType>
void fillMemfromFile(DataType* memarray, ifstream& fin)
{

	string line;
	int ievent = -1;

	while (getline(fin, line)) {
		//cout << line << endl;

		if (line.find("Event") != string::npos) {
			//if (ievent >= 0) (memarray+ievent)->print_mem();

			ievent++;
		}
		else {
			assert(ievent >= 0);
			//cout << "line: "<<line<<endl;
			(memarray+ievent)->write_mem_line(ievent,line);
		}

		if (ievent >= nevents) break;
	}
}

template<class DataType, int depth>
void fillMem(DataType result_mem[depth], DataType* mem_ptr)
{
	for (int i = 0; i < depth; ++i) {
		result_mem[i] = *(mem_ptr+i);
	}
}

int main()
{
	// error counter
	int err_count = 0;

	// declare input memory arrays
	VMStubsTEInner inputvmstubsinner[nevents];
	VMStubsTEOuter inputvmstubsouter[nevents];

	// declare output memory arrays
	StubPairs outputstubpairs[nevents];


	/////////////////////////////////////
	// read input files
	ifstream fin_vmstubsinner;
	ifstream fin_vmstubsouter;

	fin_vmstubsinner.open("emData_TE/VMStubs_VMSTE_L1PHIE18n2_04.dat");
	fin_vmstubsouter.open("emData_TE/VMStubs_VMSTE_L2PHIC17n4_04.dat");
	if (!fin_vmstubsinner) {
		cerr << "Cannot open fin_vmstubsinner. Abort." << endl;
		return -1;
	}
	if (!fin_vmstubsouter) {
		cerr << "Cannot open fin_vmstubsouter. Abort." << endl;
		return -1;
	}

	// fill memories from files
	fillMemfromFile<VMStubsTEInner>(inputvmstubsinner, fin_vmstubsinner);
	fillMemfromFile<VMStubsTEOuter>(inputvmstubsouter, fin_vmstubsouter);

	// close files
	fin_vmstubsinner.close();
	fin_vmstubsouter.close();

	/////////////////////////////////////
	// emulation output to be compared with
	ifstream fout_stubpairs;
	fout_stubpairs.open("emData_TE/StubPairs_SP_L1PHIE18_L2PHIC17_04.dat");
	assert(fout_stubpairs.good());

	fillMemfromFile<StubPairs>(outputstubpairs, fout_stubpairs);

	fout_stubpairs.close();


	/////////////////////////////////////
	// loop over events
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Event: " << dec << ievt << endl;

		//cout << "Input:" << endl;
		if ((inputvmstubsinner+ievt)->getEntries(ievt) > 0) {
		  //cout << "inputvmstub: ";
		  //	(inputvmstubs+ievt)->print_mem();
		}
		if ((inputvmstubsouter+ievt)->getEntries(ievt) > 0) {
		  //cout << "inputvmproj: ";
		  //	(inputvmprojs+ievt)->print_mem();
		}

		// input data array
		// memories that are actually connected to the processing module
		VMStubTEInner vmstubsinner[kMemDepth];
		VMStubTEOuter vmstubsouter[kMemDepth];

		// fill input data arrays
		fillMem<VMStubTEInner, kMemDepth>(vmstubsinner, (inputvmstubsinner+ievt)->get_mem(ievt));
		fillMem<VMStubTEOuter, kMemDepth>(vmstubsouter, (inputvmstubsouter+ievt)->get_mem(ievt));

		// output memories that are actually connected to the processing module
		StubPair stubpairsout[kMemDepth];
		ap_uint<7> nstubpairs=0;

		// Unit Under Test
		// PR_L3L4_L1PHI3
		HLSTrackletEngine(
			       vmstubsinner,
			       vmstubsouter,
			       (inputvmstubsinner+ievt)->getEntries(ievt),
			       (inputvmstubsouter+ievt)->getEntries(ievt),
			       stubpairsout,
			       nstubpairs
				);

		// compare calculated outputs with those read from emulation printout
		// allprojections
		cout << "Number of stub pairs : "<<nstubpairs<<" "
		     <<(outputstubpairs+ievt)->getEntries(ievt)<<endl;

		if (nstubpairs!=(outputstubpairs+ievt)->getEntries(ievt)) {
		  cout << "ERROR: Number of stub pairs don't agree"<<endl;
		  err_count++;
		}
		for (int j = 0; j < nstubpairs; ++j) {
			assert(j < kMemDepth);
			StubPair stubpair_expected = (outputstubpairs+ievt)->read_mem(ievt,j);
			StubPair stubpair_computed = stubpairsout[j];
			if (stubpair_expected != stubpair_computed) {
			  cout << "ERROR: Expected and computed results are different for j="<<j << endl;
				err_count++;
			}
		}

	}  // end of event loop

	return err_count;
}
