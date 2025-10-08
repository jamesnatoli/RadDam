#include "map"
#include "FWCore/Common/interface/TriggerNames.h"
#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;

// local variables: per-filter per-electron/muon/photon/jet arrays of matched trigger objects
// NOTE: number of elements in the arrays equals sizeof(ULong64_t)
vector<float> trgSingleElePt[64], trgSingleEleEta[64], trgSingleElePhi[64];
//vector<float> trgL1Eta[64],  trgL1Phi[64];

void ggNtuplizer::initTriggerFilters(const edm::Event &e) {
  // Fills the arrays above.

  // cleanup from previous execution
  for (size_t i = 0; i < 64; ++i) {
    trgSingleElePt [i].clear();
    trgSingleEleEta[i].clear();
    trgSingleElePhi[i].clear();
    //trgL1Eta[i].clear();
    //trgL1Phi[i].clear();
  }

  // filter => index (in trg*[] arrays) mappings
  static std::map<string,size_t> eleSingleFilters;
  //static std::map<string,size_t> l1Filters;

  // one-time initialization
  if (eleSingleFilters.size() == 0) {
  
     //HLT_Ele32_WPTight_Gsf_v
    eleSingleFilters["hltEle32WPTightGsfTrackIsoFilter"] = 0;
    //HLT_Ele30_WPTight_Gsf_v
    eleSingleFilters["hltEle30WPTightGsfTrackIsoFilter"] = 1;
    //HLT_Ele38_WPTight_Gsf_v no energy requirement
    eleSingleFilters["hltEle38noerWPTightGsfTrackIsoFilter"] = 2;
    //HLT_Ele40_WPTight_Gsf_v
    eleSingleFilters["hltEle40noerWPTightGsfTrackIsoFilter"] = 3;
    //hltEle35noerWPTightGsfTrackIsoFilter
    eleSingleFilters["hltEle35noerWPTightGsfTrackIsoFilter"] = 4;
     
    //else { throw std::invalid_argument("You need to select a year to select HLT path. The switch is in cmssw config file"); }
    
  } //elefilter
 
  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerHandleMiniAOD;
  e.getByToken(triggerObjectsLabel_, triggerHandleMiniAOD);

  edm::Handle<edm::TriggerResults> trgResultsHandle;
  e.getByToken(trgResultsLabel_, trgResultsHandle);

  edm::Handle<std::string> filterLabels_;
  e.getByLabel("slimmedPatTrigger:filterLabels", filterLabels_);

  //const edm::TriggerNames &names = e.triggerNames(*trgResultsHandle);

  for (pat::TriggerObjectStandAlone obj : *triggerHandleMiniAOD) {
    //obj.unpackPathNames(names);
    //obj.unpackPathNames(e);
    obj.unpackFilterLabels(e, *trgResultsHandle);

    // loop over filters    
    for (size_t iF = 0; iF < obj.filterLabels().size(); ++iF) {
      string label = obj.filterLabels()[iF];

      //cout<<"label : "<<iF<<" "<<label<<endl;

      std::map<string,size_t>::iterator idxEleSingle = eleSingleFilters.find(label);
      //std::map<string,size_t>::iterator idxL1 = l1Filters.find(label);

      // single electron filters
      if (idxEleSingle != eleSingleFilters.end()) {
        size_t idx = idxEleSingle->second;
        trgSingleElePt [idx].push_back(obj.pt());
        trgSingleEleEta[idx].push_back(obj.eta());
        trgSingleElePhi[idx].push_back(obj.phi());
	//cout<<idx<<" "<<obj.pt()<<" "<<obj.eta()<<" "<<obj.phi()<<endl;
      }
      
      // L1 filters
      /*if (idxL1 != l1Filters.end()) {
        size_t idx = idxL1->second;
        trgL1Eta[idx].push_back(obj.eta());
        trgL1Phi[idx].push_back(obj.phi());
      }*/
    }
  }

}//bracket out of range

ULong64_t ggNtuplizer::matchSingleElectronTriggerFilters(double pt, double eta, double phi) {

  // bits in the return value correspond to decisions from filters defined above
  ULong64_t result = 0;

  for (size_t f = 0; f < 64; ++f)
    for (size_t v = 0; v < trgSingleElePt[f].size(); ++v)
      if (fabs(pt - trgSingleElePt[f][v])/trgSingleElePt[f][v] < trgFilterDeltaPtCut_ &&
          deltaR(eta, phi, trgSingleEleEta[f][v], trgSingleElePhi[f][v]) < trgFilterDeltaRCut_) {
        result |= (1<<f);
        break;
      }

  return result;
}

/*ULong64_t ggNtuplizer::matchL1TriggerFilters(double pt, double eta, double phi) {

  // bits in the return value correspond to decisions from filters defined above
  ULong64_t result = 0;

  for (size_t f = 0; f < 64; ++f)
    for (size_t v = 0; v < trgL1Eta[f].size(); ++v)
      if (deltaR(eta, phi, trgL1Eta[f][v], trgL1Phi[f][v]) < trgFilterDeltaRCut_) {
        result |= (1<<f);
        break;
      }

  return result;
}*/

Double_t ggNtuplizer::deltaPhi(Double_t phi1, Double_t phi2) {

  Double_t dPhi = phi1 - phi2;
  if (dPhi > TMath::Pi()) dPhi -= 2.*TMath::Pi();
  if (dPhi < -TMath::Pi()) dPhi += 2.*TMath::Pi();

  return dPhi;
}

Double_t ggNtuplizer::deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2) {

  Double_t dEta, dPhi ;
  dEta = eta1 - eta2;
  dPhi = deltaPhi(phi1, phi2);

  return sqrt(dEta*dEta+dPhi*dPhi);
}

