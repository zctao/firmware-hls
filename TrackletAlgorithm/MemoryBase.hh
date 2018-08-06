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

  void add_mem(DataStruct data)
  {
	  if (nentries_ <= Depth)
		  dataarray_[nentries_++] = data;
  }

  /*
  void set_mem(int i, DataStruct data, unsigned int nEntries = 0)
  {
	  dataarray_[i] = data;
	  nentries_ = nEntries;
  }
  */

protected:

  DataStruct dataarray_[Depth];

  unsigned int nentries_;

  //const int isector_;
  //int bx_;
  //std::string name_;

};

#endif
