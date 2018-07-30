#pragma once


#ifndef __SYNTHESIS__

#include <ostream>

#include <ostream>

#include "FullStubLayer2S.hh"
#include "FullStubLayerPS.hh"
#include "ReducedStubLayer.hh"


std::ostream & operator<<(std::ostream & o, const FullStubLayer2S & sl );
std::ostream & operator<<(std::ostream & o, const FullStubLayerPS & sl );
std::ostream & operator<<(std::ostream & o, const ReducedStubLayer & sl );


#endif // __SYNTHESIS__
