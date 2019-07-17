#include <iostream>
#include "KFconstants.h"
#include "KFstub.h"
#include "KFstate.h"
#include "KalmanNode_top.h"
#include "KalmanNode.h"
#include "KFdataTypes.h"

template <unsigned int N, int M, class T> 
void getData(const AP_UINT(M)& linkData, const int& LSB, T&& valueOut) {valueOut = linkData.range(LSB + N - 1, LSB);}

int main(int argc, char **argv)
{
  const unsigned int nTracks = 1;
  const unsigned int nInvalidClks = 100;
  int mBinStore[nTracks];
  int cBinStore[nTracks];
  unsigned int htEtaSectStore[nTracks];
  unsigned int nIterationsStore[nTracks];

  unsigned int nIterations = 0;
  unsigned int nCompletedTracks = 0; // Tracks processed by KF  
  
  for (unsigned int n = 0; n <= nTracks; n++) { // n = nTracks gives invalid stubs

    static const EtaBoundaries etaBounds;

    // Track-dependent varaibles
    const int mBin = numPtBins/2 - 3 + 2*(n%3);
    const int cBin = 10 + 2*(n%4);
    const unsigned int kfEtaSect = 2 + n%2;

    const unsigned int gpLayersAtThisEtaSect[] = {1,2,7,5,4,3};
    const bool kfEtaZsign  = false;
    const unsigned int htEtaSect = kfEtaZsign  ?  EtaBoundaries::nSec - 1 - kfEtaSect  : kfEtaSect + EtaBoundaries::nSec;
    const double qOverPt = float(mBin+0.500001)*(2./minPt_HT)/float(numPtBins);
    const double phiT = float(cBin+0.500001)*phiSectorWidth/float(numPhiBins);
    const double phi0 = phiT + invPtToInv2R*chosenRofPhi_flt*qOverPt; // relative to centre of sector
    const double tanL = kfEtaZsign  ?  double(-etaBounds.tanL_[ kfEtaSect ])  :  double(etaBounds.tanL_[ kfEtaSect ]);
    std::cout<<"DELTA PHI"<< phiT - phi0<<std::endl;
    const double z0 = 0.;

    // Store to check against KF output.
    mBinStore[n] = mBin;
    cBinStore[n] = cBin;
    htEtaSectStore[n] = htEtaSect;

    // Uncertainty in track seed. Taken from KF4ParamsComb::seedP()
    const double sigma_qOverPt = 0.0157*2; // = (2*1/4)/32;
    const double sigma_phi0 = 0.0051*2; // 2*pi/16/32 = 0.0061
    const double sigma_tanL = 0.25;
    const double sigma_z0 = 5.0;
    // Error in track seed.
    /*
      const double err_qOverPt = 0.5 * sigma_qOverPt;
      const double err_phi0  = 0. * sigma_phi0;
      const double err_tanL  = 0. * sigma_tanL;
      const double err_z0    = -0.5 * sigma_z0;
    */
    const double err_qOverPt = 0.;
    const double err_phi0  = 0.;
    const double err_tanL  = 0.;
    const double err_z0    = 0.;

    std::cout<<"=== Input particle "<<n<<" ==="<<std::endl;
    std::cout<<"    q/Pt = "<<qOverPt<<std::endl;
    std::cout<<"    phi0 = "<<phi0 <<std::endl;
    std::cout<<"    tanL = "<<tanL <<std::endl;
    std::cout<<"    z0   = "<<z0   <<std::endl;
    std::cout<<"htEtaSect = "<<htEtaSect<<std::endl;
    std::cout<<"   (m,c) = "<<mBin<<" "<<cBin<<std::endl;

    std::cout<<"=== Input particle "<<n<<" (digi) ==="<<std::endl;
    std::cout<<"    1/2R = "<<floor(qOverPt*invPtToInv2R*inv2R_Mult*pow(2,B18-KFstateN::BH0))<<std::endl;
    std::cout<<"    phi0 = "<<floor(phi0*phiMult*pow(2,B18-KFstateN::BH1)) <<std::endl;
    std::cout<<"    tanL = "<<floor(tanL*pow(2,B18-KFstateN::BH2)) <<std::endl;
    std::cout<<"    z0   = "<<floor(z0*rMult*pow(2,B18-KFstateN::BH3)) <<std::endl;

    std::cout<<"=== Seed state "<<n<<" ==="<<std::endl;
    std::cout<<"    q/Pt = "<<qOverPt-err_qOverPt<<" +- "<<sigma_qOverPt<<std::endl;
    std::cout<<"    phi0 = "<<phi0+err_phi0 <<" +- "<<sigma_phi0<<std::endl;
    std::cout<<"    tanL = "<<tanL+err_tanL <<" +- "<<sigma_tanL<<std::endl;
    std::cout<<"    z0   = "<<z0+err_z0   <<" +- "<<sigma_z0<<std::endl;

    // Stubs
    const unsigned int nStubs = 4;
    double r[nStubs] = {23.,37.,50., 80.};
    double z[nStubs], phiS[nStubs];
    for (unsigned int i = 0; i < nStubs; i++) {
      z[i] = z0 + r[i]*tanL;
      phiS[i] = phi0 - invPtToInv2R*qOverPt*r[i];
    }

    KFstub stub;
    KFstate<N_HELIX_PAR> stateOut;
    KFcuts<N_HELIX_PAR> stateCuts;

    bool validTrack = (n < nTracks);
    unsigned int nStubLoop = validTrack ? nStubs : nInvalidClks;

    for (unsigned int j = 0; j < nStubLoop ; j++) {

      nIterations++;

      std::cout<<std::dec<<"=== Iteration "<<nIterations<<" : trk="<<n<<" stub="<<j<<" ==="<<std::endl;

      KFstubN::TPHI phiS_digi;
      KFstubN::TR  r_digi;
      KFstubN::TR1 rt_digi;
      KFstubN::TZ  z_digi;
      KFstubN::TLAY layerID;
      KFstubN::TSEC1 htEtaSectorID;
      KFstubN::TM mBin_digi;
      KFstubN::TM cBin_digi;
      AP_UINT(1) valid;

      if (validTrack) {
	phiS_digi = floor(phiMult*phiS[j]);
        r_digi     = floor(rMult*r[j]);
	rt_digi    = floor(rMult*(r[j] - chosenRofPhi_flt));
	z_digi     = floor(rMult*z[j]); // Same mult used for r & z in KF.
	layerID = gpLayersAtThisEtaSect[j]; 
	htEtaSectorID = htEtaSect;
	mBin_digi = mBin;
	cBin_digi = cBin;
	valid = true;

	std::cout<<"TEST: INPUT STUB: "<<std::dec<<" r="<<r_digi<<" phiS="<<phiS_digi<<" z="<<float(z_digi)<<" evt="<<0<<" trk="<<n<<" lay="<<layerID<<" stub="<<j<<" sec="<<htEtaSectorID<<" m="<<mBin_digi<<" c="<<cBin_digi<<std::endl;

      } else {
	phiS_digi = 0;
	r_digi     = 0;
        rt_digi    = 0;
	z_digi     = 0; // Same mult used for r & z in KF.
	layerID = 0; 
	htEtaSectorID = 0;
	mBin_digi = 0;
	cBin_digi = 0;
	valid = false;
      }

      LinkWord linkIn;
      linkIn.valid = valid;
      linkIn.data = 0;
      if (valid) {
	using namespace KFstubN;
	linkIn.setData<BPHI>(                                    0, phiS_digi.range());
	linkIn.setData<BR1>(                                  BPHI, rt_digi.range());
	linkIn.setData<BSEC1>(                          BR1 + BPHI, htEtaSectorID);
	linkIn.setData<BZ>(                     BSEC1 + BR1 + BPHI, z_digi.range());
	linkIn.setData<BLAY>(              BZ + BSEC1 + BR1 + BPHI, layerID);
	linkIn.setData<BM>(         BLAY + BZ + BSEC1 + BR1 + BPHI, mBin_digi);
	linkIn.setData<BC>(    BM + BLAY + BZ + BSEC1 + BR1 + BPHI, cBin_digi);
	linkIn.setData<1>(BC + BM + BLAY + BZ + BSEC1 + BR1 + BPHI, valid);
      }

      LinkWord linkOut[2];
      linkOut[0].data = 0; linkOut[0].valid = false;
      linkOut[1].data = 0; linkOut[1].valid = false;

      std::cout<<"TEST: LINKIN: "<<std::hex<<linkIn.data<<" "<<linkIn.valid<<std::endl;

      //--- Call HLS block being tested

      kalmanNode_top(linkIn, linkOut);

      std::cout<<"TEST: LINKOUT[1]: "<<std::hex<<linkOut[1].data<<" "<<linkOut[1].valid<<std::endl;
      std::cout<<"TEST: LINKOUT[0]: "<<std::hex<<linkOut[0].data<<" "<<linkOut[0].valid<<std::endl;

      AP_UINT(2*LinkWord::BDATA) linkPairData = (linkOut[1].data,linkOut[0].data);

      KFstate<4> stateOut;
      KFstateN::TSEC1 etaSectHTout = 0;
      getData<B18>           (linkPairData,                   0, stateOut.inv2R.range());
      getData<B18>           (linkPairData,                 B18, stateOut.phi0.range());
      getData<B18>           (linkPairData,               2*B18, stateOut.tanL.range());
      getData<B18>           (linkPairData,               3*B18, stateOut.z0.range());
      getData<B17>           (linkPairData,               4*B18, stateOut.chiSquared.range());
      getData<KFstateN::BM>  (linkPairData,           B17+4*B18, stateOut.mBin_ht);
      getData<KFstateN::BC>  (linkPairData,        KFstateN::BM+B17+4*B18, stateOut.cBin_ht);
      getData<KFstateN::BLAY>(linkPairData,     KFstateN::BC+KFstateN::BM+B17+4*B18, stateOut.layerID); // Check
      getData<KFstateN::BEV> (linkPairData, KFstateN::BLAY+KFstateN::BC+KFstateN::BM+B17+4*B18, stateOut.eventID); // Why output this?
      getData<KFstateN::BSEC1> (linkPairData, KFstateN::BEV+KFstateN::BLAY+KFstateN::BC+KFstateN::BM+B17+4*B18, etaSectHTout); 
      getData<1> (linkPairData, 1+1+KFstateN::BC+KFstateN::BM+KFstateN::BSEC1+KFstateN::BEV+KFstateN::BLAY+KFstateN::BC+KFstateN::BM+B17+4*B18, stateOut.valid); 
      stateOut.print("TEST: OUTPUT STATE:");
      if (stateOut.valid) std::cout<<"But with HT eta sector OUT = "<<std::dec<<etaSectHTout<<std::endl;

      if (stateOut.valid) {
	if (stateOut.mBin_ht == mBinStore[nCompletedTracks] && stateOut.cBin_ht == cBinStore[nCompletedTracks] && etaSectHTout == htEtaSectStore[nCompletedTracks]) {
	  std::cout<<"=== Track "<<nCompletedTracks<<" completed OK in iteration end/start "<<nIterations<<"/"<<nIterationsStore[nCompletedTracks]<<" ==="<<std::endl;
	} else {
	  std::cout<<"=== Track "<<nCompletedTracks<<" completed WRONG in iteration end/start"<<nIterations<<"/"<<nIterationsStore[nCompletedTracks]<<" ==="<<std::endl;
	}
	nCompletedTracks++;
      }

      /*
      // Check bodge to eliminate spurious warning messages about "cannot be negative"
      std::cout<<"PLAY"<<std::endl;
      AP_UFIXED(12,13) junk = 6.5;
      std::cout<<"PA "<<std::dec<<junk<<std::endl;
      std::cout<<"PB "<<std::dec<<float(junk)<<std::endl; // cast makes it go away.
      */
    }

    nIterationsStore[n] = nIterations;
  }

  /*
    ap_fixed<5,3> shit = 3.25;
    ap_ufixed<4,2> rats = shit;
    float ratsF = rats - ap_ufixed<4,2>(0.5);
    ap_ufixed<4,2> ratsA = ratsF - float(0.5);
    std::cout<<"CONVERT "<<shit<<" "<<rats<<" "<<ratsF<<" "<<ratsA<<std::endl;
  */

  CHECK_AP::printCheckMap();

  // Proof that casting ap_fixed to ap_int rounds towards zero, not minus infinity.

  /*
    for (ap_fixed<10,5> i = -10.7; i <= 10; i = i + ap_fixed<10,5>(1.0)) {
    ap_int<3> x = ap_fixed<3,3>(i);
    std::cout<<" ROUNDING "<<i<<" "<<x<<std::endl;
    }
  */

  return 0;
}


