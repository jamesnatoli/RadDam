#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

// (local) variables associated with tree branches
Int_t       run_;
Long64_t    event_;
Int_t       lumis_;
Int_t       nVtx_;
float       rho_;
float       rhoCentral_;

//double      L1ECALPrefire_;
//double      L1ECALPrefireUp_;
//double      L1ECALPrefireDown_;
ULong64_t   HLTEleMuX_;

void ggNtuplizer::branchesGlobalEvent(TTree* tree) {

  tree->Branch("run",     &run_);
  tree->Branch("event",   &event_);
  tree->Branch("lumis",   &lumis_);
  tree->Branch("nVtx",                 &nVtx_);
  tree->Branch("rho",                  &rho_);
  tree->Branch("rhoCentral",           &rhoCentral_);
  tree->Branch("HLTEleMuX",            &HLTEleMuX_);
  /*tree->Branch("L1ECALPrefire",        &L1ECALPrefire_);
  tree->Branch("L1ECALPrefireUp",      &L1ECALPrefireUp_);
  tree->Branch("L1ECALPrefireDown",    &L1ECALPrefireDown_);*/
}

void ggNtuplizer::fillGlobalEvent(const edm::Event& e, const edm::EventSetup& es) {

  edm::Handle<double> rhoHandle;
  e.getByToken(rhoLabel_, rhoHandle);

  edm::Handle<double> rhoCentralHandle;
  e.getByToken(rhoCentralLabel_, rhoCentralHandle);

  run_    = e.id().run();
  event_  = e.id().event();
  lumis_  = e.luminosityBlock();
  rho_    = *(rhoHandle.product());
  if (rhoCentralHandle.isValid()) rhoCentral_ = *(rhoCentralHandle.product());
  else rhoCentral_ = -99.;

  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);
  
  nVtx_     = -1;
  if (vtxHandle.isValid()) {
    nVtx_     = 0;   

    for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {
      nVtx_++;

    }
  } 
  else edm::LogWarning("ggNtuplizer") << "Primary vertices info not unavailable";
  
  /*// L1 ECAL prefiring
  L1ECALPrefire_     = 1;
  L1ECALPrefireUp_   = 1;
  L1ECALPrefireDown_ = 1;

  if (L1ECALPrefire_) {
    edm::Handle<double> theprefweight;
    e.getByToken(prefweight_token_, theprefweight);
    L1ECALPrefire_    = (*theprefweight);

    edm::Handle<double> theprefweightup;
    e.getByToken(prefweightup_token_, theprefweightup);
    L1ECALPrefireUp_   = (*theprefweightup);

    edm::Handle< double > theprefweightdown;
    e.getByToken(prefweightdown_token_, theprefweightdown);
    L1ECALPrefireDown_ = (*theprefweightdown);
  } */

  // HLT treatment
  HLTEleMuX_            = 0;
  
  edm::Handle<edm::TriggerResults> trgResultsHandle;
  e.getByToken(trgResultsLabel_, trgResultsHandle);
  
  /*bool cfg_changed = true;
  hltPrescaleProvider_.init(e.getRun(), es, trgResultsProcess_, cfg_changed);
  HLTConfigProvider const&  hltCfg = hltPrescaleProvider_.hltConfigProvider();
  const int prescaleSet = hltPrescaleProvider_.prescaleSet(e,es);*/

  const edm::TriggerNames &trgNames = e.triggerNames(*trgResultsHandle);

  for (size_t i = 0; i < trgNames.size(); ++i) {
    const string &name = trgNames.triggerName(i);

    // HLT name => bit correspondence
    int bitEleMuX = -1;
    //int bitPho    = -1;
    //int bitJet    = -1;

    //if (year_ == 2024) {
    
      if      (name.find("HLT_Ele32_WPTight_Gsf_v")                      != string::npos) bitEleMuX =  0;
      else if (name.find("HLT_Ele30_WPTight_Gsf_v")                      != string::npos) bitEleMuX =  1; 
      else if (name.find("HLT_Ele38_WPTight_Gsf_v")                      != string::npos) bitEleMuX =  2;
      else if (name.find("HLT_Ele40_WPTight_Gsf_v")                      != string::npos) bitEleMuX =  3; 
      else if (name.find("HLT_Ele35_WPTight_Gsf_v")             	 != string::npos) bitEleMuX = 4;
    //}
	
    // indicates prescaling and whether trigger was fired or not
    //ULong64_t isPrescaled = (hltCfg.prescaleValue(prescaleSet, name)!=1) ? 1 : 0;
    ULong64_t isFired     = (trgResultsHandle->accept(i)) ? 1 : 0;
    //ULong64_t isrejectedByHLTPS = (hltCfg.moduleType(hltCfg.moduleLabel(i,trgResultsHandle->index(i)))=="HLTPrescaler") ? 1: 0;

    if (bitEleMuX >= 0) {
      HLTEleMuX_            |= (isFired << bitEleMuX);
      //HLTEleMuXIsPrescaled_ |= (isPrescaled << bitEleMuX);
    }
    
    	  
  }
}
