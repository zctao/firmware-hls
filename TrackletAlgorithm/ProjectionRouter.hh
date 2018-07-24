// Projection Router
#ifndef PROJECTIONROUTER_HH
#define PROJECTIONROUTER_HH

#include "Constants.hh"

#include "TrackletProjections.hh"
#include "AllProjections.hh"
#include "VMProjections.hh"

class ProjectionRouter//:public ProcessBase
{
public:

  // constructor
  ProjectionRouter(){}
  ~ProjectionRouter(){}

  void execute()
  {

    // LOOP
    // do stuff with inputproj1_, inputproj2_, ...
    // assign output
    //allproj_->setAllProj();
    // vmprojphi1_->SetVMProj();

  }

  // connect input & output memory modules
  void addInputs(TrackletProjections* trackletproj1,
		TrackletProjections* trackletproj2,
		TrackletProjections* trackletproj3,
		TrackletProjections* trackletproj4,
		TrackletProjections* trackletproj5,
		TrackletProjections* trackletproj6,
		TrackletProjections* trackletproj7,
		TrackletProjections* trackletproj8
		// more
		)
  {
    inputproj1_ = trackletproj1->getTProj();
    inputproj2_ = trackletproj2->getTProj();
    inputproj3_ = trackletproj3->getTProj();
    inputproj4_ = trackletproj4->getTProj();
    inputproj5_ = trackletproj5->getTProj();
    inputproj6_ = trackletproj6->getTProj();
    inputproj7_ = trackletproj7->getTProj();
    inputproj8_ = trackletproj8->getTProj();
  }

  void addOutputs(AllProjections* allprojection,
		 VMProjections* vmproj1,
		 VMProjections* vmproj2,
		 VMProjections* vmproj3,
		 VMProjections* vmproj4,
		 VMProjections* vmproj5,
		 VMProjections* vmproj6,
		 VMProjections* vmproj7,
		 VMProjections* vmproj8,
		 VMProjections* vmproj9,
		 VMProjections* vmproj10,
		 VMProjections* vmproj11,
		 VMProjections* vmproj12
		 )
  {
    allproj_ = allprojection->getAllProj();

    vmprojphi1_ = vmproj1->getVMProj();
    vmprojphi2_ = vmproj2->getVMProj();
    vmprojphi3_ = vmproj3->getVMProj();
    vmprojphi4_ = vmproj4->getVMProj();
    vmprojphi5_ = vmproj5->getVMProj();
    vmprojphi6_ = vmproj6->getVMProj();
    vmprojphi7_ = vmproj7->getVMProj();
    vmprojphi8_ = vmproj8->getVMProj();
    vmprojphi9_ = vmproj9->getVMProj();
    vmprojphi10_ = vmproj10->getVMProj();
    vmprojphi11_ = vmproj11->getVMProj();
    vmprojphi12_ = vmproj12->getVMProj();
  }
  
  // overload 
  void addInputs(TProjData* trackletproj1,
		TProjData* trackletproj2,
		TProjData* trackletproj3,
		TProjData* trackletproj4,
		TProjData* trackletproj5,
		TProjData* trackletproj6,
		TProjData* trackletproj7,
		TProjData* trackletproj8
		// more
		)
  {
    inputproj1_ = trackletproj1;
    inputproj2_ = trackletproj2;
    inputproj3_ = trackletproj3;
    inputproj4_ = trackletproj4;
    inputproj5_ = trackletproj5;
    inputproj6_ = trackletproj6;
    inputproj7_ = trackletproj7;
    inputproj8_ = trackletproj8;
  }

  void addOutputs(AllProjData* allprojection,
		 VMProjData* vmproj1,
		 VMProjData* vmproj2,
		 VMProjData* vmproj3,
		 VMProjData* vmproj4,
		 VMProjData* vmproj5,
		 VMProjData* vmproj6,
		 VMProjData* vmproj7,
		 VMProjData* vmproj8,
		 VMProjData* vmproj9,
		 VMProjData* vmproj10,
		 VMProjData* vmproj11,
		 VMProjData* vmproj12
		 )
  {
    allproj_ = allprojection;

    vmprojphi1_ = vmproj1;
    vmprojphi2_ = vmproj2;
    vmprojphi3_ = vmproj3;
    vmprojphi4_ = vmproj4;
    vmprojphi5_ = vmproj5;
    vmprojphi6_ = vmproj6;
    vmprojphi7_ = vmproj7;
    vmprojphi8_ = vmproj8;
    vmprojphi9_ = vmproj9;
    vmprojphi10_ = vmproj10;
    vmprojphi11_ = vmproj11;
    vmprojphi12_ = vmproj12;
  }


private:
  
  // inputs
  TProjData* inputproj1_;
  TProjData* inputproj2_;
  TProjData* inputproj3_;
  TProjData* inputproj4_;
  TProjData* inputproj5_;
  TProjData* inputproj6_;
  TProjData* inputproj7_;
  TProjData* inputproj8_;
  // more

  // outputs
  AllProjData* allproj_;

  VMProjData* vmprojphi1_;
  VMProjData* vmprojphi2_;
  VMProjData* vmprojphi3_;
  VMProjData* vmprojphi4_;
  VMProjData* vmprojphi5_;
  VMProjData* vmprojphi6_;
  VMProjData* vmprojphi7_;
  VMProjData* vmprojphi8_;
  VMProjData* vmprojphi9_;
  VMProjData* vmprojphi10_;
  VMProjData* vmprojphi11_;
  VMProjData* vmprojphi12_;

  /*
  // inputs
  TrackletProjections* inputproj1_;
  TrackletProjections* inputproj2_;
  TrackletProjections* inputproj3_;
  TrackletProjections* inputproj4_;
  TrackletProjections* inputproj5_;
  TrackletProjections* inputproj6_;
  TrackletProjections* inputproj7_;
  TrackletProjections* inputproj8_;
  // more

  // outputs
  AllProjections* allproj_;

  VMProjections* vmprojphi1_;
  VMProjections* vmprojphi2_;
  VMProjections* vmprojphi3_;
  VMProjections* vmprojphi4_;
  VMProjections* vmprojphi5_;
  VMProjections* vmprojphi6_;
  VMProjections* vmprojphi7_;
  VMProjections* vmprojphi8_;
  VMProjections* vmprojphi9_;
  VMProjections* vmprojphi10_;
  VMProjections* vmprojphi11_;
  VMProjections* vmprojphi12_;
  */
};

#endif
