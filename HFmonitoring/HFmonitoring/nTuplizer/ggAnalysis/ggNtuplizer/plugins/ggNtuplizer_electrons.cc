#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/EcalDetId/interface/ESDetId.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
// #include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "CommonTools/Egamma/interface/ConversionTools.h"
//#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"

#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;
using namespace reco;

// (local) variables associated with tree branches
Int_t          nEle_;
vector<int>    eleCharge_;
vector<float>  eleEn_;
vector<float>  eleSCEn_;
vector<float>  eleEcalEn_;
vector<float>  eleD0_;
vector<float>  eleDz_;
vector<float>  eleSIP_;
vector<float>  elePt_;
vector<float>  eleEta_;
vector<float>  elePhi_;
vector<float>  eleCalibPt_;
vector<float>  eleCalibEn_;
vector<float>  eleSCEta_;
vector<float>  eleSCPhi_;
vector<float>  eleSCRawEn_;
vector<float>  eleSCEtaWidth_;
vector<float>  eleSCPhiWidth_;
vector<float>  eleHoverE_;
vector<float>  eleEoverP_;
vector<float>  eleEoverPout_;
vector<float>  eleEoverPInv_;
vector<float>  eleBrem_;
vector<float>  eledEtaAtVtx_;
vector<float>  eledPhiAtVtx_;
vector<float>  eledEtaAtCalo_;
vector<float>  eleSigmaIEtaIEtaFull5x5_;
vector<float>  eleSigmaIPhiIPhiFull5x5_;
vector<int>    eleConvVeto_;
vector<int>    eleMissHits_;
vector<float>  eleESEffSigmaRR_;
vector<float>  elePFChIso_;
vector<float>  elePFPhoIso_;
vector<float>  elePFNeuIso_;
vector<float>  elePFPUIso_;
vector<float>  elePFClusEcalIso_;
vector<float>  elePFClusHcalIso_;


void ggNtuplizer::branchesElectrons(TTree* tree) {

  tree->Branch("nEle",                    &nEle_);
  tree->Branch("eleCharge",               &eleCharge_);
  tree->Branch("eleEn",                   &eleEn_);
  tree->Branch("eleSCEn",                 &eleSCEn_);
  tree->Branch("eleEcalEn",               &eleEcalEn_);
  tree->Branch("eleD0",                   &eleD0_);
  tree->Branch("eleDz",                   &eleDz_);
  tree->Branch("eleSIP",                  &eleSIP_);
  tree->Branch("elePt",                   &elePt_);
  tree->Branch("eleEta",                  &eleEta_);
  tree->Branch("elePhi",                  &elePhi_);
  tree->Branch("eleCalibPt",              &eleCalibPt_);
  tree->Branch("eleCalibEn",              &eleCalibEn_);
  tree->Branch("eleSCEta",                &eleSCEta_);
  tree->Branch("eleSCPhi",                &eleSCPhi_);
  tree->Branch("eleSCRawEn",              &eleSCRawEn_);
  tree->Branch("eleSCEtaWidth",           &eleSCEtaWidth_);
  tree->Branch("eleSCPhiWidth",           &eleSCPhiWidth_);
  tree->Branch("eleHoverE",               &eleHoverE_);
  tree->Branch("eleEoverP",               &eleEoverP_);
  tree->Branch("eleEoverPout",            &eleEoverPout_);
  tree->Branch("eleEoverPInv",            &eleEoverPInv_);
  tree->Branch("eleBrem",                 &eleBrem_);
  tree->Branch("eledEtaAtVtx",            &eledEtaAtVtx_);
  tree->Branch("eledPhiAtVtx",            &eledPhiAtVtx_);
  tree->Branch("eledEtaAtCalo",           &eledEtaAtCalo_);
  tree->Branch("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);
  tree->Branch("eleSigmaIPhiIPhiFull5x5", &eleSigmaIPhiIPhiFull5x5_);
  tree->Branch("eleConvVeto",             &eleConvVeto_);
  tree->Branch("eleMissHits",             &eleMissHits_);
  tree->Branch("eleESEffSigmaRR",         &eleESEffSigmaRR_);
  tree->Branch("elePFChIso",              &elePFChIso_);
  tree->Branch("elePFPhoIso",             &elePFPhoIso_);
  tree->Branch("elePFNeuIso",             &elePFNeuIso_);
  tree->Branch("elePFPUIso",              &elePFPUIso_);
  tree->Branch("elePFClusEcalIso",        &elePFClusEcalIso_);
  tree->Branch("elePFClusHcalIso",        &elePFClusHcalIso_);
  
}

void ggNtuplizer::fillElectrons(const edm::Event &e, const edm::EventSetup &es, math::XYZPoint &pv) {
    
  // cleanup from previous execution
  eleCharge_                  .clear();
  eleEn_                      .clear();
  eleSCEn_                    .clear();
  eleEcalEn_                  .clear();
  eleD0_                      .clear();
  eleDz_                      .clear();
  eleSIP_                     .clear();
  elePt_                      .clear();
  eleEta_                     .clear();
  elePhi_                     .clear();
  eleCalibPt_                 .clear();
  eleCalibEn_                 .clear();
  eleSCEta_                   .clear();
  eleSCPhi_                   .clear();
  eleSCRawEn_                 .clear();
  eleSCEtaWidth_              .clear();
  eleSCPhiWidth_              .clear();
  eleHoverE_                  .clear();
  eleEoverP_                  .clear();
  eleEoverPout_               .clear();
  eleEoverPInv_               .clear();
  eleBrem_                    .clear();
  eledEtaAtVtx_               .clear();
  eledPhiAtVtx_               .clear();
  eledEtaAtCalo_              .clear();
  eleSigmaIEtaIEtaFull5x5_    .clear();
  eleSigmaIPhiIPhiFull5x5_    .clear();
  eleConvVeto_                .clear();
  eleMissHits_                .clear();
  eleESEffSigmaRR_            .clear();
  elePFChIso_                 .clear();
  elePFPhoIso_                .clear();
  elePFNeuIso_                .clear();
  elePFPUIso_                 .clear();
  elePFClusEcalIso_           .clear();
  elePFClusHcalIso_           .clear();

  nEle_ = 0;

  edm::Handle<edm::View<pat::Electron> > electronHandle;
  e.getByToken(electronCollection_, electronHandle);

  edm::Handle<edm::View<pat::Electron> > calibelectronHandle;
  e.getByToken(calibelectronCollection_, calibelectronHandle);

  edm::Handle<pat::PackedCandidateCollection> pfcands;
  e.getByToken(pckPFCandidateCollection_, pfcands);

  if (!electronHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no pat::Electrons in event";
    return;
  }

  if (!calibelectronHandle.isValid()) {
    edm::LogWarning("ggNtuplizer") << "no calibrated pat::Electrons in event";
    return;
  }

  edm::Handle<reco::VertexCollection> recVtxs;
  e.getByToken(vtxLabel_, recVtxs);

  EcalClusterLazyTools       lazyTool    (e, esGetTokens_.get( es), ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  noZS::EcalClusterLazyTools lazyToolnoZS(e, esGetTokens_.get( es), ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  // EcalClusterLazyTools       lazyTool    (e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);
  // noZS::EcalClusterLazyTools lazyToolnoZS(e, es, ebReducedRecHitCollection_, eeReducedRecHitCollection_, esReducedRecHitCollection_);

  for (edm::View<pat::Electron>::const_iterator iEle = electronHandle->begin(); iEle != electronHandle->end(); ++iEle) {

    Float_t corrPt = -1;
    Float_t corrEn = -1;
    for (edm::View<pat::Electron>::const_iterator iCEle = calibelectronHandle->begin(); iCEle != calibelectronHandle->end(); ++iCEle) {

      if (fabs(iEle->eta() - iCEle->eta()) < 0.001 && fabs(iEle->phi() - iCEle->phi()) < 0.001) {
	corrPt = iCEle->pt();
	corrEn = iCEle->energy();
      }
    }
    eleCalibPt_        .push_back(corrPt);
    eleCalibEn_        .push_back(corrEn);

    eleCharge_          .push_back(iEle->charge());
    eleEn_              .push_back(iEle->energy());
    eleD0_              .push_back(iEle->gsfTrack()->dxy(pv));
    eleDz_              .push_back(iEle->gsfTrack()->dz(pv));
    eleSIP_             .push_back(fabs(iEle->dB(pat::Electron::PV3D))/iEle->edB(pat::Electron::PV3D));
    elePt_              .push_back(iEle->pt());
    eleEta_             .push_back(iEle->eta());
    elePhi_             .push_back(iEle->phi());
    eleSCEn_            .push_back(iEle->superCluster()->energy());
    eleEcalEn_          .push_back(iEle->ecalEnergy());
    eleSCEta_           .push_back(iEle->superCluster()->eta());
    eleSCPhi_           .push_back(iEle->superCluster()->phi());
    eleSCRawEn_         .push_back(iEle->superCluster()->rawEnergy());
    eleSCEtaWidth_      .push_back(iEle->superCluster()->etaWidth());
    eleSCPhiWidth_      .push_back(iEle->superCluster()->phiWidth());
    eleHoverE_          .push_back(iEle->hcalOverEcal());

    ///https://cmssdt.cern.ch/SDT/doxygen/CMSSW_7_2_2/doc/html/d8/dac/GsfElectron_8h_source.html
    eleEoverP_          .push_back(iEle->eSuperClusterOverP());
    eleEoverPout_       .push_back(iEle->eEleClusterOverPout());
    eleBrem_            .push_back(iEle->fbrem());
    eledEtaAtVtx_       .push_back(iEle->deltaEtaSuperClusterTrackAtVtx());
    eledPhiAtVtx_       .push_back(iEle->deltaPhiSuperClusterTrackAtVtx());
    eledEtaAtCalo_      .push_back(iEle->deltaEtaSeedClusterTrackAtCalo());
    eleConvVeto_        .push_back((Int_t)iEle->passConversionVeto()); // ConvVtxFit || missHit == 0
    eleMissHits_        .push_back(iEle->gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS));
    eleESEffSigmaRR_    .push_back(lazyTool.eseffsirir(*((*iEle).superCluster())));

    // VID calculation of (1/E - 1/p)
    if (iEle->ecalEnergy() == 0)   eleEoverPInv_.push_back(1e30);
    else if (!std::isfinite(iEle->ecalEnergy()))  eleEoverPInv_.push_back(1e30);
    else  eleEoverPInv_.push_back((1.0 - iEle->eSuperClusterOverP())/iEle->ecalEnergy());


    reco::GsfElectron::PflowIsolationVariables pfIso = iEle->pfIsolationVariables();
    elePFChIso_         .push_back(pfIso.sumChargedHadronPt);
    elePFPhoIso_        .push_back(pfIso.sumPhotonEt);
    elePFNeuIso_        .push_back(pfIso.sumNeutralHadronEt);
    elePFPUIso_         .push_back(pfIso.sumPUPt);


    eleSigmaIEtaIEtaFull5x5_    .push_back(iEle->full5x5_sigmaIetaIeta());
    eleSigmaIPhiIPhiFull5x5_    .push_back(iEle->full5x5_sigmaIphiIphi());

    nEle_++;
  }


}
