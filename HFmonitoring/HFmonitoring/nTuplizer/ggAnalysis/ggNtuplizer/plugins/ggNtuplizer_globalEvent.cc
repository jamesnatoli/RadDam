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

void ggNtuplizer::branchesGlobalEvent(TTree* tree) {

  tree->Branch("run",     &run_);
  tree->Branch("event",   &event_);
  tree->Branch("lumis",   &lumis_);
  tree->Branch("nVtx",                 &nVtx_);
  tree->Branch("rho",                  &rho_);
  tree->Branch("rhoCentral",           &rhoCentral_);

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

}
