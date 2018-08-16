#include "HLSProjectionRouter.h"

void HLSProjectionRouter(
			     TProj inprojdata1[MemDepth],
			     TProj inprojdata2[MemDepth],
			     TProj inprojdata3[MemDepth],
			     TProj inprojdata4[MemDepth],
			     TProj inprojdata5[MemDepth],
			     TProj inprojdata6[MemDepth],
			     TProj inprojdata7[MemDepth],
			     TProj inprojdata8[MemDepth],
			     // more
				 unsigned int inprojnumber1,
				 unsigned int inprojnumber2,
				 unsigned int inprojnumber3,
				 unsigned int inprojnumber4,
				 unsigned int inprojnumber5,
				 unsigned int inprojnumber6,
				 unsigned int inprojnumber7,
				 unsigned int inprojnumber8,

			     AllProj outallproj[MemDepth],
			     VMProj outvmprojphi1[MemDepth],
			     VMProj outvmprojphi2[MemDepth],
			     VMProj outvmprojphi3[MemDepth],
			     VMProj outvmprojphi4[MemDepth]/*,
			     VMProjData outvmprojphi5[MemDepth],
			     VMProjData outvmprojphi6[MemDepth],
			     VMProjData outvmprojphi7[MemDepth],
			     VMProjData outvmprojphi8[MemDepth],
			     VMProjData outvmprojphi9[MemDepth],
			     VMProjData outvmprojphi10[MemDepth],
			     VMProjData outvmprojphi11[MemDepth],
			     VMProjData outvmprojphi12[MemDepth]*/
			     )
{
	//
	TProj* inprojs[8] = {inprojdata1, inprojdata2, inprojdata3, inprojdata4,
			inprojdata5, inprojdata6, inprojdata7, inprojdata8};
#pragma HLS ARRAY_PARTITION variable=inprojs complete dim=1

	unsigned int inprojnum[8] = {inprojnumber1, inprojnumber2, inprojnumber3, inprojnumber4,
			inprojnumber5, inprojnumber6, inprojnumber7, inprojnumber8};
#pragma HLS ARRAY_PARTITION variable=inprojnum complete dim=1

	VMProj* vmprojs[4] = {outvmprojphi1, outvmprojphi2, outvmprojphi3, outvmprojphi4};
#pragma HLS ARRAY_PARTITION variable=vmprojs complete dim=1

	static ProjectionRouter aPR(
			inprojs, //inprojnum,
			outallproj, vmprojs);
  
	aPR.execute(inprojnum);
}
