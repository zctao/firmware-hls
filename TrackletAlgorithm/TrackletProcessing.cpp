#include "ProjectionRouter.hh"

void TrackletProcessing(/*input link stream?*/)
{
  // load/stream input and output memories somehow...

  // Memory modules
  static TrackletProjections TPROJ_L1L2D_L3PHI3;
  static TrackletProjections TPROJ_L1L2E_L3PHI3;
  static TrackletProjections TPROJ_L1L2F_L3PHI3;
  static TrackletProjections TPROJ_L5L6A_L3PHI3;
  static TrackletProjections TPROJ_L5L6C_L3PHI3;
  static TrackletProjections TPROJ_L5L6D_L3PHI3;
  static TrackletProjections TPROJ_L5L6E_L3PHI3;
  static TrackletProjections TPROJ_L5L6F_L3PHI3;

  static AllProjections AP_L1L2_L3PHI3;

  //static VMProjections VMPROJ_L1L2_L3PHI1;
  //static VMProjections VMPROJ_L1L2_L3PHI2;
  //static VMProjections VMPROJ_L1L2_L3PHI3;
  //static VMProjections VMPROJ_L1L2_L3PHI4;
  //static VMProjections VMPROJ_L1L2_L3PHI5;
  //static VMProjections VMPROJ_L1L2_L3PHI6;
  //static VMProjections VMPROJ_L1L2_L3PHI7;
  //static VMProjections VMPROJ_L1L2_L3PHI8;
  static VMProjections VMPROJ_L1L2_L3PHI9;
  static VMProjections VMPROJ_L1L2_L3PHI10;
  static VMProjections VMPROJ_L1L2_L3PHI11;
  static VMProjections VMPROJ_L1L2_L3PHI12;
  
  static ProjectionRouter PR_L1L2_L3PHI3;

  PR_L1L2_L3PHI3.addInputs(&TPROJ_L1L2D_L3PHI3, &TPROJ_L1L2E_L3PHI3,
			   &TPROJ_L1L2F_L3PHI3, &TPROJ_L5L6A_L3PHI3,
			   &TPROJ_L5L6C_L3PHI3, &TPROJ_L5L6D_L3PHI3,
			   &TPROJ_L5L6E_L3PHI3, &TPROJ_L5L6F_L3PHI3);
  PR_L1L2_L3PHI3.addInputs(&AP_L1L2_L3PHI3,
			   0, 0, 0, 0, 0, 0, 0, 0, // or nullptr?
			   &VMPROJ_L1L2_L3PHI9, &VMPROJ_L1L2_L3PHI10,
			   &VMPROJ_L1L2_L3PHI11, &VMPROJ_L1L2_L3PHI12);

  PR_L1L2_L3PHI3.execute();
}
