// Base class for memory modules
#ifndef MEMORYBASE_HH
#define MEMORYBASE_HH


template <class DataType, unsigned int NBX, unsigned int DEPTH>
class MemoryBase{
public:
  
  MemoryBase()
  {
#pragma HLS ARRAY_PARTITION variable=nentries_ complete
	clear();
  }

  virtual ~MemoryBase(){}

  void clear()
  {
  MEM_RST: for (ap_uint<3> ibx=0; ibx<NBX; ++ibx) {
#pragma HLS UNROLL
	  nentries_[ibx%NBX] = 0;
	}
  }

  void clear(ap_uint<3> bx) {nentries_[bx%NBX] = 0;}

  unsigned int getDepth() const {return DEPTH;}
  unsigned int getnBX() const {return NBX;}
  
  unsigned int getEntries(ap_uint<3> bx) const {return nentries_[bx%NBX];}

  DataType* get_mem() {return dataarray_;}
  
  DataType read_mem(ap_uint<3> ibx, unsigned int index) const // to be optimized
  {
	// TODO: check if valid
	return dataarray_[ibx%NBX][index];
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
  
  bool write_mem(ap_uint<3> bx, const char* datastr, int base = 16)
  {
	DataType data(datastr, base);
	std::cout << "write_mem " << data << std::endl;
	return write_mem(bx, data);
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
	for (int i = 0; i < nentries_[bx%NBX]; ++i) {
	  std::cout << bx << " " << i << " ";
	  print_entry(bx,i);
	}
  }

  void print_mem() const
  {
	for (int ibx = 0; ibx < NBX; ++ibx) {
	  for (int i = 0; i < nentries_[ibx%NBX]; ++i) {
		std::cout << ibx << " " << i << " ";
		print_entry(ibx,i);
	  }
	}
  }

#endif

protected:
  
  DataType dataarray_[NBX][DEPTH];
  unsigned int nentries_[NBX]; 

  //const int isector_;
  //std::string name_;
};

#endif
