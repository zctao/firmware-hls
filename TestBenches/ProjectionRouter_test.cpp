// ProjectionRouter test bench
#include "HLSProjectionRouter.h"
//#include "ProjectionRouter.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

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
void fillMemFromFile(MemType (&memarray)[nevents], const char* filename,
					 int base = 16)
{

	ifstream fin;
	bool validin = openFile(fin, filename);
	assert(validin);

	string line;
	int ievent = -1;

	cout << filename << endl;
	
	while (getline(fin, line)) {
		//cout << line << endl;
		if (line.find("Event") != string::npos) {
			ievent++;
		}
		else {
			assert(ievent >= 0);

			string datastr = split(line, ' ').back();
			//cout << datastr << endl;
			memarray[ievent]->write_mem(ievent, datastr.c_str());
		}

		if (ievent >= nevents) break;
	}

	fin.close();
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

	/////////////////////////////////////
	// declare input memory arrays
	TrackletProjections inputtproj1[nevents];
	TrackletProjections inputtproj2[nevents];
	TrackletProjections inputtproj3[nevents];
	TrackletProjections inputtproj4[nevents];
	TrackletProjections inputtproj5[nevents];
	TrackletProjections inputtproj6[nevents];

	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "Read input files and fill input memories" << endl;
	fillMemFromFile<TrackletProjections>(inputtproj1,"emData_PR/TrackletProjections_TPROJ_L3L4C_L1PHI3_04.dat");
	fillMemFromFile<TrackletProjections>(inputtproj2,"emData_PR/TrackletProjections_TPROJ_L3L4D_L1PHI3_04.dat");
	fillMemFromFile<TrackletProjections>(inputtproj3,"emData_PR/TrackletProjections_TPROJ_L3L4E_L1PHI3_04.dat");
	fillMemFromFile<TrackletProjections>(inputtproj4,"emData_PR/TrackletProjections_TPROJ_L3L4F_L1PHI3_04.dat");
	fillMemFromFile<TrackletProjections>(inputtproj5,"emData_PR/TrackletProjections_TPROJ_D1L2B_L1PHI3_04.dat");
	fillMemFromFile<TrackletProjections>(inputtproj6,"emData_PR/TrackletProjections_TPROJ_L3L4_L1PHI3FromPlus_04.dat");

	
	/////////////////////////////////////
	// emulation output to be compared with

	// declare output memory arrays
	AllProjections outputallproj[nevents];
	
	VMProjections outputvmproj9[nevents];
	VMProjections outputvmproj10[nevents];
	VMProjections outputvmproj11[nevents];
	VMProjections outputvmproj12[nevents];
	
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	cout << "Read emulation printouts and fill output memories" << endl;

	fillMemFromFile<AllProjections>(outputallproj,"emData_PR/AllProj_AP_L3L4_L1PHI3_04.dat");

	fillMemFromFile<VMProjections>(outputvmproj9, "emData_PR/VMProjections_VMPROJ_L3L4_L1PHI9_04.dat");
	fillMemFromFile<VMProjections>(outputvmproj10,"emData_PR/VMProjections_VMPROJ_L3L4_L1PHI10_04.dat");
	fillMemFromFile<VMProjections>(outputvmproj11,"emData_PR/VMProjections_VMPROJ_L3L4_L1PHI11_04.dat");
	fillMemFromFile<VMProjections>(outputvmproj12,"emData_PR/VMProjections_VMPROJ_L3L4_L1PHI12_04.dat");

	/////////////////////////////////////
	// loop over events
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Processing event " << dec << ievt << " ..." << endl;

		ap_uint<3> ibx = ievt;
		ap_uint<3> obx;
		
		// Unit Under Test
		// PR_L3L4_L1PHI3
		HLSProjectionRouter(
				tproj1in,
				tproj2in,
				tproj3in,
				tproj4in,
				tproj5in,
				tproj6in,
				tproj7in,
				tproj8in,
				(inputtproj1+ievt)->getEntries(),
				(inputtproj2+ievt)->getEntries(),
				(inputtproj3+ievt)->getEntries(),
				(inputtproj4+ievt)->getEntries(),
				(inputtproj5+ievt)->getEntries(),
				(inputtproj6+ievt)->getEntries(),
				(inputtproj7+ievt)->getEntries(),
				(inputtproj8+ievt)->getEntries(),
				allprojout,
				vmproj9out, vmproj10out, vmproj11out, vmproj12out
				);

		cout << "Output:" << endl;

		// compare calculated outputs with those read from emulation printout
		// allprojections
		for (int j = 0; j < (outputallproj+ievt)->getEntries(); ++j) {
			assert(j < MemDepth);
			if (j==0) cout << "allprojections: " << endl;
			TProj allproj_expected = ((outputallproj+ievt)->get_mem())[j];
			TProj allproj_computed = allprojout[j];
			cout << allproj_expected << " " << allproj_computed << endl;
			if (allproj_expected != allproj_computed) {
				cout << "ERROR! Expected and computed results are different!" << endl;
				err_count++;
			}
		}
		// vmprojections
		for (int j = 0; j < (outputvmproj9+ievt)->getEntries(); ++j) {
			assert(j < MemDepth);
			if (j==0) cout << "vmproj9: " << endl;
			VMProj vmproj9_expected = ((outputvmproj9+ievt)->get_mem())[j];
			VMProj vmproj9_computed = vmproj9out[j];
			cout << vmproj9_expected << " " << vmproj9_computed << endl;
			if (vmproj9_expected != vmproj9_computed) {
				cout << "ERROR! Expected and computed results are different!" << endl;
				err_count++;
			}
		}
		for (int j = 0; j < (outputvmproj10+ievt)->getEntries(); ++j) {
			assert(j < MemDepth);
			if (j==0) cout << "vmproj10: " << endl;
			VMProj vmproj10_expected = ((outputvmproj10+ievt)->get_mem())[j];
			VMProj vmproj10_computed = vmproj10out[j];
			cout << vmproj10_expected << " " << vmproj10_computed << endl;
			if (vmproj10_expected != vmproj10_computed) {
				cout << "ERROR! Expected and computed results are different!" << endl;
				err_count++;
			}
		}
		for (int j = 0; j < (outputvmproj11+ievt)->getEntries(); ++j) {
			assert(j < MemDepth);
			if (j==0) cout << "vmproj11: " << endl;
			VMProj vmproj11_expected = ((outputvmproj11+ievt)->get_mem())[j];
			VMProj vmproj11_computed = vmproj11out[j];
			cout << vmproj11_expected << " " << vmproj11_computed << endl;
			if (vmproj11_expected != vmproj11_computed) {
				cout << "ERROR! Expected and computed results are different!" << endl;
				err_count++;
			}
		}
		for (int j = 0; j < (outputvmproj12+ievt)->getEntries(); ++j) {
			assert(j < MemDepth);
			if (j==0) cout << "vmproj12: " << endl;
			VMProj vmproj12_expected = ((outputvmproj12+ievt)->get_mem())[j];
			VMProj vmproj12_computed = vmproj12out[j];
			cout << vmproj12_expected << " " << vmproj12_computed << endl;
			if (vmproj12_expected != vmproj12_computed) {
				cout << "ERROR! Expected and computed results are different!" << endl;
				err_count++;
			}
		}

	}  // end of event loop

	return err_count;
}
