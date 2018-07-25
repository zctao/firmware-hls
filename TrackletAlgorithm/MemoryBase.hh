// Base class for memory modules
#ifndef MEMORYBASE_HH
#define MEMORYBASE_HH

template <class DataStruct, unsigned int Depth>
class MemoryBase{
public:
  
  MemoryBase(){}
  virtual ~MemoryBase(){}

  unsigned int getEntries() {return nentries_;}
  unsigned int getDepth() {return Depth;}

  const DataStruct* get_mem() const {return dataarray_;}

  void set_mem(int i, DataStruct data, unsigned int nEntries = 0)
  {
	  dataarray_[i] = data;
	  nentries_ = nEntries;
  }

protected:

  DataStruct dataarray_[Depth];

  unsigned int nentries_ = 0;

  //const int isector_;
  //int bx_;
  //std::string name_;

};

#endif
