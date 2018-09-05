// Base class for memory modules
#ifndef MEMORYBASE_HH
#define MEMORYBASE_HH


template <class DataType, unsigned int NBX, unsigned int DEPTH>
class MemoryBase{
public:
  
  MemoryBase()
  {
#pragma HLS ARRAY_PARTITION variable=nentries_ complete dim=1
	//clear();
  }

  virtual ~MemoryBase(){}

  void clear()
  {
	for (ap_uint<3> ibx=0; ibx<NBX; ++ibx) {
#pragma HLS UNROLL
	  nentries_[ibx] = 0;
	}
  }

  unsigned int getDepth() const {return DEPTH;}
  unsigned int getnBX() const {return NBX;}
  
  unsigned int getEntries(ap_uint<3> bx) const {return nentries_[bx];}

  DataType* get_mem() {return dataarray_;}
  
  DataType read_mem(ap_uint<3> ibx, unsigned int index) const // to be optimized
  {
	return dataarray_[ibx][index];
  }

  bool write_mem(ap_uint<3> ibx, DataType data)
  {
	//assert(ibx < NBX);
	
	if (nentries_[ibx%NBX] <= DEPTH) {
	  dataarray_[ibx%NBX][nentries_[ibx%NBX]++] = data;
	  return true;
	}
	else
	  return false;
  }
  
  bool write_mem(const char* datastr, ap_uint<3> bx=0, int base = 16)
  {
	DataType data(datastr, base);
	return write_mem(data, bx);
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
	print_data(dataarray_[bx][i]);
  }

  void print_mem(ap_uint<3> bx) const
  {
	for (int i = 0; i < nentries_[bx]; ++i) {
	  std::cout << bx << " " << i << " ";
	  print_entry(bx,i);
	}
  }

  void print_mem() const
  {
	for (int ibx = 0; ibx < NBX; ++ibx) {
	  for (int i = 0; i < nentries_[ibx]; ++i) {
		std::cout << ibx << " " << i << " ";
		print_entry(ibx,i);
	  }
	}
  }

#endif

protected:

  //const ap_uint<3> nBX_; // number of BXs the memory module keeps track of
  //const unsigned int Depth_; // depth of memory block per BX
  
  DataType dataarray_[NBX][DEPTH];
  unsigned int nentries_[NBX]; 

  //const int isector_;
  //std::string name_;
};

#endif
