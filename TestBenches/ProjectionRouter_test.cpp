// ProjectionRouter test bench
#include "ProjectionRouterWrapper.h"
//#include "ProjectionRouter.hh"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

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

			string datastr = split(line, ' ').back();
			//cout << datastr << endl;
			(memarray+ievent)->add_mem(datastr.c_str());
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
	TrackletProjections inputtproj1[nevents];
	TrackletProjections inputtproj2[nevents];
	TrackletProjections inputtproj3[nevents];
	TrackletProjections inputtproj4[nevents];
	TrackletProjections inputtproj5[nevents];
	TrackletProjections inputtproj6[nevents];
	TrackletProjections inputtproj7[nevents];
	TrackletProjections inputtproj8[nevents];

	// declare output memory arrays
	AllProjections outputallproj[nevents];
	VMProjections outputvmproj1[nevents];
	VMProjections outputvmproj2[nevents];
	VMProjections outputvmproj3[nevents];
	VMProjections outputvmproj4[nevents];
	VMProjections outputvmproj5[nevents];
	VMProjections outputvmproj6[nevents];
	VMProjections outputvmproj7[nevents];
	VMProjections outputvmproj8[nevents];
	VMProjections outputvmproj9[nevents];
	VMProjections outputvmproj10[nevents];
	VMProjections outputvmproj11[nevents];
	VMProjections outputvmproj12[nevents];

	/////////////////////////////////////
	// read input files
	ifstream fin_tproj1;
	ifstream fin_tproj2;
	ifstream fin_tproj3;
	ifstream fin_tproj4;
	ifstream fin_tproj5;

	fin_tproj1.open("emData_PR/TrackletProjections_TPROJ_L3L4C_L1PHI3_04.dat");
	fin_tproj2.open("emData_PR/TrackletProjections_TPROJ_L3L4D_L1PHI3_04.dat");
	fin_tproj3.open("emData_PR/TrackletProjections_TPROJ_L3L4E_L1PHI3_04.dat");
	fin_tproj4.open("emData_PR/TrackletProjections_TPROJ_L3L4F_L1PHI3_04.dat");
	fin_tproj5.open("emData_PR/TrackletProjections_TPROJ_D1L2B_L1PHI3_04.dat");

	if (!fin_tproj1) {
		cerr << "Cannot open fin_tproj1. Abort." << endl;
		return -1;
	}
	if (!fin_tproj2) {
		cerr << "Cannot open fin_tproj2. Abort." << endl;
		return -1;
	}
	if (!fin_tproj3) {
		cerr << "Cannot open fin_tproj3. Abort." << endl;
		return -1;
	}
	if (!fin_tproj4) {
		cerr << "Cannot open fin_tproj4. Abort." << endl;
		return -1;
	}
	if (!fin_tproj5) {
		cerr << "Cannot open fin_tproj5. Abort." << endl;
		return -1;
	}

	// fill memories from files
	fillMemfromFile<TrackletProjections>(inputtproj1, fin_tproj1);
	fillMemfromFile<TrackletProjections>(inputtproj2, fin_tproj2);
	fillMemfromFile<TrackletProjections>(inputtproj3, fin_tproj3);
	fillMemfromFile<TrackletProjections>(inputtproj4, fin_tproj4);
	fillMemfromFile<TrackletProjections>(inputtproj5, fin_tproj5);

	// close files
	fin_tproj1.close();
	fin_tproj2.close();
	fin_tproj3.close();
	fin_tproj4.close();
	fin_tproj5.close();

	/////////////////////////////////////
	// emulation output to be compared with
	ifstream fout_aproj;
	fout_aproj.open("emData_PR/AllProj_AP_L3L4_L1PHI3_04.dat");

	//ifstream fout_vmproj1, fout_vmproj2, fout_vmproj3, fout_vmproj4;
	//ifstream fout_vmproj5, fout_vmproj6, fout_vmproj7, fout_vmproj8;
	ifstream fout_vmproj9, fout_vmproj10, fout_vmproj11, fout_vmproj12;
	//fout_vmproj1.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI1_04.dat");
	//fout_vmproj2.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI2_04.dat");
	//fout_vmproj3.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI3_04.dat");
	//fout_vmproj4.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI4_04.dat");
	//fout_vmproj5.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI5_04.dat");
	//fout_vmproj6.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI6_04.dat");
	//fout_vmproj7.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI7_04.dat");
	//fout_vmproj8.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI8_04.dat");
	fout_vmproj9.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI9_04.dat");
	fout_vmproj10.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI10_04.dat");
	fout_vmproj11.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI11_04.dat");
	fout_vmproj12.open("emData_PR/VMProjections_VMPROJ_L3L4_L1PHI12_04.dat");

	fillMemfromFile<AllProjections>(outputallproj, fout_aproj);
	//fillMemfromFile<VMProjections>(outputvmproj1, fout_vmproj1);
	//fillMemfromFile<VMProjections>(outputvmproj2, fout_vmproj2);
	//fillMemfromFile<VMProjections>(outputvmproj3, fout_vmproj3);
	//fillMemfromFile<VMProjections>(outputvmproj4, fout_vmproj4);
	//fillMemfromFile<VMProjections>(outputvmproj5, fout_vmproj5);
	//fillMemfromFile<VMProjections>(outputvmproj6, fout_vmproj6);
	//fillMemfromFile<VMProjections>(outputvmproj7, fout_vmproj7);
	//fillMemfromFile<VMProjections>(outputvmproj8, fout_vmproj8);
	fillMemfromFile<VMProjections>(outputvmproj9, fout_vmproj9);
	fillMemfromFile<VMProjections>(outputvmproj10, fout_vmproj10);
	fillMemfromFile<VMProjections>(outputvmproj11, fout_vmproj11);
	fillMemfromFile<VMProjections>(outputvmproj12, fout_vmproj12);

	fout_aproj.close();
	//fout_vmproj1.close();
	//fout_vmproj2.close();
	//fout_vmproj3.close();
	//fout_vmproj4.close();
	//fout_vmproj5.close();
	//fout_vmproj6.close();
	//fout_vmproj7.close();
	//fout_vmproj8.close();
	fout_vmproj9.close();
	fout_vmproj10.close();
	fout_vmproj11.close();
	fout_vmproj12.close();

	/////////////////////////////////////
	// loop over events
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Event: " << dec << ievt << endl;

		cout << "Input:" << endl;
		if ((inputtproj1+ievt)->getEntries() > 0) {
			cout << "inputtproj1: ";
			(inputtproj1+ievt)->print_mem();
		}
		if ((inputtproj2+ievt)->getEntries() > 0) {
			cout << "inputtproj2: ";
			(inputtproj2+ievt)->print_mem();
		}
		if ((inputtproj3+ievt)->getEntries() > 0) {
			cout << "inputtproj3: ";
			(inputtproj3+ievt)->print_mem();
		}
		if ((inputtproj4+ievt)->getEntries() > 0) {
			cout << "inputtproj4: ";
			(inputtproj4+ievt)->print_mem();
		}
		if ((inputtproj5+ievt)->getEntries() > 0) {
			cout << "inputtproj5: ";
			(inputtproj5+ievt)->print_mem();
		}
		if ((inputtproj6+ievt)->getEntries() > 0) {
			cout << "inputtproj6: ";
			(inputtproj6+ievt)->print_mem();
		}
		if ((inputtproj7+ievt)->getEntries() > 0) {
			cout << "inputtproj7: ";
			(inputtproj7+ievt)->print_mem();
		}
		if ((inputtproj8+ievt)->getEntries() > 0) {
			cout << "inputtproj8: ";
			(inputtproj8+ievt)->print_mem();
		}
		// input data array
		// memories that are actually connected to the processing module
		TProj tproj1in[MemDepth];
		TProj tproj2in[MemDepth];
		TProj tproj3in[MemDepth];
		TProj tproj4in[MemDepth];
		TProj tproj5in[MemDepth];
		TProj tproj6in[MemDepth];
		TProj tproj7in[MemDepth];
		TProj tproj8in[MemDepth];
		// fill input data arrays
		fillMem<TProj, MemDepth>(tproj1in, (inputtproj1+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj2in, (inputtproj2+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj3in, (inputtproj3+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj4in, (inputtproj4+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj5in, (inputtproj5+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj6in, (inputtproj6+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj7in, (inputtproj7+ievt)->get_mem());
		fillMem<TProj, MemDepth>(tproj8in, (inputtproj8+ievt)->get_mem());

		// output memories that are actually connected to the processing module
		AllProj allprojout[MemDepth];
		VMProj vmproj9out[MemDepth];
		VMProj vmproj10out[MemDepth];
		VMProj vmproj11out[MemDepth];
		VMProj vmproj12out[MemDepth];

		// Unit Under Test
		// PR_L3L4_L1PHI3
		ProjectionRouterWrapper(
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
		/*
		for (int iin = 0; iin < numberin; ++iin) {
			cout << "allproj" << endl;
			cout << "Calculated: " << endl;
			cout << hex << allprojout[iin] << endl;
			//(outputallproj+ievt)->print_mem();

			cout << "vmproj12" << endl;
			cout << "Calculated: " << endl;
			// FIXME
			cout << hex << vmproj12out[0] << endl;
			cout << hex << vmproj12out[1] << endl;
		}
		*/

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
