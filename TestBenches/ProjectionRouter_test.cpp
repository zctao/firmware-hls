// ProjectionRouter test bench
#include "HLSProjectionRouter.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

const int nevents = 100;  // number of events to run

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

bool openFile(ifstream& file, const char* filename)
{
	file.open(filename);
	if (!file) {
		cerr << "Cannot open " << filename << ". Abort." << endl;
		return false;
	}

	return true;
}

template<class MemType>
void readEventFromFile(MemType& memory, ifstream& fin, int ievt,
					   int base = 16)
// Cf. https://github.com/cms-tracklet/firmware-hls/blob/matchengine/TestBenches/FileReadUtility.hh#L10
{
	string line;

	if (ievt==0) {
		getline(fin, line);
	}

	memory.clear();

	while (getline(fin, line)) {

		if (!fin.good()) {
			return;
		}

		if (line.find("Event") != string::npos) {
			return;
		}
		else {
			const string datastr = split(line, ' ').back();
			memory.write_mem(ievt, datastr.c_str(), base);
		}
		
	}
}

int main()
{
	// error counts
	int err = 0;
	
	// input memories
	static TrackletProjectionMemory tproj1;
	static TrackletProjectionMemory tproj2;
	static TrackletProjectionMemory tproj3;
	static TrackletProjectionMemory tproj4;
	static TrackletProjectionMemory tproj5;
	static TrackletProjectionMemory tproj6;
	static TrackletProjectionMemory tproj7;
	static TrackletProjectionMemory tproj8;

	// output memories
	static AllProjectionMemory allproj;
	static VMProjectionMemory vmproj1;
	static VMProjectionMemory vmproj2;
	static VMProjectionMemory vmproj3;
	static VMProjectionMemory vmproj4;

	// open input files
	ifstream fin_tproj1("emData_PR/TrackletProjections_TPROJ_L3L4C_L1PHI3_04.dat");
	ifstream fin_tproj2("emData_PR/TrackletProjections_TPROJ_L3L4D_L1PHI3_04.dat");
	ifstream fin_tproj3("emData_PR/TrackletProjections_TPROJ_L3L4E_L1PHI3_04.dat");
	ifstream fin_tproj4("emData_PR/TrackletProjections_TPROJ_L3L4F_L1PHI3_04.dat");
	ifstream fin_tproj5("emData_PR/TrackletProjections_TPROJ_D1L2B_L1PHI3_04.dat");
	ifstream fin_tproj6("emData_PR/TrackletProjections_TPROJ_L3L4_L1PHI3FromPlus_04.dat");

	assert(fin_tproj1.good());
	assert(fin_tproj2.good());
	assert(fin_tproj3.good());
	assert(fin_tproj4.good());
	assert(fin_tproj5.good());
	assert(fin_tproj6.good());

	// loop over events
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Event: " << dec << ievt << endl;

		// read next event
		readEventFromFile<TrackletProjectionMemory>(tproj1, fin_tproj1, ievt);
		readEventFromFile<TrackletProjectionMemory>(tproj2, fin_tproj2, ievt);
		readEventFromFile<TrackletProjectionMemory>(tproj3, fin_tproj3, ievt);
		readEventFromFile<TrackletProjectionMemory>(tproj4, fin_tproj4, ievt);
		readEventFromFile<TrackletProjectionMemory>(tproj5, fin_tproj5, ievt);
		readEventFromFile<TrackletProjectionMemory>(tproj6, fin_tproj6, ievt);

		// bx
		ap_uint<3> bx = ievt&0x7;
		ap_uint<3> bx_out;

		// Unit Under Test
		HLSProjectionRouter(bx,
							tproj1, tproj2, tproj3, tproj4,
							tproj5, tproj6, tproj7, tproj8,
							bx_out,
							allproj,
							vmproj1, vmproj2, vmproj3, vmproj4
							);

		// dump output
		if (allproj.getEntries(bx)) {
			cout << "AllProjection:" << endl;
			allproj.print_mem(bx);
		}
		if (vmproj1.getEntries(bx)) {
			cout << "VMProjection1:" << endl;
			vmproj1.print_mem(bx);
		}
		if (vmproj2.getEntries(bx)) {
			cout << "VMProjection2:" << endl;
			vmproj2.print_mem(bx);
		}
		if (vmproj3.getEntries(bx)) {
			cout << "VMProjection3:" << endl;
			vmproj3.print_mem(bx);
		}
		if (vmproj4.getEntries(bx)) {
			cout << "VMProjection4:" << endl;
			vmproj4.print_mem(bx);
		}
		
		// todo
		// compare outputs
		
	} // end event loop

	return err;
}





