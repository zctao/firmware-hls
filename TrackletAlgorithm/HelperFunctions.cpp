
#ifndef __SYNTHESIS__

#include "HelperFunctions.hh"

std::ostream & operator<<(std::ostream & o, const FullStubLayer2S & sl )
{
  o << "FullStubLayer2S: " 
    << "raw data: " << std::hex << sl.raw() << std::dec
    << ", pt, r, phi, z " 
    << sl.GetPt() << ", " << sl.GetR() << ", "
    << sl.GetPhi() << ", " << sl.GetZ() ;
  
  return o;

}


std::ostream & operator<<(std::ostream & o, const FullStubLayerPS & sl )
{
  o << "FullStubLayerPS: " 
    << "raw data: " << std::hex << sl.raw() << std::dec
    << ", pt, r, phi, z " 
    << sl.GetPt() << ", " << sl.GetR() << ", "
    << sl.GetPhi() << ", " << sl.GetZ() ;
  
  return o;

}

std::ostream & operator<<(std::ostream & o, const ReducedStubLayer & sl )
{
  o << "ReducedStubLayer: " 
    << "raw data: " << std::hex << sl.raw() << std::dec
    << ", pt, r, phi, z, index: " 
    << sl.GetPt() << ", " << sl.GetR() << ", "
    << sl.GetPhi() << ", " << sl.GetZ() << ", "
    << sl.GetIndex() ;
  
  return o;

}


#endif // not __SYNTHESIS__
