// ProjectionRouter test bench
#include "HLSMatchEngine.h"
#include "CandidateMatches.hh"
#include "VMStubs.hh"
#include "VMProjections.hh"
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
	VMStubs inputvmstubs[nevents];
	VMProjections inputvmprojs[nevents];

	// declare output memory arrays
	CandidateMatches outputcandmatches[nevents];


	/////////////////////////////////////
	// read input files
	ifstream fin_vmstub;
	ifstream fin_vmproj;

	fin_vmstub.open("emData_ME/VMStubs_VMSME_L1PHIE20n1_04.dat");
	fin_vmproj.open("emData_ME/VMProjections_VMPROJ_L1PHIE20_04.dat");
	if (!fin_vmstub) {
		cerr << "Cannot open fin_vmstub. Abort." << endl;
		return -1;
	}
	if (!fin_vmproj) {
		cerr << "Cannot open fin_vmproj. Abort." << endl;
		return -1;
	}

	// fill memories from files
	fillMemfromFile<VMStubs>(inputvmstubs, fin_vmstub);
	fillMemfromFile<VMProjections>(inputvmprojs, fin_vmproj);

	// close files
	fin_vmstub.close();
	fin_vmproj.close();

	/////////////////////////////////////
	// emulation output to be compared with
	ifstream fout_candmatch;
	fout_candmatch.open("emData_ME/CandidateMatches_CM_L1PHIE20_04.dat");


	fillMemfromFile<CandidateMatches>(outputcandmatches, fout_candmatch);

	fout_candmatch.close();


	/////////////////////////////////////
	// loop over events
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Event: " << dec << ievt << endl;

		// input data array
		// memories that are actually connected to the processing module
		VMStub vmstubin[kMemDepth];
		VMProj vmprojin[kMemDepth];

		// fill input data arrays
		fillMem<VMStub, kMemDepth>(vmstubin, (inputvmstubs+ievt)->get_mem(ievt));
		fillMem<VMProj, kMemDepth>(vmprojin, (inputvmprojs+ievt)->get_mem(ievt));

		// output memories that are actually connected to the processing module
		CandidateMatch candmatchout[kMemDepth];
		ap_uint<7> ncandmatch=0;

		ap_uint<4> binentries[8];
		(inputvmstubs+ievt)->getEntries(ievt,binentries);

		// Unit Under Test
		// PR_L3L4_L1PHI3
		HLSMatchEngine(
			       vmstubin,
			       vmprojin,
			       binentries,
			       (inputvmprojs+ievt)->getEntries(ievt),
			       candmatchout,
			       ncandmatch
				);

		// compare calculated outputs with those read from emulation printout
		// allprojections
		cout << "Number of candidate matches : "<<ncandmatch<<" "
		     <<(outputcandmatches+ievt)->getEntries(ievt)<<endl;
		for (int j = 0; j < ncandmatch; ++j) {
			assert(j < kMemDepth);
			//if (j==0) cout << "candmatches: " << endl;
			CandidateMatch candmatch_expected = (outputcandmatches+ievt)->read_mem(ievt,j);
			CandidateMatch candmatch_computed = candmatchout[j];
			//cout << candmatch_expected << " " << candmatch_computed << endl;
			if (candmatch_expected != candmatch_computed) {
			  cout << "ERROR! Expected and computed results are different for j="<<j << endl;
				err_count++;
			}
		}

	}  // end of event loop

	return err_count;
}
