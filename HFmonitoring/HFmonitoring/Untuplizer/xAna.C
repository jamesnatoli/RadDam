// ROOT Includes
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

// C++ Includes
#include <vector>
#include <iostream>

using namespace std;
// Personal Includes
#include "untuplizer.h"
#include "Utilities.h"
#include "PhotonSelections.h"
#include "../progressBar.C"

// Main work function
void xAna( TreeReader* pdata) {
  TreeReader data = *pdata;

  int nvtx;
  float rho;
  int nele;
  int run;
  Long64_t event;
  int lumis;
  vector<float> ele_pt;
  vector<float> ele_eta;
  vector<float> ele_phi;
  vector<int>   ele_mediumID;
  int nhf;
  vector<float> hf_en;
  vector<float> hf_pt;
  vector<float> hf_eta;
  vector<float> hf_phi;
  vector<float> hf_iso;
  vector<float> hf_ecal;
  vector<float> hf_hcal;
  vector<int>   hf_match;
  int nmc;
  vector<float> mc_pt;
  vector<float> mc_eta;
  vector<float> mc_phi;
  
  TFile* file = TFile::Open("output_data.root", "RECREATE");
  TH1F* hh = new TH1F("hh", "", 100, 50, 150);
  TTree* tree = new TTree("miniTree", "miniTree");
  tree->Branch("run", &run);
  tree->Branch("event", &event);
  tree->Branch("lumis", &lumis);
  tree->Branch("nvtx",       &nvtx);
  tree->Branch("nele",       &nele);
  tree->Branch("ele_pt",     &ele_pt);
  tree->Branch("ele_eta",    &ele_eta);
  tree->Branch("ele_phi",    &ele_phi);
  tree->Branch("ele_mediumID",     &ele_mediumID);
  tree->Branch("nhf",        &nhf);
  tree->Branch("hf_en",      &hf_en);
  tree->Branch("hf_pt",      &hf_pt);
  tree->Branch("hf_eta",     &hf_eta);
  tree->Branch("hf_phi",     &hf_phi);
  tree->Branch("hf_iso",     &hf_iso);
  tree->Branch("hf_ecal",    &hf_ecal);
  tree->Branch("hf_hcal",    &hf_hcal);
  tree->Branch("hf_match",   &hf_match);
  tree->Branch("nmc",        &nmc);
  tree->Branch("mc_pt",      &mc_pt);
  tree->Branch("mc_eta",     &mc_eta);
  tree->Branch("mc_phi",     &mc_phi);

  bool condor = false;
  bool isMC = true;
  
  Long64_t nev = data.GetEntriesFast();
  std::cout << "Processing " << nev << " events..." << std::endl;
  std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
  for (Long64_t ev = 0; ev < nev; ++ev) {
    //for (Long64_t ev = 0; ev < 100000; ++ev) {
    data.GetEntry(ev);    
    
    vector<TLorentzVector> genElectrons;

    if ( isMC ) {
      nmc = data.GetInt("nMC");
      Int_t*   mcPID       = data.GetPtrInt("mcPID");
      Int_t*   mcParentage = data.GetPtrInt("mcParentage");
      Float_t* mcPt        = data.GetPtrFloat("mcPt");
      Float_t* mcEta       = data.GetPtrFloat("mcEta");
      Float_t* mcPhi       = data.GetPtrFloat("mcPhi");
      Int_t*   mcStatus    = data.GetPtrInt("mcStatus");
      
      for(int i = 0; i != nmc; ++i) {
	if ( abs(mcPID[i]) == 11 && mcStatus[i] == 1 ) {
	  bool z = (mcParentage[i] & (1 << 3)) > 0;
	  if ( z ) {
	    TLorentzVector gen;
	    gen.SetPtEtaPhiM(mcPt[i], mcEta[i], mcPhi[i], 0);
	    genElectrons.push_back(gen);
	  }
	}
      }
      if ( nmc != 0 && genElectrons.size() != 2 ) {
	continue;
      }
    }

    nvtx = 0;
    rho  = 0;

    nele = 0;
    ele_pt .clear();
    ele_eta.clear();
    ele_phi.clear();
    ele_mediumID .clear();

    nhf = 0;
    hf_en.clear();
    hf_pt.clear();
    hf_eta.clear();
    hf_phi.clear();
    hf_iso.clear();
    hf_ecal.clear();
    hf_hcal.clear();
    hf_match.clear();

    nmc = 0;
    mc_pt.clear();
    mc_eta.clear();
    mc_phi.clear();

    if (!condor)
      progressBar( ev, nev, start);
    // if ( ev%100000 == 0 ) cout << "Processed: " << ev
    //                            << " / " << nev
    //                            << " (" << (100.0 * ev / nev)
    //                            << "%)"
    //                            << endl;
    
    Int_t nHFEle = 0;
    Float_t* hfeleEn = 0;
    Float_t* hfelePt = 0;
    Float_t* hfeleEta = 0;
    Float_t* hfelePhi = 0;
    Float_t* hfeleIso = 0;
    Int_t*   hfeleType = 0;
    Float_t* hfeleECALEn = 0;
    Float_t* hfeleHCALEn = 0;

    nHFEle      = data.GetInt("npfHF");
    if ( nHFEle != 0 ) {
      hfeleEn     = data.GetPtrFloat("pfHFEn");
      hfelePt     = data.GetPtrFloat("pfHFPt");
      hfeleEta    = data.GetPtrFloat("pfHFEta");
      hfelePhi    = data.GetPtrFloat("pfHFPhi");
      hfeleIso    = data.GetPtrFloat("pfHFIso");
      hfeleECALEn = data.GetPtrFloat("pfHFECALEn");
      hfeleHCALEn = data.GetPtrFloat("pfHFHCALEn");
    }
    
    for(int i = 0; i != nHFEle; ++i) {      
      double iso   = hfeleIso[i];
      hf_en.push_back(hfeleEn[i]);
      hf_pt.push_back(hfelePt[i]);
      hf_eta.push_back(hfeleEta[i]);
      hf_phi.push_back(hfelePhi[i]);
      hf_iso.push_back(iso);
      hf_ecal.push_back(hfeleECALEn[i]);
      hf_hcal.push_back(hfeleHCALEn[i]);

      if ( isMC ) {
	TLorentzVector hf;
	hf.SetPtEtaPhiM(hfelePt[i], hfeleEta[i], hfelePhi[i], 0);
	double dR = 1000;
	int    indexGen = -1;
	for(int igen = 0; igen != (int)genElectrons.size(); ++igen) {
	  TLorentzVector gen = genElectrons[igen];
	  double currentDR = gen.DeltaR(hf);
	  if ( currentDR < dR ) {
	    dR = currentDR;
	    indexGen = igen;
	  }
	}
	if ( dR < 0.2 ) hf_match.push_back(indexGen);
	else            hf_match.push_back(-1);
      } else {
	hf_match.push_back(-2);
      } // if ( isMC )
      ++nhf;
      
    } // for( nHFEle)
   
    Int_t nEle = 0;
    Float_t*  elePt = 0;
    Float_t*  eleEta = 0;
    Float_t*  eleSCEta = 0;
    Float_t*  elePhi = 0;
    Int_t*    eleConvVeto = 0;
    Int_t*    eleMissHits = 0;
    Float_t*  eleEoverPInv = 0;
    Float_t*  eleSigmaIEtaIEtaFull5x5 = 0;
    Float_t*  eledEtaAtVtx = 0;
    Float_t*  eledPhiAtVtx = 0;
    Float_t*  eleHoverE = 0;
    Float_t*  elePFChIso = 0;
    Float_t*  elePFPhoIso = 0;
    Float_t*  elePFNeuIso = 0;
    Float_t*  eleESEffSigmaRR = 0;

    nvtx     = data.GetInt("nVtx");
    rho      = data.GetFloat("rho");
    nEle     = data.GetInt("nEle");
    if ( nEle != 0 ) {
      elePt    = data.GetPtrFloat("elePt");
      eleEta   = data.GetPtrFloat("eleEta");
      eleSCEta = data.GetPtrFloat("eleSCEta");
      elePhi   = data.GetPtrFloat("elePhi");
      eleConvVeto   = data.GetPtrInt("eleConvVeto");
      eleMissHits   = data.GetPtrInt("eleMissHits");
      eleEoverPInv   = data.GetPtrFloat("eleEoverPInv");
      eleSigmaIEtaIEtaFull5x5   = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5");
      eledEtaAtVtx   = data.GetPtrFloat("eledEtaAtVtx");
      eledPhiAtVtx   = data.GetPtrFloat("eledPhiAtVtx");
      eleHoverE   = data.GetPtrFloat("eleHoverE");
      elePFChIso   = data.GetPtrFloat("elePFChIso");
      elePFPhoIso   = data.GetPtrFloat("elePFPhoIso");
      elePFNeuIso   = data.GetPtrFloat("elePFNeuIso");
      eleESEffSigmaRR   = data.GetPtrFloat("eleESEffSigmaRR");
    }
    
    for(int iele = 0; iele != nEle; ++iele) {
      ele_pt .push_back(elePt[iele]);
      ele_eta.push_back(eleEta[iele]);
      ele_phi.push_back(elePhi[iele]);
      ++nele;
      
      // Looks like this is where the Cut-Based Electron ID is implemented...
      // should these be barrel or endcap? 
      // https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun3
      double eleECALpt = elePt[iele];
      if (eleECALpt == 0) eleECALpt = 0.0001;
      float relIsoRhoCor  = (elePFChIso[iele] + std::max((float)0.0, elePFNeuIso[iele] + elePFPhoIso[iele] - rho*eleESEffSigmaRR[iele]))/eleECALpt; 
      int isMediumEle = 0;
      
      /* These are the old Run2 Electron ID things
      if (eleConvVeto[iele] == 1 && // pass conversion veto
	  eleMissHits[iele] < 2 && // xpected missing inner hits <= 
	  eleEoverPInv[iele] < 0.134 && // abs( 1/E - 1/p) < 
	  eleSigmaIEtaIEtaFull5x5[iele] < 0.00998 &&  // full5x5_sigmaIetaIeta
	  eledEtaAtVtx[iele] < 0.00311 && 
	  eledPhiAtVtx[iele] < 0.103 && 
	  eleHoverE[iele] < 0.253 && // H / E < 0.253
	  relIsoRhoCor < 0.0695 && // RelIsoWithEA < 
	  fabs(eleSCEta[iele]) < 1.479 ) // AH! this selects BARRELL ELECTRONS
	isMediumEle = 1 ;
      if (eleConvVeto[iele] == 1 && 
	  eleMissHits[iele] < 2 && 
	  eleEoverPInv[iele] < 0.13 && 
	  eleSigmaIEtaIEtaFull5x5[iele] < 0.0298 && 
	  eledEtaAtVtx[iele] < 0.00609 && 
	  eledPhiAtVtx[iele] < 0.045 && 
	  eleHoverE[iele] < 0.0878 && 
	  relIsoRhoCor < 0.0821 && 
	  fabs(eleSCEta[iele]) > 1.479 ) // and this selects ENDCAP ELECTRONS
	isMediumEle = 1 ;
      ele_mediumID.push_back(isMediumEle);
      */

      if (eleConvVeto[iele] == 1 && // pass conversion veto
	  eleMissHits[iele] < 2 && // xpected missing inner hits <= 
	  eleEoverPInv[iele] < 0.134 && // abs( 1/E - 1/p) < 
	  eleSigmaIEtaIEtaFull5x5[iele] < 0.00998 &&  // full5x5_sigmaIetaIeta
	  eledEtaAtVtx[iele] < 0.00311 && 
	  eledPhiAtVtx[iele] < 0.103 && 
	  eleHoverE[iele] < 0.253 && // H / E < 0.253
	  relIsoRhoCor < 0.0695 && // RelIsoWithEA < 
	  fabs(eleSCEta[iele]) < 1.479 ) // AH! this selects BARRELL ELECTRONS
	isMediumEle = 1 ;
      if (eleConvVeto[iele] == 1 && 
	  eleMissHits[iele] < 2 && 
	  eleEoverPInv[iele] < 0.13 && 
	  eleSigmaIEtaIEtaFull5x5[iele] < 0.0298 && 
	  eledEtaAtVtx[iele] < 0.00609 && 
	  eledPhiAtVtx[iele] < 0.045 && 
	  eleHoverE[iele] < 0.0878 && 
	  relIsoRhoCor < 0.0821 && 
	  fabs(eleSCEta[iele]) > 1.479 ) // and this selects ENDCAP ELECTRONS
	isMediumEle = 1 ;
      ele_mediumID.push_back(isMediumEle);

    } // for (int iele...
    
    // Selection criteria, either two electrons with pT 10 GeV in EB/EE
    // or one electron with 10 GeV in EB/EE and at least on HF electron
    // or two electrons in HF
    bool twoElectrons  = nele > 1 && ele_pt[1] > 10.0;
    bool electronAndHF = nele > 0 && ele_pt[0] > 10.0 && nhf > 0;
    bool twoHF         = nhf > 1;
    bool passEvent =  twoElectrons || electronAndHF || twoHF;
    //bool passEvent = nele > 0 && ele_pt[0] > 15.0 && nhf > 0 && hf_pt[0] > 10.0;
    //if ( !passEvent ) continue;

    run = data.GetInt("run");
    event = data.GetLong64("event");
    lumis = data.GetInt("lumis");
    // std::cout << "topick " << run << ":" << lumis << ":" << event << std::endl;
    

    tree->Fill();
  } // End Event Loop
  std::cout.flush();
  std::cout << "\n";
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << ">>> Finished in " << duration.count() << " seconds" << std::endl;
  tree->Write();
}

void xAna(std::vector<std::string> inpaths) {
  TreeReader* data = new TreeReader( inpaths);
  xAna( data);
}

void xAna(const char** inpaths, int npaths) {
  TreeReader* data = new TreeReader(inpaths, npaths);
  xAna( data);
}

// for use with HTCondor
int main( int argc, char** argv) {
  std::cout << ">>> Starting to Untuple... " << std::endl;
  std::vector<std::string> inpaths = {};
  if (argc < 2) {
    std::cout << "!!! ERROR !!! You must pass at least one file" << std::endl;
    return 1;
  } else {
    if ((argc == 2) && (std::string(argv[1]).find(".txt") != std::string::npos)) { // file as input
      std::string line;
      ifstream infile(argv[1]);
      while ( getline( infile, line))
	inpaths.push_back( line);
    } else {
      for (int i = 1; i < argc; ++i)
	inpaths.push_back( argv[i]);
    }
  }

  // for (auto ele : inpaths)
  //   std::cout << ele << std::endl;

  xAna( inpaths);
  std::cout << "All done!" << std::endl;
  return 0;
}
