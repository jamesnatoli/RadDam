#ifndef ggNtuplizer_h
#define ggNtuplizer_h

#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct3.h"
#include <HepMC3/GenEvent.h>
#include <HepMC3/GenPdfInfo.h>

#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
//#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"

#include "DataFormats/PatCandidates/interface/MET.h"
using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class ggNtuplizer : public edm::one::EDAnalyzer<edm::one::SharedResources> {
 public:

  explicit ggNtuplizer(const edm::ParameterSet&);
  ~ggNtuplizer();
  
  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  
  //   virtual void beginJob() {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  //   virtual void endJob() {};
  
  void initTriggerFilters(const edm::Event&);
  ULong64_t matchSingleElectronTriggerFilters(double pt, double eta, double phi);
  //ULong64_t matchL1TriggerFilters(double pt, double eta, double phi);
  
  Double_t deltaPhi(Double_t phi1, Double_t phi2);
  Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);

  void branchesGlobalEvent(TTree*);
  void branchesElectrons  (TTree*);
  void branchesHFElectrons(TTree*);
  void branchesGenInfo    (TTree*, edm::Service<TFileService>&);
  void branchesGenPart    (TTree*);
  void branchesMET        (TTree*);

  void fillGlobalEvent(const edm::Event&, const edm::EventSetup&);
  void fillElectrons  (const edm::Event&, const edm::EventSetup&, math::XYZPoint&);
  void fillHFElectrons(const edm::Event&);
  void fillGenInfo    (const edm::Event&);
  void fillGenPart    (const edm::Event&);
  void fillMET        (const edm::Event&, const edm::EventSetup&);

  vector<int> newparticles_;
  bool doNoHFMET_;
  bool doGenParticles_;
  bool runOnParticleGun_;
  bool addFilterInfoMINIAOD_;  
  
  double trgFilterDeltaPtCut_;
  double trgFilterDeltaRCut_;
  
  edm::EDGetTokenT<trigger::TriggerEvent>           trgEventLabel_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsLabel_;
  edm::EDGetTokenT<edm::TriggerResults>             trgResultsLabel_;
  string                                            trgResultsProcess_;
  edm::EDGetTokenT<edm::TriggerResults>             patTrgResultsLabel_;
  
  edm::EDGetTokenT<edm::View<pat::MET> >           pfMETlabel_;
  edm::EDGetTokenT<edm::View<pat::MET> >            puppiMETlabel_;
  edm::EDGetTokenT<GenEventInfoProduct>         generatorLabel_;
  edm::EDGetTokenT<vector<reco::GenParticle> >  genParticlesCollection_;
  edm::EDGetTokenT<vector<PileupSummaryInfo> >  puCollection_;
  edm::EDGetTokenT<reco::VertexCollection>         vtxLabel_;
  edm::EDGetTokenT<double>                         rhoLabel_;
  edm::EDGetTokenT<double>                         rhoCentralLabel_;
  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  edm::EDGetTokenT<edm::View<pat::Electron> >      calibelectronCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           ebReducedRecHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           eeReducedRecHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           esReducedRecHitCollection_; 
  edm::EDGetTokenT<edm::View<pat::Jet> >           jetsAK4Label_;
  edm::EDGetTokenT<pat::PackedCandidateCollection> pckPFCandidateCollection_;
  
  edm::EDGetTokenT<bool> BadPFMuonFilterUpdateDz_;
   
  EcalClusterLazyTools::ESGetTokens esGetTokens_;
  noZS::EcalClusterLazyTools::ESGetTokens noZSesGetTokens_;

  TTree   *tree_;
  TH1F    *hEvents_;
};

#endif
