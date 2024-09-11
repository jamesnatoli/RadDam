#include "TMath.h"

void select_photon(Int_t iWP, TreeReader &data, vector<int>& accepted) {

  accepted.clear();

  // load relevant branches from TTree/TChain
  Int_t    nPho                = data.GetInt("nPho");
  Float_t* phoEt               = data.GetPtrFloat("phoEt");
  Float_t* phoSCEta            = data.GetPtrFloat("phoSCEta");
  Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
  Float_t* phoSigmaIEtaIEta    = data.GetPtrFloat("phoSigmaIEtaIEta"); // to be updated
  Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
  Float_t* phoPFChIso          = data.GetPtrFloat("phoPFChIso");
  Float_t* phoPFNeuIso         = data.GetPtrFloat("phoPFNeuIso");
  Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
  Float_t  rho                 = data.GetFloat("rho");

  Float_t HoECut[3][2]    = {{0.028,  0.054},  {0.011,  0.023},  {0.011,  0.014}};
  Float_t sieieCut[3][2]  = {{0.0100, 0.0276}, {0.0099, 0.0269}, {0.0099, 0.0264}};
  Float_t chIsoCut[3][2]  = {{3.01,   3.175},  {2.10,   1.59},   {1.75,   1.17}};
  Float_t nhIsoCut[3][2]  = {{1.38,   6.33},   {1.37,   6.14},   {0.93,   5.30}};
  Float_t phoIsoCut[3][2] = {{2.79,   1.53},   {1.60,   1.01},   {0.80,   0.55}};

  Float_t effArea[3][7] = { //[Ch,Nu,Pho][iPhof_eta]
    { 0.0267188, 0.0233977, 0.0236342, 0.0155614, 0.0180204, 0.0204917, 0.0114235},
    { 0.0205471, 0.024657,  0.0315359, 0.0575048, 0.0633432, 0.0697536, 0.220697},
    { 0.0720225, 0.0615237, 0.0317852, 0.0588503, 0.0876866, 0.101231,  0.14981} 
  };

  Int_t phoEB = 0;
  for (Int_t i = 0; i < nPho; ++i) {
    if (fabs(phoSCEta[i]) > 1.4442 && fabs(phoSCEta[i]) < 1.566) continue;
    if (fabs(phoSCEta[i]) > 2.5) continue;

    if (fabs(phoSCEta[i]) >= 1.566) phoEB = 1;
    //if ( phoEleVeto[i] == 0 ) continue ; // turn it off when checking Savvas's ID efficiency
    if (phoHoverE[i] > HoECut[iWP][phoEB]) continue;
    if (phoSigmaIEtaIEta[i] > sieieCut[iWP][phoEB]) continue;

    Int_t i_effArea = 0 ;
    if      (fabs(phoSCEta[i]) < 1.0                               ) i_effArea = 0 ;
    else if (fabs(phoSCEta[i]) > 1.0   && fabs(phoSCEta[i]) < 1.479) i_effArea = 1 ;
    else if (fabs(phoSCEta[i]) > 1.479 && fabs(phoSCEta[i]) < 2.0  ) i_effArea = 2 ;
    else if (fabs(phoSCEta[i]) > 2.0   && fabs(phoSCEta[i]) < 2.2  ) i_effArea = 3 ;
    else if (fabs(phoSCEta[i]) > 2.2   && fabs(phoSCEta[i]) < 2.3  ) i_effArea = 4 ;
    else if (fabs(phoSCEta[i]) > 2.3   && fabs(phoSCEta[i]) < 2.4  ) i_effArea = 5 ;
    else if (fabs(phoSCEta[i]) > 2.4                               ) i_effArea = 6 ;

    if ((phoPFChIso[i] - effArea[0][i_effArea] * rho) > chIsoCut[iWP][phoEB]) continue;

    if (phoEB == 0 ) {
      if ((phoPFNeuIso[i] - effArea[1][i_effArea] * rho - TMath::Exp(0.0030 * phoEt[i] + 1.287)) > nhIsoCut[iWP][phoEB]) continue;
      if ((phoPFPhoIso[i] - effArea[2][i_effArea] * rho - 0.0018 * phoEt[i]) > phoIsoCut[iWP][phoEB]) continue;
    } else if (phoEB == 1) {
      if ((phoPFNeuIso[i] - effArea[1][i_effArea] * rho - 0.0125 * phoEt[i]) > nhIsoCut[iWP][phoEB]) continue;
      if ((phoPFPhoIso[i] - effArea[2][i_effArea] * rho - 0.0077 * phoEt[i]) > phoIsoCut[iWP][phoEB]) continue;
    }

    accepted.push_back(i);
  }

}
