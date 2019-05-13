#ifndef PRMEMCTEST_H
#define PRMEMCTEST_H

#include "Constants.hh"
#include "TrackletCalculator.hh"
#include "ProjectionRouter.hh"
#include "MatchEngine.h"
#include "MatchCalculator.hh"

void PRMEMCTest(
BXType bx,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC22n1,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC23n1,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC24n1,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L1L2F_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L1L2G_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L1L2H_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L1L2I_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L1L2J_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L5L6B_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L5L6C_L3PHIC,
const TrackletProjectionMemory<BARRELPS>& TPROJ_L5L6D_L3PHIC,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC17n1,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC18n1,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC19n1,
const AllStubMemory<BARRELPS>& AS_L3PHICn4,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC20n1,
const VMStubMEMemory<BARRELPS>& VMSME_L3PHIC21n1,
BXType& bx_o,
FullMatchMemory<BARREL>& FM_L5L6_L3PHIC,
FullMatchMemory<BARREL>& FM_L1L2_L3PHIC);

#endif
