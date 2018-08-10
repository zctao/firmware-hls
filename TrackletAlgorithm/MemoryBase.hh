// Base class for memory modules
#ifndef MEMORYBASE_HH
#define MEMORYBASE_HH

template <class DataStruct, unsigned int Depth>
class MemoryBase{
public:
  
  MemoryBase() {
	  nentries_ = 0;  // need a reset function
  }

  virtual ~MemoryBase(){}

  unsigned int getEntries() {return nentries_;}
  unsigned int getDepth() {return Depth;}

  DataStruct* get_mem() {return dataarray_;}

  bool add_mem(DataStruct data)
  {
	  if (nentries_ <= Depth) {
		  dataarray_[nentries_++] = data;
		  return true;
	  }
	  else
		  return false;
  }

  /*
  void set_mem(int i, DataStruct data, unsigned int nEntries = 0)
  {
	  dataarray_[i] = data;
	  nentries_ = nEntries;
  }
  */

#ifndef __SYNTHESIS__
#include <iostream>
  virtual void print_data(const DataStruct&) const {}

  void print_entry(int i) const
  {
	  print_data(dataarray_[i]);
  }

  void print_mem() const
  {
	  for (int i = 0; i < nentries_; ++i) {
  		  std::cout << i << " ";
  		  print_entry(i);
  	  }
  }

#endif

protected:

  DataStruct dataarray_[Depth];

  unsigned int nentries_;

  //const int isector_;
  //int bx_;
  //std::string name_;

};

#endif
