// ProjectionRouter test bench
#include "ProjectionRouterWrapper.h"
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

	// read input files
	ifstream fin_tproj1;
	ifstream fin_tproj2;
	ifstream fin_tproj3;
	ifstream fin_tproj4;

	fin_tproj1.open("emData_PR/TrackletProjections_TPROJ_L3L4C_L1PHI3_04.dat");
	fin_tproj2.open("emData_PR/TrackletProjections_TPROJ_L3L4D_L1PHI3_04.dat");
	fin_tproj3.open("emData_PR/TrackletProjections_TPROJ_L3L4E_L1PHI3_04.dat");
	fin_tproj4.open("emData_PR/TrackletProjections_TPROJ_L3L4F_L1PHI3_04.dat");

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

	// fill memories from files
	fillMemfromFile<TrackletProjections>(inputtproj1, fin_tproj1);
	fillMemfromFile<TrackletProjections>(inputtproj2, fin_tproj2);
	fillMemfromFile<TrackletProjections>(inputtproj3, fin_tproj3);
	fillMemfromFile<TrackletProjections>(inputtproj4, fin_tproj4);

	// close files
	fin_tproj1.close();
	fin_tproj2.close();
	fin_tproj3.close();
	fin_tproj4.close();

	// loop over events
	for (int ievt = 0; ievt < nevents; ++ievt) {
		cout << "Event: " << dec << ievt << endl;

		cout << "Input:" << endl;
		cout << "inputtproj4: " << endl;
		(inputtproj4+ievt)->print_mem();
		int numberin = (inputtproj4+ievt)->getEntries();

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

		//AllProj* allprojout = (outputallproj+ievt)->get_mem();
		//VMProj* vmproj9out = (outputvmproj9+ievt)->get_mem();
		//VMProj* vmproj10out = (outputvmproj9+ievt)->get_mem();
		//VMProj* vmproj11out = (outputvmproj9+ievt)->get_mem();
		//VMProj* vmproj12out = (outputvmproj9+ievt)->get_mem();

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
/*
				(outputallproj+ievt)->get_mem(),
				(outputvmproj9+ievt)->get_mem(),
				(outputvmproj10+ievt)->get_mem(),
				(outputvmproj11+ievt)->get_mem(),
				(outputvmproj12+ievt)->get_mem()
*/
				);

		cout << "Output:" << endl;
		for (int iin = 0; iin < numberin; ++iin) {
			cout << "allproj" << endl;
			cout << "Calculated: " << endl;
			(outputallproj+ievt)->print_data(allprojout[iin]);
			//(outputallproj+ievt)->print_mem();

			cout << "vmproj12" << endl;
			cout << "Calculated: " << endl;
			// FIXME
			(outputvmproj12+ievt)->print_data(vmproj12out[0]);
			(outputvmproj12+ievt)->print_data(vmproj12out[1]);
		}

	}  // end of event loop

	return 0;
}
