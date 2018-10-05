// Base class for memory modules
#ifndef MEMORYBASEBINNED_HH
#define MEMORYBASEBINNED_HH

#include <sstream>
#include <vector>

using namespace std;


template <class DataType, unsigned int NBX, unsigned int DEPTH>
class MemoryBaseBinned{
public:
  
  MemoryBaseBinned()
  {
#pragma HLS ARRAY_PARTITION variable=nentries_ complete
	clear();
  }

  virtual ~MemoryBaseBinned(){}

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


  void clear()
  {
	for (ap_uint<3> ibx=0; ibx<NBX; ++ibx) {
#pragma HLS UNROLL
	  nentries_[ibx%NBX] = 0;
	}
  }

  void clear(ap_uint<3> bx) {nentries_[bx%NBX] = 0;}

  unsigned int getDepth() const {return DEPTH;}
  unsigned int getnBX() const {return NBX;}
  
  unsigned int getEntries(ap_uint<3> bx) const {return nentries_[bx%NBX];}

  DataType* get_mem(ap_uint<3> bx) {return dataarray_[bx%NBX];}
  
  DataType read_mem(ap_uint<3> ibx, unsigned int index) const // to be optimized
  {
	// TODO: check if valid
	return dataarray_[ibx%NBX][index];
  }

  bool write_mem(ap_uint<3> ibx, ap_uint<3> slot, DataType data) {
    //assert(ibx < NBX);
    
    if (nentries_[ibx%NBX].range((slot+1)*4-1,slot*4) < DEPTH) {
      ap_uint<32> increment=1;
      dataarray_[ibx%NBX][16*slot+nentries_[ibx%NBX].range((slot+1)*4-1,slot*4)] = data;
      //cout <<"nentries : "<<hex<<nentries_[ibx%NBX]<<" "<<nentries_[ibx%NBX].range((slot+1)*4-1,slot*4) <<dec<<endl;
      increment<<=(slot*4);
      nentries_[ibx%NBX]+=increment;
      return true;
    }
    else {
      std::cout << "Warning out of range"<<std::endl;
      return false;
    }
  }
  
  bool write_mem_line(ap_uint<3> bx, const std::string& line, int base = 16) {

 
    assert(split(line, ' ').size()==4);
    string datastr = split(line, ' ').back();

    int slot=atoi(split(line, ' ').front().c_str());

    DataType data(datastr.c_str(), base);
    //std::cout << "write_mem slot data : " << slot<<" "<<data << std::endl;
    return write_mem(bx, slot, data);
  }

#ifndef __SYNTHESIS__
#include <iostream>

  // print memory contents
  virtual void print_data(const DataType data) const
  {
	std::cout << std::hex << data << std::endl;
  }

  void print_entry(ap_uint<3> bx, unsigned int i) const
  {
	print_data(dataarray_[bx%NBX][i]);
  }

  void print_mem(ap_uint<3> bx) const
  {
    for(int slot=0;slot<8;slot++) {
      //std::cout << "slot "<<slot<<" entries "
      //		<<nentries_[bx%NBX].range((slot+1)*4-1,slot*4)<<endl;
      for (int i = 0; i < nentries_[bx%NBX].range((slot+1)*4-1,slot*4); ++i) {
	std::cout << bx << " " << i << " ";
	print_entry(bx,i+slot*16);
      }
    }
  }

  void print_mem() const
  {
	for (int ibx = 0; ibx < NBX; ++ibx) {
	  print_mem(ibx);
	}
  }

#endif

protected:
  
  DataType dataarray_[NBX][DEPTH];
  ap_uint<32> nentries_[NBX]; 

  //const int isector_;
  //std::string name_;
};

#endif
