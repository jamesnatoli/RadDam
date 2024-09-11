#define Analysis18_cxx
#include "Analysis18.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "CMSStyle.C"

using namespace std;
void beautify(TH1F* plot, TString xTitle, TString yTitle, int color) {
  plot->GetXaxis()->SetTitle(xTitle);
  plot->GetYaxis()->SetTitle(yTitle);
  plot->SetMarkerColor(color);
  plot->SetLineColor(color);
  return;
}
void beautify(TH2F* plot, TString xTitle, TString yTitle, int color) {
  plot->GetXaxis()->SetTitle(xTitle);
  plot->GetYaxis()->SetTitle(yTitle);
  plot->SetMarkerColor(color);
  plot->SetLineColor(color);
  return;
}

int getRunIndex(int run) {
  return -1;
}
int getEtaIndex(float eta) {
  return -1;
}

float getRaddamCorrection(int run, float eta) {
  return 0;
}

std::string getOutName( bool isData, bool usePU, bool useRaddam, std::string tag="") {
  std::string outdir  = "outplots/";
  std::string outname = outdir + "outplots2022";
  if (isData)
    outname += "_data";
  else
    outname += "_mc";
  
  if (usePU)
    outname += "_PU";
  else
    outname += "_noPU";

  if (useRaddam)
    outname += "_RaddCorr";

  if (tag != "")
    outname = outname + "_" + tag;
  
   outname += ".root";
   return outname;
}

void Analysis18::Loop() 
{
   CMSStyle();
   if (fChain == 0) return;
   
   bool usePU = false;
   bool useRaddam = false;
   std::string outname = getOutName( this->isData, usePU, useRaddam, "oldTest");
   std::cout << ">>> Creating outfile: " << outname << std::endl;
    
   TFile* out = TFile::Open( outname.c_str(), "RECREATE");

   TH1F* h_mass = new TH1F("h_mass", "", 140, 20, 160);
   beautify(h_mass, "M_{e, hf} (GeV)", "Events / 1 GeV", 2);
   TH1F* h_nvtx = new TH1F("h_nvtx", "", 60, 0, 60);
   beautify(h_nvtx, "nVtx", "Events", 2);

   TH1F* h_lsRatio = new TH1F("h_lsRatio", "", 80, 0, 20);
   beautify(h_lsRatio, "Long/Short Fiber Energy Ratio", "Events", 2);
    
   TH1F* h_mass_iEta33_before = new TH1F("h_mass_iEta33_before", "", 140, 20, 160);
   beautify(h_mass_iEta33_before, "M_{e, hf} (GeV)", "Events / 1 GeV", 2);
   TH1F* h_mass_iEta33_after = new TH1F("h_mass_iEta33_after", "", 140, 20, 160);
   beautify(h_mass_iEta33_after, "M_{e, hf} (GeV)", "Events / 1 GeV", 2);
 
   TH1F* etaPlus30  = new TH1F("etaPlus30", "", 140, 20, 160);
   TH1F* etaPlus31  = new TH1F("etaPlus31", "", 140, 20, 160);
   TH1F* etaPlus32  = new TH1F("etaPlus32", "", 140, 20, 160);
   TH1F* etaPlus33  = new TH1F("etaPlus33", "", 140, 20, 160);
   TH1F* etaPlus34  = new TH1F("etaPlus34", "", 140, 20, 160);
   TH1F* etaPlus35  = new TH1F("etaPlus35", "", 140, 20, 160);
   TH1F* etaPlus36  = new TH1F("etaPlus36", "", 140, 20, 160);
   TH1F* etaPlus37  = new TH1F("etaPlus37", "", 140, 20, 160);
   TH1F* etaPlus38  = new TH1F("etaPlus38", "", 140, 20, 160);
   TH1F* etaPlus39  = new TH1F("etaPlus39", "", 140, 20, 160);
   TH1F* etaPlus40  = new TH1F("etaPlus40", "", 140, 20, 160);
   TH1F* etaPlus41  = new TH1F("etaPlus41", "", 140, 20, 160);
   TH1F* etaMinus30  = new TH1F("etaMinus30", "", 140, 20, 160);
   TH1F* etaMinus31  = new TH1F("etaMinus31", "", 140, 20, 160);
   TH1F* etaMinus32  = new TH1F("etaMinus32", "", 140, 20, 160);
   TH1F* etaMinus33  = new TH1F("etaMinus33", "", 140, 20, 160);
   TH1F* etaMinus34  = new TH1F("etaMinus34", "", 140, 20, 160);
   TH1F* etaMinus35  = new TH1F("etaMinus35", "", 140, 20, 160);
   TH1F* etaMinus36  = new TH1F("etaMinus36", "", 140, 20, 160);
   TH1F* etaMinus37  = new TH1F("etaMinus37", "", 140, 20, 160);
   TH1F* etaMinus38  = new TH1F("etaMinus38", "", 140, 20, 160);
   TH1F* etaMinus39  = new TH1F("etaMinus39", "", 140, 20, 160);
   TH1F* etaMinus40  = new TH1F("etaMinus40", "", 140, 20, 160);
   TH1F* etaMinus41  = new TH1F("etaMinus41", "", 140, 20, 160);
    
   TH1F* eta30lsRatio = new TH1F("eta30lsRatio", "", 80, 0, 20);
   beautify(eta30lsRatio, "Long/Short Fiber Energy Ratio (i#eta30)", "Events", 2);
   TH1F* eta31lsRatio = new TH1F("eta31lsRatio", "", 80, 0, 20);
   beautify(eta31lsRatio, "Long/Short Fiber Energy Ratio (i#eta31)", "Events", 2);
   TH1F* eta32lsRatio = new TH1F("eta32lsRatio", "", 80, 0, 20);
   beautify(eta32lsRatio, "Long/Short Fiber Energy Ratio (i#eta32)", "Events", 2);
   TH1F* eta33lsRatio = new TH1F("eta33lsRatio", "", 80, 0, 20);
   beautify(eta33lsRatio, "Long/Short Fiber Energy Ratio (i#eta33)", "Events", 2);
   TH1F* eta34lsRatio = new TH1F("eta34lsRatio", "", 80, 0, 20);
   beautify(eta34lsRatio, "Long/Short Fiber Energy Ratio (i#eta34)", "Events", 2);
   TH1F* eta35lsRatio = new TH1F("eta35lsRatio", "", 80, 0, 20);
   beautify(eta35lsRatio, "Long/Short Fiber Energy Ratio (i#eta35)", "Events", 2);
   TH1F* eta36lsRatio = new TH1F("eta36lsRatio", "", 80, 0, 20);
   beautify(eta36lsRatio, "Long/Short Fiber Energy Ratio (i#eta36)", "Events", 2);
   TH1F* eta37lsRatio = new TH1F("eta37lsRatio", "", 80, 0, 20);
   beautify(eta37lsRatio, "Long/Short Fiber Energy Ratio (i#eta37)", "Events", 2);
   TH1F* eta38lsRatio = new TH1F("eta38lsRatio", "", 80, 0, 20);
   beautify(eta38lsRatio, "Long/Short Fiber Energy Ratio (i#eta38)", "Events", 2);
   TH1F* eta39lsRatio = new TH1F("eta39lsRatio", "", 80, 0, 20);
   beautify(eta39lsRatio, "Long/Short Fiber Energy Ratio (i#eta39)", "Events", 2);
   TH1F* eta40lsRatio = new TH1F("eta40lsRatio", "", 80, 0, 20);
   beautify(eta40lsRatio, "Long/Short Fiber Energy Ratio (i#eta40)", "Events", 2);
   TH1F* eta41lsRatio = new TH1F("eta41lsRatio", "", 80, 0, 20);
   beautify(eta41lsRatio, "Long/Short Fiber Energy Ratio (i#eta41)", "Events", 2);

   TH1F* phi1  = new TH1F("phi1", "", 140, 20, 160);
   TH1F* phi3  = new TH1F("phi3", "", 140, 20, 160);
   TH1F* phi5  = new TH1F("phi5", "", 140, 20, 160);
   TH1F* phi7  = new TH1F("phi7", "", 140, 20, 160);
   TH1F* phi9  = new TH1F("phi9", "", 140, 20, 160);
   TH1F* phi11  = new TH1F("phi11", "", 140, 20, 160);
   TH1F* phi13  = new TH1F("phi13", "", 140, 20, 160);
   TH1F* phi15  = new TH1F("phi15", "", 140, 20, 160);
   TH1F* phi17  = new TH1F("phi17", "", 140, 20, 160);
   TH1F* phi19  = new TH1F("phi19", "", 140, 20, 160);
   TH1F* phi21  = new TH1F("phi21", "", 140, 20, 160);
   TH1F* phi23  = new TH1F("phi23", "", 140, 20, 160);
   TH1F* phi25  = new TH1F("phi25", "", 140, 20, 160);
   TH1F* phi27  = new TH1F("phi27", "", 140, 20, 160);
   TH1F* phi29  = new TH1F("phi29", "", 140, 20, 160);
   TH1F* phi31  = new TH1F("phi31", "", 140, 20, 160);
   TH1F* phi33  = new TH1F("phi33", "", 140, 20, 160);
   TH1F* phi35  = new TH1F("phi35", "", 140, 20, 160);
   TH1F* phi37  = new TH1F("phi37", "", 140, 20, 160);
   TH1F* phi39  = new TH1F("phi39", "", 140, 20, 160);
   TH1F* phi41  = new TH1F("phi41", "", 140, 20, 160);
   TH1F* phi43  = new TH1F("phi43", "", 140, 20, 160);
   TH1F* phi45  = new TH1F("phi45", "", 140, 20, 160);
   TH1F* phi47  = new TH1F("phi47", "", 140, 20, 160);
   TH1F* phi49  = new TH1F("phi49", "", 140, 20, 160);
   TH1F* phi51  = new TH1F("phi51", "", 140, 20, 160);
   TH1F* phi53  = new TH1F("phi53", "", 140, 20, 160);
   TH1F* phi55  = new TH1F("phi55", "", 140, 20, 160);
   TH1F* phi57  = new TH1F("phi57", "", 140, 20, 160);
   TH1F* phi59  = new TH1F("phi59", "", 140, 20, 160);
   TH1F* phi61  = new TH1F("phi61", "", 140, 20, 160);
   TH1F* phi63  = new TH1F("phi63", "", 140, 20, 160);
   TH1F* phi65  = new TH1F("phi65", "", 140, 20, 160);
   TH1F* phi67  = new TH1F("phi67", "", 140, 20, 160);
   TH1F* phi69  = new TH1F("phi69", "", 140, 20, 160);
   TH1F* phi71  = new TH1F("phi71", "", 140, 20, 160);
   
   TH1F* nVtx1  = new TH1F("nVtx1", "", 140, 20, 160);
   TH1F* nVtx2  = new TH1F("nVtx2", "", 140, 20, 160);
   TH1F* nVtx3  = new TH1F("nVtx3", "", 140, 20, 160);
   TH1F* nVtx4  = new TH1F("nVtx4", "", 140, 20, 160);
   TH1F* nVtx5  = new TH1F("nVtx5", "", 140, 20, 160);
   TH1F* nVtx6  = new TH1F("nVtx6", "", 140, 20, 160);
   TH1F* nVtx7  = new TH1F("nVtx7", "", 140, 20, 160);
   TH1F* nVtx8  = new TH1F("nVtx8", "", 140, 20, 160);
   TH1F* nVtx9  = new TH1F("nVtx9", "", 140, 20, 160);
    
   TH1F* eta30phi1  = new TH1F("eta30phi1", "", 140, 20, 160);
   TH1F* eta30phi3  = new TH1F("eta30phi3", "", 140, 20, 160);
   TH1F* eta30phi5  = new TH1F("eta30phi5", "", 140, 20, 160);
   TH1F* eta30phi7  = new TH1F("eta30phi7", "", 140, 20, 160);
   TH1F* eta30phi9  = new TH1F("eta30phi9", "", 140, 20, 160);
   TH1F* eta30phi11  = new TH1F("eta30phi11", "", 140, 20, 160);
   TH1F* eta30phi13  = new TH1F("eta30phi13", "", 140, 20, 160);
   TH1F* eta30phi15  = new TH1F("eta30phi15", "", 140, 20, 160);
   TH1F* eta30phi17  = new TH1F("eta30phi17", "", 140, 20, 160);
   TH1F* eta30phi19  = new TH1F("eta30phi19", "", 140, 20, 160);
   TH1F* eta30phi21  = new TH1F("eta30phi21", "", 140, 20, 160);
   TH1F* eta30phi23  = new TH1F("eta30phi23", "", 140, 20, 160);
   TH1F* eta30phi25  = new TH1F("eta30phi25", "", 140, 20, 160);
   TH1F* eta30phi27  = new TH1F("eta30phi27", "", 140, 20, 160);
   TH1F* eta30phi29  = new TH1F("eta30phi29", "", 140, 20, 160);
   TH1F* eta30phi31  = new TH1F("eta30phi31", "", 140, 20, 160);
   TH1F* eta30phi33  = new TH1F("eta30phi33", "", 140, 20, 160);
   TH1F* eta30phi35  = new TH1F("eta30phi35", "", 140, 20, 160);
   TH1F* eta30phi37  = new TH1F("eta30phi37", "", 140, 20, 160);
   TH1F* eta30phi39  = new TH1F("eta30phi39", "", 140, 20, 160);
   TH1F* eta30phi41  = new TH1F("eta30phi41", "", 140, 20, 160);
   TH1F* eta30phi43  = new TH1F("eta30phi43", "", 140, 20, 160);
   TH1F* eta30phi45  = new TH1F("eta30phi45", "", 140, 20, 160);
   TH1F* eta30phi47  = new TH1F("eta30phi47", "", 140, 20, 160);
   TH1F* eta30phi49  = new TH1F("eta30phi49", "", 140, 20, 160);
   TH1F* eta30phi51  = new TH1F("eta30phi51", "", 140, 20, 160);
   TH1F* eta30phi53  = new TH1F("eta30phi53", "", 140, 20, 160);
   TH1F* eta30phi55  = new TH1F("eta30phi55", "", 140, 20, 160);
   TH1F* eta30phi57  = new TH1F("eta30phi57", "", 140, 20, 160);
   TH1F* eta30phi59  = new TH1F("eta30phi59", "", 140, 20, 160);
   TH1F* eta30phi61  = new TH1F("eta30phi61", "", 140, 20, 160);
   TH1F* eta30phi63  = new TH1F("eta30phi63", "", 140, 20, 160);
   TH1F* eta30phi65  = new TH1F("eta30phi65", "", 140, 20, 160);
   TH1F* eta30phi67  = new TH1F("eta30phi67", "", 140, 20, 160);
   TH1F* eta30phi69  = new TH1F("eta30phi69", "", 140, 20, 160);
   TH1F* eta30phi71  = new TH1F("eta30phi71", "", 140, 20, 160);
   TH1F* eta31phi1  = new TH1F("eta31phi1", "", 140, 20, 160);
   TH1F* eta31phi3  = new TH1F("eta31phi3", "", 140, 20, 160);
   TH1F* eta31phi5  = new TH1F("eta31phi5", "", 140, 20, 160);
   TH1F* eta31phi7  = new TH1F("eta31phi7", "", 140, 20, 160);
   TH1F* eta31phi9  = new TH1F("eta31phi9", "", 140, 20, 160);
   TH1F* eta31phi11  = new TH1F("eta31phi11", "", 140, 20, 160);
   TH1F* eta31phi13  = new TH1F("eta31phi13", "", 140, 20, 160);
   TH1F* eta31phi15  = new TH1F("eta31phi15", "", 140, 20, 160);
   TH1F* eta31phi17  = new TH1F("eta31phi17", "", 140, 20, 160);
   TH1F* eta31phi19  = new TH1F("eta31phi19", "", 140, 20, 160);
   TH1F* eta31phi21  = new TH1F("eta31phi21", "", 140, 20, 160);
   TH1F* eta31phi23  = new TH1F("eta31phi23", "", 140, 20, 160);
   TH1F* eta31phi25  = new TH1F("eta31phi25", "", 140, 20, 160);
   TH1F* eta31phi27  = new TH1F("eta31phi27", "", 140, 20, 160);
   TH1F* eta31phi29  = new TH1F("eta31phi29", "", 140, 20, 160);
   TH1F* eta31phi31  = new TH1F("eta31phi31", "", 140, 20, 160);
   TH1F* eta31phi33  = new TH1F("eta31phi33", "", 140, 20, 160);
   TH1F* eta31phi35  = new TH1F("eta31phi35", "", 140, 20, 160);
   TH1F* eta31phi37  = new TH1F("eta31phi37", "", 140, 20, 160);
   TH1F* eta31phi39  = new TH1F("eta31phi39", "", 140, 20, 160);
   TH1F* eta31phi41  = new TH1F("eta31phi41", "", 140, 20, 160);
   TH1F* eta31phi43  = new TH1F("eta31phi43", "", 140, 20, 160);
   TH1F* eta31phi45  = new TH1F("eta31phi45", "", 140, 20, 160);
   TH1F* eta31phi47  = new TH1F("eta31phi47", "", 140, 20, 160);
   TH1F* eta31phi49  = new TH1F("eta31phi49", "", 140, 20, 160);
   TH1F* eta31phi51  = new TH1F("eta31phi51", "", 140, 20, 160);
   TH1F* eta31phi53  = new TH1F("eta31phi53", "", 140, 20, 160);
   TH1F* eta31phi55  = new TH1F("eta31phi55", "", 140, 20, 160);
   TH1F* eta31phi57  = new TH1F("eta31phi57", "", 140, 20, 160);
   TH1F* eta31phi59  = new TH1F("eta31phi59", "", 140, 20, 160);
   TH1F* eta31phi61  = new TH1F("eta31phi61", "", 140, 20, 160);
   TH1F* eta31phi63  = new TH1F("eta31phi63", "", 140, 20, 160);
   TH1F* eta31phi65  = new TH1F("eta31phi65", "", 140, 20, 160);
   TH1F* eta31phi67  = new TH1F("eta31phi67", "", 140, 20, 160);
   TH1F* eta31phi69  = new TH1F("eta31phi69", "", 140, 20, 160);
   TH1F* eta31phi71  = new TH1F("eta31phi71", "", 140, 20, 160);
   TH1F* eta32phi1  = new TH1F("eta32phi1", "", 140, 20, 160);
   TH1F* eta32phi3  = new TH1F("eta32phi3", "", 140, 20, 160);
   TH1F* eta32phi5  = new TH1F("eta32phi5", "", 140, 20, 160);
   TH1F* eta32phi7  = new TH1F("eta32phi7", "", 140, 20, 160);
   TH1F* eta32phi9  = new TH1F("eta32phi9", "", 140, 20, 160);
   TH1F* eta32phi11  = new TH1F("eta32phi11", "", 140, 20, 160);
   TH1F* eta32phi13  = new TH1F("eta32phi13", "", 140, 20, 160);
   TH1F* eta32phi15  = new TH1F("eta32phi15", "", 140, 20, 160);
   TH1F* eta32phi17  = new TH1F("eta32phi17", "", 140, 20, 160);
   TH1F* eta32phi19  = new TH1F("eta32phi19", "", 140, 20, 160);
   TH1F* eta32phi21  = new TH1F("eta32phi21", "", 140, 20, 160);
   TH1F* eta32phi23  = new TH1F("eta32phi23", "", 140, 20, 160);
   TH1F* eta32phi25  = new TH1F("eta32phi25", "", 140, 20, 160);
   TH1F* eta32phi27  = new TH1F("eta32phi27", "", 140, 20, 160);
   TH1F* eta32phi29  = new TH1F("eta32phi29", "", 140, 20, 160);
   TH1F* eta32phi31  = new TH1F("eta32phi31", "", 140, 20, 160);
   TH1F* eta32phi33  = new TH1F("eta32phi33", "", 140, 20, 160);
   TH1F* eta32phi35  = new TH1F("eta32phi35", "", 140, 20, 160);
   TH1F* eta32phi37  = new TH1F("eta32phi37", "", 140, 20, 160);
   TH1F* eta32phi39  = new TH1F("eta32phi39", "", 140, 20, 160);
   TH1F* eta32phi41  = new TH1F("eta32phi41", "", 140, 20, 160);
   TH1F* eta32phi43  = new TH1F("eta32phi43", "", 140, 20, 160);
   TH1F* eta32phi45  = new TH1F("eta32phi45", "", 140, 20, 160);
   TH1F* eta32phi47  = new TH1F("eta32phi47", "", 140, 20, 160);
   TH1F* eta32phi49  = new TH1F("eta32phi49", "", 140, 20, 160);
   TH1F* eta32phi51  = new TH1F("eta32phi51", "", 140, 20, 160);
   TH1F* eta32phi53  = new TH1F("eta32phi53", "", 140, 20, 160);
   TH1F* eta32phi55  = new TH1F("eta32phi55", "", 140, 20, 160);
   TH1F* eta32phi57  = new TH1F("eta32phi57", "", 140, 20, 160);
   TH1F* eta32phi59  = new TH1F("eta32phi59", "", 140, 20, 160);
   TH1F* eta32phi61  = new TH1F("eta32phi61", "", 140, 20, 160);
   TH1F* eta32phi63  = new TH1F("eta32phi63", "", 140, 20, 160);
   TH1F* eta32phi65  = new TH1F("eta32phi65", "", 140, 20, 160);
   TH1F* eta32phi67  = new TH1F("eta32phi67", "", 140, 20, 160);
   TH1F* eta32phi69  = new TH1F("eta32phi69", "", 140, 20, 160);
   TH1F* eta32phi71  = new TH1F("eta32phi71", "", 140, 20, 160);
   TH1F* eta33phi1  = new TH1F("eta33phi1", "", 140, 20, 160);
   TH1F* eta33phi3  = new TH1F("eta33phi3", "", 140, 20, 160);
   TH1F* eta33phi5  = new TH1F("eta33phi5", "", 140, 20, 160);
   TH1F* eta33phi7  = new TH1F("eta33phi7", "", 140, 20, 160);
   TH1F* eta33phi9  = new TH1F("eta33phi9", "", 140, 20, 160);
   TH1F* eta33phi11  = new TH1F("eta33phi11", "", 140, 20, 160);
   TH1F* eta33phi13  = new TH1F("eta33phi13", "", 140, 20, 160);
   TH1F* eta33phi15  = new TH1F("eta33phi15", "", 140, 20, 160);
   TH1F* eta33phi17  = new TH1F("eta33phi17", "", 140, 20, 160);
   TH1F* eta33phi19  = new TH1F("eta33phi19", "", 140, 20, 160);
   TH1F* eta33phi21  = new TH1F("eta33phi21", "", 140, 20, 160);
   TH1F* eta33phi23  = new TH1F("eta33phi23", "", 140, 20, 160);
   TH1F* eta33phi25  = new TH1F("eta33phi25", "", 140, 20, 160);
   TH1F* eta33phi27  = new TH1F("eta33phi27", "", 140, 20, 160);
   TH1F* eta33phi29  = new TH1F("eta33phi29", "", 140, 20, 160);
   TH1F* eta33phi31  = new TH1F("eta33phi31", "", 140, 20, 160);
   TH1F* eta33phi33  = new TH1F("eta33phi33", "", 140, 20, 160);
   TH1F* eta33phi35  = new TH1F("eta33phi35", "", 140, 20, 160);
   TH1F* eta33phi37  = new TH1F("eta33phi37", "", 140, 20, 160);
   TH1F* eta33phi39  = new TH1F("eta33phi39", "", 140, 20, 160);
   TH1F* eta33phi41  = new TH1F("eta33phi41", "", 140, 20, 160);
   TH1F* eta33phi43  = new TH1F("eta33phi43", "", 140, 20, 160);
   TH1F* eta33phi45  = new TH1F("eta33phi45", "", 140, 20, 160);
   TH1F* eta33phi47  = new TH1F("eta33phi47", "", 140, 20, 160);
   TH1F* eta33phi49  = new TH1F("eta33phi49", "", 140, 20, 160);
   TH1F* eta33phi51  = new TH1F("eta33phi51", "", 140, 20, 160);
   TH1F* eta33phi53  = new TH1F("eta33phi53", "", 140, 20, 160);
   TH1F* eta33phi55  = new TH1F("eta33phi55", "", 140, 20, 160);
   TH1F* eta33phi57  = new TH1F("eta33phi57", "", 140, 20, 160);
   TH1F* eta33phi59  = new TH1F("eta33phi59", "", 140, 20, 160);
   TH1F* eta33phi61  = new TH1F("eta33phi61", "", 140, 20, 160);
   TH1F* eta33phi63  = new TH1F("eta33phi63", "", 140, 20, 160);
   TH1F* eta33phi65  = new TH1F("eta33phi65", "", 140, 20, 160);
   TH1F* eta33phi67  = new TH1F("eta33phi67", "", 140, 20, 160);
   TH1F* eta33phi69  = new TH1F("eta33phi69", "", 140, 20, 160);
   TH1F* eta33phi71  = new TH1F("eta33phi71", "", 140, 20, 160);
   TH1F* eta34phi1  = new TH1F("eta34phi1", "", 140, 20, 160);
   TH1F* eta34phi3  = new TH1F("eta34phi3", "", 140, 20, 160);
   TH1F* eta34phi5  = new TH1F("eta34phi5", "", 140, 20, 160);
   TH1F* eta34phi7  = new TH1F("eta34phi7", "", 140, 20, 160);
   TH1F* eta34phi9  = new TH1F("eta34phi9", "", 140, 20, 160);
   TH1F* eta34phi11  = new TH1F("eta34phi11", "", 140, 20, 160);
   TH1F* eta34phi13  = new TH1F("eta34phi13", "", 140, 20, 160);
   TH1F* eta34phi15  = new TH1F("eta34phi15", "", 140, 20, 160);
   TH1F* eta34phi17  = new TH1F("eta34phi17", "", 140, 20, 160);
   TH1F* eta34phi19  = new TH1F("eta34phi19", "", 140, 20, 160);
   TH1F* eta34phi21  = new TH1F("eta34phi21", "", 140, 20, 160);
   TH1F* eta34phi23  = new TH1F("eta34phi23", "", 140, 20, 160);
   TH1F* eta34phi25  = new TH1F("eta34phi25", "", 140, 20, 160);
   TH1F* eta34phi27  = new TH1F("eta34phi27", "", 140, 20, 160);
   TH1F* eta34phi29  = new TH1F("eta34phi29", "", 140, 20, 160);
   TH1F* eta34phi31  = new TH1F("eta34phi31", "", 140, 20, 160);
   TH1F* eta34phi33  = new TH1F("eta34phi33", "", 140, 20, 160);
   TH1F* eta34phi35  = new TH1F("eta34phi35", "", 140, 20, 160);
   TH1F* eta34phi37  = new TH1F("eta34phi37", "", 140, 20, 160);
   TH1F* eta34phi39  = new TH1F("eta34phi39", "", 140, 20, 160);
   TH1F* eta34phi41  = new TH1F("eta34phi41", "", 140, 20, 160);
   TH1F* eta34phi43  = new TH1F("eta34phi43", "", 140, 20, 160);
   TH1F* eta34phi45  = new TH1F("eta34phi45", "", 140, 20, 160);
   TH1F* eta34phi47  = new TH1F("eta34phi47", "", 140, 20, 160);
   TH1F* eta34phi49  = new TH1F("eta34phi49", "", 140, 20, 160);
   TH1F* eta34phi51  = new TH1F("eta34phi51", "", 140, 20, 160);
   TH1F* eta34phi53  = new TH1F("eta34phi53", "", 140, 20, 160);
   TH1F* eta34phi55  = new TH1F("eta34phi55", "", 140, 20, 160);
   TH1F* eta34phi57  = new TH1F("eta34phi57", "", 140, 20, 160);
   TH1F* eta34phi59  = new TH1F("eta34phi59", "", 140, 20, 160);
   TH1F* eta34phi61  = new TH1F("eta34phi61", "", 140, 20, 160);
   TH1F* eta34phi63  = new TH1F("eta34phi63", "", 140, 20, 160);
   TH1F* eta34phi65  = new TH1F("eta34phi65", "", 140, 20, 160);
   TH1F* eta34phi67  = new TH1F("eta34phi67", "", 140, 20, 160);
   TH1F* eta34phi69  = new TH1F("eta34phi69", "", 140, 20, 160);
   TH1F* eta34phi71  = new TH1F("eta34phi71", "", 140, 20, 160);
   TH1F* eta35phi1  = new TH1F("eta35phi1", "", 140, 20, 160);
   TH1F* eta35phi3  = new TH1F("eta35phi3", "", 140, 20, 160);
   TH1F* eta35phi5  = new TH1F("eta35phi5", "", 140, 20, 160);
   TH1F* eta35phi7  = new TH1F("eta35phi7", "", 140, 20, 160);
   TH1F* eta35phi9  = new TH1F("eta35phi9", "", 140, 20, 160);
   TH1F* eta35phi11  = new TH1F("eta35phi11", "", 140, 20, 160);
   TH1F* eta35phi13  = new TH1F("eta35phi13", "", 140, 20, 160);
   TH1F* eta35phi15  = new TH1F("eta35phi15", "", 140, 20, 160);
   TH1F* eta35phi17  = new TH1F("eta35phi17", "", 140, 20, 160);
   TH1F* eta35phi19  = new TH1F("eta35phi19", "", 140, 20, 160);
   TH1F* eta35phi21  = new TH1F("eta35phi21", "", 140, 20, 160);
   TH1F* eta35phi23  = new TH1F("eta35phi23", "", 140, 20, 160);
   TH1F* eta35phi25  = new TH1F("eta35phi25", "", 140, 20, 160);
   TH1F* eta35phi27  = new TH1F("eta35phi27", "", 140, 20, 160);
   TH1F* eta35phi29  = new TH1F("eta35phi29", "", 140, 20, 160);
   TH1F* eta35phi31  = new TH1F("eta35phi31", "", 140, 20, 160);
   TH1F* eta35phi33  = new TH1F("eta35phi33", "", 140, 20, 160);
   TH1F* eta35phi35  = new TH1F("eta35phi35", "", 140, 20, 160);
   TH1F* eta35phi37  = new TH1F("eta35phi37", "", 140, 20, 160);
   TH1F* eta35phi39  = new TH1F("eta35phi39", "", 140, 20, 160);
   TH1F* eta35phi41  = new TH1F("eta35phi41", "", 140, 20, 160);
   TH1F* eta35phi43  = new TH1F("eta35phi43", "", 140, 20, 160);
   TH1F* eta35phi45  = new TH1F("eta35phi45", "", 140, 20, 160);
   TH1F* eta35phi47  = new TH1F("eta35phi47", "", 140, 20, 160);
   TH1F* eta35phi49  = new TH1F("eta35phi49", "", 140, 20, 160);
   TH1F* eta35phi51  = new TH1F("eta35phi51", "", 140, 20, 160);
   TH1F* eta35phi53  = new TH1F("eta35phi53", "", 140, 20, 160);
   TH1F* eta35phi55  = new TH1F("eta35phi55", "", 140, 20, 160);
   TH1F* eta35phi57  = new TH1F("eta35phi57", "", 140, 20, 160);
   TH1F* eta35phi59  = new TH1F("eta35phi59", "", 140, 20, 160);
   TH1F* eta35phi61  = new TH1F("eta35phi61", "", 140, 20, 160);
   TH1F* eta35phi63  = new TH1F("eta35phi63", "", 140, 20, 160);
   TH1F* eta35phi65  = new TH1F("eta35phi65", "", 140, 20, 160);
   TH1F* eta35phi67  = new TH1F("eta35phi67", "", 140, 20, 160);
   TH1F* eta35phi69  = new TH1F("eta35phi69", "", 140, 20, 160);
   TH1F* eta35phi71  = new TH1F("eta35phi71", "", 140, 20, 160);
   TH1F* eta36phi1  = new TH1F("eta36phi1", "", 140, 20, 160);
   TH1F* eta36phi3  = new TH1F("eta36phi3", "", 140, 20, 160);
   TH1F* eta36phi5  = new TH1F("eta36phi5", "", 140, 20, 160);
   TH1F* eta36phi7  = new TH1F("eta36phi7", "", 140, 20, 160);
   TH1F* eta36phi9  = new TH1F("eta36phi9", "", 140, 20, 160);
   TH1F* eta36phi11  = new TH1F("eta36phi11", "", 140, 20, 160);
   TH1F* eta36phi13  = new TH1F("eta36phi13", "", 140, 20, 160);
   TH1F* eta36phi15  = new TH1F("eta36phi15", "", 140, 20, 160);
   TH1F* eta36phi17  = new TH1F("eta36phi17", "", 140, 20, 160);
   TH1F* eta36phi19  = new TH1F("eta36phi19", "", 140, 20, 160);
   TH1F* eta36phi21  = new TH1F("eta36phi21", "", 140, 20, 160);
   TH1F* eta36phi23  = new TH1F("eta36phi23", "", 140, 20, 160);
   TH1F* eta36phi25  = new TH1F("eta36phi25", "", 140, 20, 160);
   TH1F* eta36phi27  = new TH1F("eta36phi27", "", 140, 20, 160);
   TH1F* eta36phi29  = new TH1F("eta36phi29", "", 140, 20, 160);
   TH1F* eta36phi31  = new TH1F("eta36phi31", "", 140, 20, 160);
   TH1F* eta36phi33  = new TH1F("eta36phi33", "", 140, 20, 160);
   TH1F* eta36phi35  = new TH1F("eta36phi35", "", 140, 20, 160);
   TH1F* eta36phi37  = new TH1F("eta36phi37", "", 140, 20, 160);
   TH1F* eta36phi39  = new TH1F("eta36phi39", "", 140, 20, 160);
   TH1F* eta36phi41  = new TH1F("eta36phi41", "", 140, 20, 160);
   TH1F* eta36phi43  = new TH1F("eta36phi43", "", 140, 20, 160);
   TH1F* eta36phi45  = new TH1F("eta36phi45", "", 140, 20, 160);
   TH1F* eta36phi47  = new TH1F("eta36phi47", "", 140, 20, 160);
   TH1F* eta36phi49  = new TH1F("eta36phi49", "", 140, 20, 160);
   TH1F* eta36phi51  = new TH1F("eta36phi51", "", 140, 20, 160);
   TH1F* eta36phi53  = new TH1F("eta36phi53", "", 140, 20, 160);
   TH1F* eta36phi55  = new TH1F("eta36phi55", "", 140, 20, 160);
   TH1F* eta36phi57  = new TH1F("eta36phi57", "", 140, 20, 160);
   TH1F* eta36phi59  = new TH1F("eta36phi59", "", 140, 20, 160);
   TH1F* eta36phi61  = new TH1F("eta36phi61", "", 140, 20, 160);
   TH1F* eta36phi63  = new TH1F("eta36phi63", "", 140, 20, 160);
   TH1F* eta36phi65  = new TH1F("eta36phi65", "", 140, 20, 160);
   TH1F* eta36phi67  = new TH1F("eta36phi67", "", 140, 20, 160);
   TH1F* eta36phi69  = new TH1F("eta36phi69", "", 140, 20, 160);
   TH1F* eta36phi71  = new TH1F("eta36phi71", "", 140, 20, 160);
   TH1F* eta37phi1  = new TH1F("eta37phi1", "", 140, 20, 160);
   TH1F* eta37phi3  = new TH1F("eta37phi3", "", 140, 20, 160);
   TH1F* eta37phi5  = new TH1F("eta37phi5", "", 140, 20, 160);
   TH1F* eta37phi7  = new TH1F("eta37phi7", "", 140, 20, 160);
   TH1F* eta37phi9  = new TH1F("eta37phi9", "", 140, 20, 160);
   TH1F* eta37phi11  = new TH1F("eta37phi11", "", 140, 20, 160);
   TH1F* eta37phi13  = new TH1F("eta37phi13", "", 140, 20, 160);
   TH1F* eta37phi15  = new TH1F("eta37phi15", "", 140, 20, 160);
   TH1F* eta37phi17  = new TH1F("eta37phi17", "", 140, 20, 160);
   TH1F* eta37phi19  = new TH1F("eta37phi19", "", 140, 20, 160);
   TH1F* eta37phi21  = new TH1F("eta37phi21", "", 140, 20, 160);
   TH1F* eta37phi23  = new TH1F("eta37phi23", "", 140, 20, 160);
   TH1F* eta37phi25  = new TH1F("eta37phi25", "", 140, 20, 160);
   TH1F* eta37phi27  = new TH1F("eta37phi27", "", 140, 20, 160);
   TH1F* eta37phi29  = new TH1F("eta37phi29", "", 140, 20, 160);
   TH1F* eta37phi31  = new TH1F("eta37phi31", "", 140, 20, 160);
   TH1F* eta37phi33  = new TH1F("eta37phi33", "", 140, 20, 160);
   TH1F* eta37phi35  = new TH1F("eta37phi35", "", 140, 20, 160);
   TH1F* eta37phi37  = new TH1F("eta37phi37", "", 140, 20, 160);
   TH1F* eta37phi39  = new TH1F("eta37phi39", "", 140, 20, 160);
   TH1F* eta37phi41  = new TH1F("eta37phi41", "", 140, 20, 160);
   TH1F* eta37phi43  = new TH1F("eta37phi43", "", 140, 20, 160);
   TH1F* eta37phi45  = new TH1F("eta37phi45", "", 140, 20, 160);
   TH1F* eta37phi47  = new TH1F("eta37phi47", "", 140, 20, 160);
   TH1F* eta37phi49  = new TH1F("eta37phi49", "", 140, 20, 160);
   TH1F* eta37phi51  = new TH1F("eta37phi51", "", 140, 20, 160);
   TH1F* eta37phi53  = new TH1F("eta37phi53", "", 140, 20, 160);
   TH1F* eta37phi55  = new TH1F("eta37phi55", "", 140, 20, 160);
   TH1F* eta37phi57  = new TH1F("eta37phi57", "", 140, 20, 160);
   TH1F* eta37phi59  = new TH1F("eta37phi59", "", 140, 20, 160);
   TH1F* eta37phi61  = new TH1F("eta37phi61", "", 140, 20, 160);
   TH1F* eta37phi63  = new TH1F("eta37phi63", "", 140, 20, 160);
   TH1F* eta37phi65  = new TH1F("eta37phi65", "", 140, 20, 160);
   TH1F* eta37phi67  = new TH1F("eta37phi67", "", 140, 20, 160);
   TH1F* eta37phi69  = new TH1F("eta37phi69", "", 140, 20, 160);
   TH1F* eta37phi71  = new TH1F("eta37phi71", "", 140, 20, 160);
   TH1F* eta38phi1  = new TH1F("eta38phi1", "", 140, 20, 160);
   TH1F* eta38phi3  = new TH1F("eta38phi3", "", 140, 20, 160);
   TH1F* eta38phi5  = new TH1F("eta38phi5", "", 140, 20, 160);
   TH1F* eta38phi7  = new TH1F("eta38phi7", "", 140, 20, 160);
   TH1F* eta38phi9  = new TH1F("eta38phi9", "", 140, 20, 160);
   TH1F* eta38phi11  = new TH1F("eta38phi11", "", 140, 20, 160);
   TH1F* eta38phi13  = new TH1F("eta38phi13", "", 140, 20, 160);
   TH1F* eta38phi15  = new TH1F("eta38phi15", "", 140, 20, 160);
   TH1F* eta38phi17  = new TH1F("eta38phi17", "", 140, 20, 160);
   TH1F* eta38phi19  = new TH1F("eta38phi19", "", 140, 20, 160);
   TH1F* eta38phi21  = new TH1F("eta38phi21", "", 140, 20, 160);
   TH1F* eta38phi23  = new TH1F("eta38phi23", "", 140, 20, 160);
   TH1F* eta38phi25  = new TH1F("eta38phi25", "", 140, 20, 160);
   TH1F* eta38phi27  = new TH1F("eta38phi27", "", 140, 20, 160);
   TH1F* eta38phi29  = new TH1F("eta38phi29", "", 140, 20, 160);
   TH1F* eta38phi31  = new TH1F("eta38phi31", "", 140, 20, 160);
   TH1F* eta38phi33  = new TH1F("eta38phi33", "", 140, 20, 160);
   TH1F* eta38phi35  = new TH1F("eta38phi35", "", 140, 20, 160);
   TH1F* eta38phi37  = new TH1F("eta38phi37", "", 140, 20, 160);
   TH1F* eta38phi39  = new TH1F("eta38phi39", "", 140, 20, 160);
   TH1F* eta38phi41  = new TH1F("eta38phi41", "", 140, 20, 160);
   TH1F* eta38phi43  = new TH1F("eta38phi43", "", 140, 20, 160);
   TH1F* eta38phi45  = new TH1F("eta38phi45", "", 140, 20, 160);
   TH1F* eta38phi47  = new TH1F("eta38phi47", "", 140, 20, 160);
   TH1F* eta38phi49  = new TH1F("eta38phi49", "", 140, 20, 160);
   TH1F* eta38phi51  = new TH1F("eta38phi51", "", 140, 20, 160);
   TH1F* eta38phi53  = new TH1F("eta38phi53", "", 140, 20, 160);
   TH1F* eta38phi55  = new TH1F("eta38phi55", "", 140, 20, 160);
   TH1F* eta38phi57  = new TH1F("eta38phi57", "", 140, 20, 160);
   TH1F* eta38phi59  = new TH1F("eta38phi59", "", 140, 20, 160);
   TH1F* eta38phi61  = new TH1F("eta38phi61", "", 140, 20, 160);
   TH1F* eta38phi63  = new TH1F("eta38phi63", "", 140, 20, 160);
   TH1F* eta38phi65  = new TH1F("eta38phi65", "", 140, 20, 160);
   TH1F* eta38phi67  = new TH1F("eta38phi67", "", 140, 20, 160);
   TH1F* eta38phi69  = new TH1F("eta38phi69", "", 140, 20, 160);
   TH1F* eta38phi71  = new TH1F("eta38phi71", "", 140, 20, 160);
   TH1F* eta39phi1  = new TH1F("eta39phi1", "", 140, 20, 160);
   TH1F* eta39phi3  = new TH1F("eta39phi3", "", 140, 20, 160);
   TH1F* eta39phi5  = new TH1F("eta39phi5", "", 140, 20, 160);
   TH1F* eta39phi7  = new TH1F("eta39phi7", "", 140, 20, 160);
   TH1F* eta39phi9  = new TH1F("eta39phi9", "", 140, 20, 160);
   TH1F* eta39phi11  = new TH1F("eta39phi11", "", 140, 20, 160);
   TH1F* eta39phi13  = new TH1F("eta39phi13", "", 140, 20, 160);
   TH1F* eta39phi15  = new TH1F("eta39phi15", "", 140, 20, 160);
   TH1F* eta39phi17  = new TH1F("eta39phi17", "", 140, 20, 160);
   TH1F* eta39phi19  = new TH1F("eta39phi19", "", 140, 20, 160);
   TH1F* eta39phi21  = new TH1F("eta39phi21", "", 140, 20, 160);
   TH1F* eta39phi23  = new TH1F("eta39phi23", "", 140, 20, 160);
   TH1F* eta39phi25  = new TH1F("eta39phi25", "", 140, 20, 160);
   TH1F* eta39phi27  = new TH1F("eta39phi27", "", 140, 20, 160);
   TH1F* eta39phi29  = new TH1F("eta39phi29", "", 140, 20, 160);
   TH1F* eta39phi31  = new TH1F("eta39phi31", "", 140, 20, 160);
   TH1F* eta39phi33  = new TH1F("eta39phi33", "", 140, 20, 160);
   TH1F* eta39phi35  = new TH1F("eta39phi35", "", 140, 20, 160);
   TH1F* eta39phi37  = new TH1F("eta39phi37", "", 140, 20, 160);
   TH1F* eta39phi39  = new TH1F("eta39phi39", "", 140, 20, 160);
   TH1F* eta39phi41  = new TH1F("eta39phi41", "", 140, 20, 160);
   TH1F* eta39phi43  = new TH1F("eta39phi43", "", 140, 20, 160);
   TH1F* eta39phi45  = new TH1F("eta39phi45", "", 140, 20, 160);
   TH1F* eta39phi47  = new TH1F("eta39phi47", "", 140, 20, 160);
   TH1F* eta39phi49  = new TH1F("eta39phi49", "", 140, 20, 160);
   TH1F* eta39phi51  = new TH1F("eta39phi51", "", 140, 20, 160);
   TH1F* eta39phi53  = new TH1F("eta39phi53", "", 140, 20, 160);
   TH1F* eta39phi55  = new TH1F("eta39phi55", "", 140, 20, 160);
   TH1F* eta39phi57  = new TH1F("eta39phi57", "", 140, 20, 160);
   TH1F* eta39phi59  = new TH1F("eta39phi59", "", 140, 20, 160);
   TH1F* eta39phi61  = new TH1F("eta39phi61", "", 140, 20, 160);
   TH1F* eta39phi63  = new TH1F("eta39phi63", "", 140, 20, 160);
   TH1F* eta39phi65  = new TH1F("eta39phi65", "", 140, 20, 160);
   TH1F* eta39phi67  = new TH1F("eta39phi67", "", 140, 20, 160);
   TH1F* eta39phi69  = new TH1F("eta39phi69", "", 140, 20, 160);
   TH1F* eta39phi71  = new TH1F("eta39phi71", "", 140, 20, 160);
   TH1F* eta40phi3  = new TH1F("eta40phi3", "", 140, 20, 160);
   TH1F* eta40phi7  = new TH1F("eta40phi7", "", 140, 20, 160);
   TH1F* eta40phi11  = new TH1F("eta40phi11", "", 140, 20, 160);
   TH1F* eta40phi15  = new TH1F("eta40phi15", "", 140, 20, 160);
   TH1F* eta40phi19  = new TH1F("eta40phi19", "", 140, 20, 160);
   TH1F* eta40phi23  = new TH1F("eta40phi23", "", 140, 20, 160);
   TH1F* eta40phi27  = new TH1F("eta40phi27", "", 140, 20, 160);
   TH1F* eta40phi31  = new TH1F("eta40phi31", "", 140, 20, 160);
   TH1F* eta40phi35  = new TH1F("eta40phi35", "", 140, 20, 160);
   TH1F* eta40phi39  = new TH1F("eta40phi39", "", 140, 20, 160);
   TH1F* eta40phi43  = new TH1F("eta40phi43", "", 140, 20, 160);
   TH1F* eta40phi47  = new TH1F("eta40phi47", "", 140, 20, 160);
   TH1F* eta40phi51  = new TH1F("eta40phi51", "", 140, 20, 160);
   TH1F* eta40phi55  = new TH1F("eta40phi55", "", 140, 20, 160);
   TH1F* eta40phi59  = new TH1F("eta40phi59", "", 140, 20, 160);
   TH1F* eta40phi63  = new TH1F("eta40phi63", "", 140, 20, 160);
   TH1F* eta40phi67  = new TH1F("eta40phi67", "", 140, 20, 160);
   TH1F* eta40phi71  = new TH1F("eta40phi71", "", 140, 20, 160);
   TH1F* eta41phi3  = new TH1F("eta41phi3", "", 140, 20, 160);
   TH1F* eta41phi7  = new TH1F("eta41phi7", "", 140, 20, 160);
   TH1F* eta41phi11  = new TH1F("eta41phi11", "", 140, 20, 160);
   TH1F* eta41phi15  = new TH1F("eta41phi15", "", 140, 20, 160);
   TH1F* eta41phi19  = new TH1F("eta41phi19", "", 140, 20, 160);
   TH1F* eta41phi23  = new TH1F("eta41phi23", "", 140, 20, 160);
   TH1F* eta41phi27  = new TH1F("eta41phi27", "", 140, 20, 160);
   TH1F* eta41phi31  = new TH1F("eta41phi31", "", 140, 20, 160);
   TH1F* eta41phi35  = new TH1F("eta41phi35", "", 140, 20, 160);
   TH1F* eta41phi39  = new TH1F("eta41phi39", "", 140, 20, 160);
   TH1F* eta41phi43  = new TH1F("eta41phi43", "", 140, 20, 160);
   TH1F* eta41phi47  = new TH1F("eta41phi47", "", 140, 20, 160);
   TH1F* eta41phi51  = new TH1F("eta41phi51", "", 140, 20, 160);
   TH1F* eta41phi55  = new TH1F("eta41phi55", "", 140, 20, 160);
   TH1F* eta41phi59  = new TH1F("eta41phi59", "", 140, 20, 160);
   TH1F* eta41phi63  = new TH1F("eta41phi63", "", 140, 20, 160);
   TH1F* eta41phi67  = new TH1F("eta41phi67", "", 140, 20, 160);
   TH1F* eta41phi71  = new TH1F("eta41phi71", "", 140, 20, 160);
   
   TH1F* eta30nvtx = new TH1F("eta30nvtx", "", 60, 0, 60);
   beautify(eta30nvtx, "nVtx (i#eta30)", "Events", 2);
   TH1F* eta31nvtx = new TH1F("eta31nvtx", "", 60, 0, 60);
   beautify(eta31nvtx, "nVtx (i#eta31)", "Events", 2);
   TH1F* eta32nvtx = new TH1F("eta32nvtx", "", 60, 0, 60);
   beautify(eta32nvtx, "nVtx (i#eta32)", "Events", 2);
   TH1F* eta33nvtx = new TH1F("eta33nvtx", "", 60, 0, 60);
   beautify(eta33nvtx, "nVtx (i#eta33)", "Events", 2);
   TH1F* eta34nvtx = new TH1F("eta34nvtx", "", 60, 0, 60);
   beautify(eta34nvtx, "nVtx (i#eta34)", "Events", 2);
   TH1F* eta35nvtx = new TH1F("eta35nvtx", "", 60, 0, 60);
   beautify(eta35nvtx, "nVtx (i#eta35)", "Events", 2);
   TH1F* eta36nvtx = new TH1F("eta36nvtx", "", 60, 0, 60);
   beautify(eta36nvtx, "nVtx (i#eta36)", "Events", 2);
   TH1F* eta37nvtx = new TH1F("eta37nvtx", "", 60, 0, 60);
   beautify(eta37nvtx, "nVtx (i#eta37)", "Events", 2);
   TH1F* eta38nvtx = new TH1F("eta38nvtx", "", 60, 0, 60);
   beautify(eta38nvtx, "nVtx (i#eta38)", "Events", 2);
   TH1F* eta39nvtx = new TH1F("eta39nvtx", "", 60, 0, 60);
   beautify(eta39nvtx, "nVtx (i#eta39)", "Events", 2);
   TH1F* eta40nvtx = new TH1F("eta40nvtx", "", 60, 0, 60);
   beautify(eta40nvtx, "nVtx (i#eta40)", "Events", 2);
   TH1F* eta41nvtx = new TH1F("eta41nvtx", "", 60, 0, 60);
   beautify(eta41nvtx, "nVtx (i#eta41)", "Events", 2);
   
   TH1F* eta30phi = new TH1F("eta30phi", "eta30", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta30phi, "#phi_{HF}", "Events", 2);
   TH1F* eta31phi = new TH1F("eta31phi", "eta31", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta31phi, "#phi_{HF}", "Events", 2);
   TH1F* eta32phi = new TH1F("eta32phi", "eta32", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta32phi, "#phi_{HF}", "Events", 2);
   TH1F* eta33phi = new TH1F("eta33phi", "eta33", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta33phi, "#phi_{HF}", "Events", 2);
   TH1F* eta34phi = new TH1F("eta34phi", "eta34", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta34phi, "#phi_{HF}", "Events", 2);
   TH1F* eta35phi = new TH1F("eta35phi", "eta35", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta35phi, "#phi_{HF}", "Events", 2);
   TH1F* eta36phi = new TH1F("eta36phi", "eta36", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta36phi, "#phi_{HF}", "Events", 2);
   TH1F* eta37phi = new TH1F("eta37phi", "eta37", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta37phi, "#phi_{HF}", "Events", 2);
   TH1F* eta38phi = new TH1F("eta38phi", "eta38", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta38phi, "#phi_{HF}", "Events", 2);
   TH1F* eta39phi = new TH1F("eta39phi", "eta39", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta39phi, "#phi_{HF}", "Events", 2);
   TH1F* eta40phi = new TH1F("eta40phi", "eta40", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta40phi, "#phi_{HF}", "Events", 2);
   TH1F* eta41phi = new TH1F("eta41phi", "eta41", 36, -TMath::Pi(), TMath::Pi());
   beautify(eta41phi, "#phi_{HF}", "Events", 2);
   
   TH1F* eta30etaEE = new TH1F("eta30etaEE", "eta30", 126, -3.15, 3.15);
   beautify(eta30etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta31etaEE = new TH1F("eta31etaEE", "eta31", 126, -3.15, 3.15);
   beautify(eta31etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta32etaEE = new TH1F("eta32etaEE", "eta32", 126, -3.15, 3.15);
   beautify(eta32etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta33etaEE = new TH1F("eta33etaEE", "eta33", 126, -3.15, 3.15);
   beautify(eta33etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta34etaEE = new TH1F("eta34etaEE", "eta34", 126, -3.15, 3.15);
   beautify(eta34etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta35etaEE = new TH1F("eta35etaEE", "eta35", 126, -3.15, 3.15);
   beautify(eta35etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta36etaEE = new TH1F("eta36etaEE", "eta36", 126, -3.15, 3.15);
   beautify(eta36etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta37etaEE = new TH1F("eta37etaEE", "eta37", 126, -3.15, 3.15);
   beautify(eta37etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta38etaEE = new TH1F("eta38etaEE", "eta38", 126, -3.15, 3.15);
   beautify(eta38etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta39etaEE = new TH1F("eta39etaEE", "eta39", 126, -3.15, 3.15);
   beautify(eta39etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta40etaEE = new TH1F("eta40etaEE", "eta40", 126, -3.15, 3.15);
   beautify(eta40etaEE, "#eta_{ECAL}", "Events", 2);
   TH1F* eta41etaEE = new TH1F("eta41etaEE", "eta41", 126, -3.15, 3.15);
   beautify(eta41etaEE, "#eta_{ECAL}", "Events", 2);
   
   TH1F* eta30phiEE = new TH1F("eta30phiEE", "eta30", 126, -3.15, 3.15);
   beautify(eta30phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta31phiEE = new TH1F("eta31phiEE", "eta31", 126, -3.15, 3.15);
   beautify(eta31phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta32phiEE = new TH1F("eta32phiEE", "eta32", 126, -3.15, 3.15);
   beautify(eta32phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta33phiEE = new TH1F("eta33phiEE", "eta33", 126, -3.15, 3.15);
   beautify(eta33phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta34phiEE = new TH1F("eta34phiEE", "eta34", 126, -3.15, 3.15);
   beautify(eta34phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta35phiEE = new TH1F("eta35phiEE", "eta35", 126, -3.15, 3.15);
   beautify(eta35phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta36phiEE = new TH1F("eta36phiEE", "eta36", 126, -3.15, 3.15);
   beautify(eta36phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta37phiEE = new TH1F("eta37phiEE", "eta37", 126, -3.15, 3.15);
   beautify(eta37phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta38phiEE = new TH1F("eta38phiEE", "eta38", 126, -3.15, 3.15);
   beautify(eta38phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta39phiEE = new TH1F("eta39phiEE", "eta39", 126, -3.15, 3.15);
   beautify(eta39phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta40phiEE = new TH1F("eta40phiEE", "eta40", 126, -3.15, 3.15);
   beautify(eta40phiEE, "#phi_{ECAL}", "Events", 2);
   TH1F* eta41phiEE = new TH1F("eta41phiEE", "eta41", 126, -3.15, 3.15);
   beautify(eta41phiEE, "#phi_{ECAL}", "Events", 2);
   
   TH1F* eta30dphi = new TH1F("eta30dphi", "eta30", 252, -6.3, 6.3);
   beautify(eta30dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta31dphi = new TH1F("eta31dphi", "eta31", 252, -6.3, 6.3);
   beautify(eta31dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta32dphi = new TH1F("eta32dphi", "eta32", 252, -6.3, 6.3);
   beautify(eta32dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta33dphi = new TH1F("eta33dphi", "eta33", 252, -6.3, 6.3);
   beautify(eta33dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta34dphi = new TH1F("eta34dphi", "eta34", 252, -6.3, 6.3);
   beautify(eta34dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta35dphi = new TH1F("eta35dphi", "eta35", 252, -6.3, 6.3);
   beautify(eta35dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta36dphi = new TH1F("eta36dphi", "eta36", 252, -6.3, 6.3);
   beautify(eta36dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta37dphi = new TH1F("eta37dphi", "eta37", 252, -6.3, 6.3);
   beautify(eta37dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta38dphi = new TH1F("eta38dphi", "eta38", 252, -6.3, 6.3);
   beautify(eta38dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta39dphi = new TH1F("eta39dphi", "eta39", 252, -6.3, 6.3);
   beautify(eta39dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta40dphi = new TH1F("eta40dphi", "eta40", 252, -6.3, 6.3);
   beautify(eta40dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   TH1F* eta41dphi = new TH1F("eta41dphi", "eta41", 252, -6.3, 6.3);
   beautify(eta41dphi, "#Delta#phi_{ECAL, HF}", "Events", 2);
   
   TH1F* eta30en = new TH1F("eta30en", "eta30", 60, 0, 150);
   beautify(eta30en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta31en = new TH1F("eta31en", "eta31", 60, 0, 150);
   beautify(eta31en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta32en = new TH1F("eta32en", "eta32", 60, 0, 150);
   beautify(eta32en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta33en = new TH1F("eta33en", "eta33", 60, 0, 150);
   beautify(eta33en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta34en = new TH1F("eta34en", "eta34", 60, 0, 150);
   beautify(eta34en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta35en = new TH1F("eta35en", "eta35", 60, 0, 150);
   beautify(eta35en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta36en = new TH1F("eta36en", "eta36", 60, 0, 150);
   beautify(eta36en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta37en = new TH1F("eta37en", "eta37", 60, 0, 150);
   beautify(eta37en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta38en = new TH1F("eta38en", "eta38", 60, 0, 150);
   beautify(eta38en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta39en = new TH1F("eta39en", "eta39", 60, 0, 150);
   beautify(eta39en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta40en = new TH1F("eta40en", "eta40", 60, 0, 150);
   beautify(eta40en, "E_{T}^{HF} [GeV]", "Events", 2);
   TH1F* eta41en = new TH1F("eta41en", "eta41", 60, 0, 150);
   beautify(eta41en, "E_{T}^{HF} [GeV]", "Events", 2);
   
   TH1F* eta30enEE = new TH1F("eta30enEE", "eta30", 60, 0, 150);
   beautify(eta30enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta31enEE = new TH1F("eta31enEE", "eta31", 60, 0, 150);
   beautify(eta31enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta32enEE = new TH1F("eta32enEE", "eta32", 60, 0, 150);
   beautify(eta32enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta33enEE = new TH1F("eta33enEE", "eta33", 60, 0, 150);
   beautify(eta33enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta34enEE = new TH1F("eta34enEE", "eta34", 60, 0, 150);
   beautify(eta34enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta35enEE = new TH1F("eta35enEE", "eta35", 60, 0, 150);
   beautify(eta35enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta36enEE = new TH1F("eta36enEE", "eta36", 60, 0, 150);
   beautify(eta36enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta37enEE = new TH1F("eta37enEE", "eta37", 60, 0, 150);
   beautify(eta37enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta38enEE = new TH1F("eta38enEE", "eta38", 60, 0, 150);
   beautify(eta38enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta39enEE = new TH1F("eta39enEE", "eta39", 60, 0, 150);
   beautify(eta39enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta40enEE = new TH1F("eta40enEE", "eta40", 60, 0, 150);
   beautify(eta40enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);
   TH1F* eta41enEE = new TH1F("eta41enEE", "eta41", 60, 0, 150);
   beautify(eta41enEE, "E_{T}^{ECAL} [GeV]", "Events", 2);   
     
   double alpha = 1;
   double beta = 1;

   std::stringstream ratio;
   Long64_t eventsProcessed = 0;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if ( jentry%1000 == 0 ) cout << "Processed " << jentry << " events" << endl;
      if ((jentry % (nentries / 50)) == 0) {
	ratio << std::fixed << std::setprecision(2) << 100.0 * (double)jentry / nentries;
	std::cout << ratio.str() << "%" << std::endl;
	ratio.str(std::string());
      }
      
      // PU bins
      bool PU1 = (nvtx <= 6); 
      bool PU2 = (nvtx > 6 && nvtx <= 12); 
      bool PU3 = (nvtx > 12 && nvtx <= 18); 
      bool PU4 = (nvtx > 18 && nvtx <= 24); 
      bool PU5 = (nvtx > 24 && nvtx <= 30); 
      bool PU6 = (nvtx > 30 && nvtx <= 36); 
      bool PU7 = (nvtx > 36 && nvtx <= 42);
      bool PU8 = (nvtx > 42 && nvtx <= 48);
      bool PU9 = (nvtx > 48);
      
      bool iEta33_after = false;
       if (isData == 1) {
           iEta33_after = (run >= 319819);
      }
      
      vector<TLorentzVector> electrons;
      for(int i = 0; i != nele; ++i ) {
	if ( ele_mediumID->at(i) == 0 ) continue;
	if ( ele_pt->at(i) < 25.0 ) continue; // energetic to fire trigger
	TLorentzVector e;
	e.SetPtEtaPhiM(ele_pt->at(i), ele_eta->at(i), ele_phi->at(i), 0);
	electrons.push_back(e);
      }

      vector<TLorentzVector> hf;
      int firstIndex = -1;
      for(int i = 0; i != nhf; ++i) {
	if ( hf_pt->at(i) < 15.0 ) continue;
	if ( fabs(hf_eta->at(i)) < 2.964 ) continue;
	if ( fabs(hf_eta->at(i)) > 5.191 ) continue;
	if ( hf_hcal->at(i)/hf_ecal->at(i) > 1.2 ) continue;
	if ( hf_iso->at(i)/hf_en->at(i) > 0.55 ) continue;
	
	// L - S = ecal
	// 2S = hcal
	double L = hf_ecal->at(i) + 0.5*hf_hcal->at(i);
	double S = hf_hcal->at(i)/2;
	if ( L == 0 && S == 0 ) continue;

	// Raddam correction - only data
	double corrL = L;
	double corrS = S;
	if (isData == 1) {
                       if (useRaddam == 1) { corrL = L/getRaddamCorrection(run, fabs(hf_eta->at(i))); }
                       if (useRaddam == 1) { corrS = S/getRaddamCorrection(run, fabs(hf_eta->at(i))); }
	}
	double corrpT = hf_pt->at(i)*(corrL + corrS)/(L + S);
	
	// Use only long fiber energy
	alpha = 1;
	beta = 0;
	
	TLorentzVector e;
	double newpT = corrpT*(corrL*alpha + corrS*beta)/(corrL + corrS);
	newpT *= 1.00; // cross check
	e.SetPtEtaPhiM(newpT, hf_eta->at(i), hf_phi->at(i), 0);
	hf.push_back(e);
	
	if ( firstIndex == -1 ) firstIndex = i;
      }
      if ( electrons.size() > 1 || electrons.size() == 0 ) continue;
      if ( hf.size() == 0 ) continue;

      TLorentzVector e1, e2;
      e1 = electrons[0];
      e2 = hf[0];
      
      double longFiberEn = hf_ecal->at(firstIndex) + 0.5*hf_hcal->at(firstIndex);
      double shortFiberEn = hf_hcal->at(firstIndex)/2;

      double Mass = (e1+e2).M();

      // PU corrected mass
      TLorentzVector e1pu;
      TLorentzVector e2pu;
      double puCorrection = 1;
      if (usePU == 1) { puCorrection = 1./(1.0 + 0.080/74.390*(nvtx-26)); } // MC (peak @ 26) 
      if (usePU == 1 && isData == 1 ) { puCorrection = 1./(1.0 + 0.088/73.909*(nvtx-26)); } // Data (peak @ 26)
      e1pu.SetPtEtaPhiM(e1.Pt()*puCorrection, e1.Eta(), e1.Phi(), 0);
      e2pu.SetPtEtaPhiM(e2.Pt()*puCorrection, e2.Eta(), e2.Phi(), 0);
      double MassPUCorrected = (e1pu + e2pu).M();
      Mass = MassPUCorrected;
       
      //if ( fabs(e1pu.Eta()) > 2.1 ) continue;
      //if ( e1pu.Pt() < 35 || e1pu.Pt() > 40 ) continue;
      //if ( e2pu.Pt() < 25 || e2pu.Pt() > 30 ) continue;
      
      h_mass->Fill(Mass);
      if ( shortFiberEn>0.0 ) h_lsRatio->Fill(longFiberEn/shortFiberEn);

      if ( PU1 ) nVtx1->Fill(Mass);
      if ( PU2 ) nVtx2->Fill(Mass);
      if ( PU3 ) nVtx3->Fill(Mass);
      if ( PU4 ) nVtx4->Fill(Mass);
      if ( PU5 ) nVtx5->Fill(Mass);
      if ( PU6 ) nVtx6->Fill(Mass);
      if ( PU7 ) nVtx7->Fill(Mass);
      if ( PU8 ) nVtx8->Fill(Mass);
      if ( PU9 ) nVtx9->Fill(Mass);
             
      float phi = e2pu.Phi();
      
      // iPhi bins
      bool iPhi1 = (phi > 0*TMath::Pi()/18 && phi < 1*TMath::Pi()/18);
      bool iPhi3 = (phi > 1*TMath::Pi()/18 && phi < 2*TMath::Pi()/18);
      bool iPhi5 = (phi > 2*TMath::Pi()/18 && phi < 3*TMath::Pi()/18);
      bool iPhi7 = (phi > 3*TMath::Pi()/18 && phi < 4*TMath::Pi()/18);
      bool iPhi9 = (phi > 4*TMath::Pi()/18 && phi < 5*TMath::Pi()/18);
      bool iPhi11 = (phi > 5*TMath::Pi()/18 && phi < 6*TMath::Pi()/18);
      bool iPhi13 = (phi > 6*TMath::Pi()/18 && phi < 7*TMath::Pi()/18);
      bool iPhi15 = (phi > 7*TMath::Pi()/18 && phi < 8*TMath::Pi()/18);
      bool iPhi17 = (phi > 8*TMath::Pi()/18 && phi < 9*TMath::Pi()/18);
      bool iPhi19 = (phi > 9*TMath::Pi()/18 && phi < 10*TMath::Pi()/18);
      bool iPhi21 = (phi > 10*TMath::Pi()/18 && phi < 11*TMath::Pi()/18);
      bool iPhi23 = (phi > 11*TMath::Pi()/18 && phi < 12*TMath::Pi()/18);
      bool iPhi25 = (phi > 12*TMath::Pi()/18 && phi < 13*TMath::Pi()/18);
      bool iPhi27 = (phi > 13*TMath::Pi()/18 && phi < 14*TMath::Pi()/18);
      bool iPhi29 = (phi > 14*TMath::Pi()/18 && phi < 15*TMath::Pi()/18);
      bool iPhi31 = (phi > 15*TMath::Pi()/18 && phi < 16*TMath::Pi()/18);
      bool iPhi33 = (phi > 16*TMath::Pi()/18 && phi < 17*TMath::Pi()/18);
      bool iPhi35 = (phi > 17*TMath::Pi()/18 && phi < 18*TMath::Pi()/18);
      bool iPhi37 = (phi > -18*TMath::Pi()/18 && phi < -17*TMath::Pi()/18);
      bool iPhi39 = (phi > -17*TMath::Pi()/18 && phi < -16*TMath::Pi()/18);
      bool iPhi41 = (phi > -16*TMath::Pi()/18 && phi < -15*TMath::Pi()/18);
      bool iPhi43 = (phi > -15*TMath::Pi()/18 && phi < -14*TMath::Pi()/18);
      bool iPhi45 = (phi > -14*TMath::Pi()/18 && phi < -13*TMath::Pi()/18);
      bool iPhi47 = (phi > -13*TMath::Pi()/18 && phi < -12*TMath::Pi()/18);
      bool iPhi49 = (phi > -12*TMath::Pi()/18 && phi < -11*TMath::Pi()/18);
      bool iPhi51 = (phi > -11*TMath::Pi()/18 && phi < -10*TMath::Pi()/18);
      bool iPhi53 = (phi > -10*TMath::Pi()/18 && phi < -9*TMath::Pi()/18);
      bool iPhi55 = (phi > -9*TMath::Pi()/18 && phi < -8*TMath::Pi()/18);
      bool iPhi57 = (phi > -8*TMath::Pi()/18 && phi < -7*TMath::Pi()/18);
      bool iPhi59 = (phi > -7*TMath::Pi()/18 && phi < -6*TMath::Pi()/18);
      bool iPhi61 = (phi > -6*TMath::Pi()/18 && phi < -5*TMath::Pi()/18);
      bool iPhi63 = (phi > -5*TMath::Pi()/18 && phi < -4*TMath::Pi()/18);
      bool iPhi65 = (phi > -4*TMath::Pi()/18 && phi < -3*TMath::Pi()/18);
      bool iPhi67 = (phi > -3*TMath::Pi()/18 && phi < -2*TMath::Pi()/18);
      bool iPhi69 = (phi > -2*TMath::Pi()/18 && phi < -1*TMath::Pi()/18);
      bool iPhi71 = (phi > -1*TMath::Pi()/18 && phi < 0*TMath::Pi()/18);
       
      bool iPhi3_EtaEnd = (phi > 0*TMath::Pi()/18 && phi < 2*TMath::Pi()/18);
      bool iPhi7_EtaEnd = (phi > 2*TMath::Pi()/18 && phi < 4*TMath::Pi()/18);
      bool iPhi11_EtaEnd = (phi > 4*TMath::Pi()/18 && phi < 6*TMath::Pi()/18);
      bool iPhi15_EtaEnd = (phi > 6*TMath::Pi()/18 && phi < 8*TMath::Pi()/18);
      bool iPhi19_EtaEnd = (phi > 8*TMath::Pi()/18 && phi < 10*TMath::Pi()/18);
      bool iPhi23_EtaEnd = (phi > 10*TMath::Pi()/18 && phi < 12*TMath::Pi()/18);
      bool iPhi27_EtaEnd = (phi > 12*TMath::Pi()/18 && phi < 14*TMath::Pi()/18);
      bool iPhi31_EtaEnd = (phi > 14*TMath::Pi()/18 && phi < 16*TMath::Pi()/18);
      bool iPhi35_EtaEnd = (phi > 16*TMath::Pi()/18 && phi < 18*TMath::Pi()/18);
      bool iPhi39_EtaEnd = (phi > -18*TMath::Pi()/18 && phi < -16*TMath::Pi()/18);
      bool iPhi43_EtaEnd = (phi > -16*TMath::Pi()/18 && phi < -14*TMath::Pi()/18);
      bool iPhi47_EtaEnd = (phi > -14*TMath::Pi()/18 && phi < -12*TMath::Pi()/18);
      bool iPhi51_EtaEnd = (phi > -12*TMath::Pi()/18 && phi < -10*TMath::Pi()/18);
      bool iPhi55_EtaEnd = (phi > -10*TMath::Pi()/18 && phi < -8*TMath::Pi()/18);
      bool iPhi59_EtaEnd = (phi > -8*TMath::Pi()/18 && phi < -6*TMath::Pi()/18);
      bool iPhi63_EtaEnd = (phi > -6*TMath::Pi()/18 && phi < -4*TMath::Pi()/18);
      bool iPhi67_EtaEnd = (phi > -4*TMath::Pi()/18 && phi < -2*TMath::Pi()/18);
      bool iPhi71_EtaEnd = (phi > -2*TMath::Pi()/18 && phi < 0*TMath::Pi()/18);
      
      if ( iPhi1 ) phi1->Fill(Mass);
      if ( iPhi3 ) phi3->Fill(Mass);
      if ( iPhi5 ) phi5->Fill(Mass);
      if ( iPhi7 ) phi7->Fill(Mass);
      if ( iPhi9 ) phi9->Fill(Mass);
      if ( iPhi11 ) phi11->Fill(Mass);
      if ( iPhi13 ) phi13->Fill(Mass);
      if ( iPhi15 ) phi15->Fill(Mass);
      if ( iPhi17 ) phi17->Fill(Mass);
      if ( iPhi19 ) phi19->Fill(Mass);
      if ( iPhi21 ) phi21->Fill(Mass);
      if ( iPhi23 ) phi23->Fill(Mass);
      if ( iPhi25 ) phi25->Fill(Mass);
      if ( iPhi27 ) phi27->Fill(Mass);
      if ( iPhi29 ) phi29->Fill(Mass);
      if ( iPhi31 ) phi31->Fill(Mass);
      if ( iPhi33 ) phi33->Fill(Mass);
      if ( iPhi35 ) phi35->Fill(Mass);
      if ( iPhi37 ) phi37->Fill(Mass);
      if ( iPhi39 ) phi39->Fill(Mass);
      if ( iPhi41 ) phi41->Fill(Mass);
      if ( iPhi43 ) phi43->Fill(Mass);
      if ( iPhi45 ) phi45->Fill(Mass);
      if ( iPhi47 ) phi47->Fill(Mass);
      if ( iPhi49 ) phi49->Fill(Mass);
      if ( iPhi51 ) phi51->Fill(Mass);
      if ( iPhi53 ) phi53->Fill(Mass);
      if ( iPhi55 ) phi55->Fill(Mass);
      if ( iPhi57 ) phi57->Fill(Mass);
      if ( iPhi59 ) phi59->Fill(Mass);
      if ( iPhi61 ) phi61->Fill(Mass);
      if ( iPhi63 ) phi63->Fill(Mass);
      if ( iPhi65 ) phi65->Fill(Mass);
      if ( iPhi67 ) phi67->Fill(Mass);
      if ( iPhi69 ) phi69->Fill(Mass);
      if ( iPhi71 ) phi71->Fill(Mass);
      
      double eta = e2pu.Eta();
      
      // iEta bins
      bool iEta30Plus = eta > 2.964 && eta < 3.139;
      bool iEta31Plus = eta > 3.139 && eta < 3.314;
      bool iEta32Plus = eta > 3.314 && eta < 3.489;
      bool iEta33Plus = eta > 3.489 && eta < 3.664;
      bool iEta34Plus = eta > 3.664 && eta < 3.839;
      bool iEta35Plus = eta > 3.839 && eta < 4.013;
      bool iEta36Plus = eta > 4.013 && eta < 4.191;
      bool iEta37Plus = eta > 4.191 && eta < 4.363;
      bool iEta38Plus = eta > 4.363 && eta < 4.538;
      bool iEta39Plus = eta > 4.538 && eta < 4.716;
      bool iEta40Plus = eta > 4.716 && eta < 4.889;
      bool iEta41Plus = eta > 4.889 && eta < 5.191;
      bool iEta30Minus = eta < -2.964 && eta > -3.139;
      bool iEta31Minus = eta < -3.139 && eta > -3.314;
      bool iEta32Minus = eta < -3.314 && eta > -3.489;
      bool iEta33Minus = eta < -3.489 && eta > -3.664;
      bool iEta34Minus = eta < -3.664 && eta > -3.839;
      bool iEta35Minus = eta < -3.839 && eta > -4.013;
      bool iEta36Minus = eta < -4.013 && eta > -4.191;
      bool iEta37Minus = eta < -4.191 && eta > -4.363;
      bool iEta38Minus = eta < -4.363 && eta > -4.538;
      bool iEta39Minus = eta < -4.538 && eta > -4.716;
      bool iEta40Minus = eta < -4.716 && eta > -4.889;
      bool iEta41Minus = eta < -4.889 && eta > -5.191;
      
      if ( iEta30Plus ) etaPlus30->Fill(Mass);
      if ( iEta31Plus ) etaPlus31->Fill(Mass);
      if ( iEta32Plus ) etaPlus32->Fill(Mass);
      if ( iEta33Plus ) etaPlus33->Fill(Mass);
      if ( iEta34Plus ) etaPlus34->Fill(Mass);
      if ( iEta35Plus ) etaPlus35->Fill(Mass);
      if ( iEta36Plus ) etaPlus36->Fill(Mass);
      if ( iEta37Plus ) etaPlus37->Fill(Mass);
      if ( iEta38Plus ) etaPlus38->Fill(Mass);
      if ( iEta39Plus ) etaPlus39->Fill(Mass);
      if ( iEta40Plus ) etaPlus40->Fill(Mass);
      if ( iEta41Plus ) etaPlus41->Fill(Mass);
      if ( iEta30Minus ) etaMinus30->Fill(Mass);
      if ( iEta31Minus ) etaMinus31->Fill(Mass);
      if ( iEta32Minus ) etaMinus32->Fill(Mass);
      if ( iEta33Minus ) etaMinus33->Fill(Mass);
      if ( iEta34Minus ) etaMinus34->Fill(Mass);
      if ( iEta35Minus ) etaMinus35->Fill(Mass);
      if ( iEta36Minus ) etaMinus36->Fill(Mass);
      if ( iEta37Minus ) etaMinus37->Fill(Mass);
      if ( iEta38Minus ) etaMinus38->Fill(Mass);
      if ( iEta39Minus ) etaMinus39->Fill(Mass);
      if ( iEta40Minus ) etaMinus40->Fill(Mass);
      if ( iEta41Minus ) etaMinus41->Fill(Mass);
      
      h_nvtx->Fill(nvtx);
      
      if ( iEta30Plus || iEta30Minus ) {
    if ( shortFiberEn>0.0 ) eta30lsRatio->Fill(longFiberEn/shortFiberEn);
    eta30nvtx->Fill(nvtx);
	eta30phi->Fill(e2.Phi());
	eta30etaEE->Fill(e1.Eta());
	eta30phiEE->Fill(e1.Phi());
	eta30dphi->Fill(e1.Phi()-e2.Phi());
	eta30en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta30enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta31Plus || iEta31Minus ) {
    if ( shortFiberEn>0.0 ) eta31lsRatio->Fill(longFiberEn/shortFiberEn);
    eta31nvtx->Fill(nvtx);
	eta31phi->Fill(e2.Phi());
	eta31etaEE->Fill(e1.Eta());
	eta31phiEE->Fill(e1.Phi());
	eta31dphi->Fill(e1.Phi()-e2.Phi());
	eta31en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta31enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta32Plus || iEta32Minus ) {
    if ( shortFiberEn>0.0 ) eta32lsRatio->Fill(longFiberEn/shortFiberEn);
    eta32nvtx->Fill(nvtx);
	eta32phi->Fill(e2.Phi());
	eta32etaEE->Fill(e1.Eta());
	eta32phiEE->Fill(e1.Phi());
	eta32dphi->Fill(e1.Phi()-e2.Phi());
	eta32en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta32enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta33Plus || iEta33Minus ) {
    if ( shortFiberEn>0.0 ) eta33lsRatio->Fill(longFiberEn/shortFiberEn);
    eta33nvtx->Fill(nvtx);
	eta33phi->Fill(e2.Phi());
	eta33etaEE->Fill(e1.Eta());
	eta33phiEE->Fill(e1.Phi());
	eta33dphi->Fill(e1.Phi()-e2.Phi());
	eta33en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta33enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
    if ( iEta33_after ) {h_mass_iEta33_after->Fill(Mass);}
    else {h_mass_iEta33_before->Fill(Mass);}
      }
      if ( iEta34Plus || iEta34Minus ) {
    if ( shortFiberEn>0.0 ) eta34lsRatio->Fill(longFiberEn/shortFiberEn);
    eta34nvtx->Fill(nvtx);
	eta34phi->Fill(e2.Phi());
	eta34etaEE->Fill(e1.Eta());
	eta34phiEE->Fill(e1.Phi());
	eta34dphi->Fill(e1.Phi()-e2.Phi());
	eta34en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta34enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta35Plus || iEta35Minus ) {
    if ( shortFiberEn>0.0 ) eta35lsRatio->Fill(longFiberEn/shortFiberEn);
    eta35nvtx->Fill(nvtx);
	eta35phi->Fill(e2.Phi());
	eta35etaEE->Fill(e1.Eta());
	eta35phiEE->Fill(e1.Phi());
	eta35dphi->Fill(e1.Phi()-e2.Phi());
	eta35en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta35enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta36Plus || iEta36Minus ) {
    if ( shortFiberEn>0.0 ) eta36lsRatio->Fill(longFiberEn/shortFiberEn);
    eta36nvtx->Fill(nvtx);
	eta36phi->Fill(e2.Phi());
	eta36etaEE->Fill(e1.Eta());
	eta36phiEE->Fill(e1.Phi());
	eta36dphi->Fill(e1.Phi()-e2.Phi());
	eta36en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta36enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta37Plus || iEta37Minus ) {
    if ( shortFiberEn>0.0 ) eta37lsRatio->Fill(longFiberEn/shortFiberEn);
    eta37nvtx->Fill(nvtx);
	eta37phi->Fill(e2.Phi());
	eta37etaEE->Fill(e1.Eta());
	eta37phiEE->Fill(e1.Phi());
	eta37dphi->Fill(e1.Phi()-e2.Phi());
	eta37en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta37enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta38Plus || iEta38Minus ) {
    if ( shortFiberEn>0.0 ) eta38lsRatio->Fill(longFiberEn/shortFiberEn);
    eta38nvtx->Fill(nvtx);
	eta38phi->Fill(e2.Phi());
	eta38etaEE->Fill(e1.Eta());
	eta38phiEE->Fill(e1.Phi());
	eta38dphi->Fill(e1.Phi()-e2.Phi());
	eta38en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta38enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta39Plus || iEta39Minus ) {
    if ( shortFiberEn>0.0 ) eta39lsRatio->Fill(longFiberEn/shortFiberEn);
    eta39nvtx->Fill(nvtx);
	eta39phi->Fill(e2.Phi());
	eta39etaEE->Fill(e1.Eta());
	eta39phiEE->Fill(e1.Phi());
	eta39dphi->Fill(e1.Phi()-e2.Phi());
	eta39en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta39enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta40Plus || iEta40Minus ) {
    if ( shortFiberEn>0.0 ) eta40lsRatio->Fill(longFiberEn/shortFiberEn);
    eta40nvtx->Fill(nvtx);
	eta40phi->Fill(e2.Phi());
	eta40etaEE->Fill(e1.Eta());
	eta40phiEE->Fill(e1.Phi());
	eta40dphi->Fill(e1.Phi()-e2.Phi());
	eta40en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta40enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
      if ( iEta41Plus || iEta41Minus ) {
    if ( shortFiberEn>0.0 ) eta41lsRatio->Fill(longFiberEn/shortFiberEn);
    eta41nvtx->Fill(nvtx);
	eta41phi->Fill(e2.Phi());
	eta41etaEE->Fill(e1.Eta());
	eta41phiEE->Fill(e1.Phi());
	eta41dphi->Fill(e1.Phi()-e2.Phi());
	eta41en->Fill(e2.E()*TMath::Sin(e2.Theta()));
	eta41enEE->Fill(e1.E()*TMath::Sin(e1.Theta()));
      }
       
      if ( iPhi1 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi1->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi1->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi1->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi1->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi1->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi1->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi1->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi1->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi1->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi1->Fill(Mass);
      }
      if ( iPhi3 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi3->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi3->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi3->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi3->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi3->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi3->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi3->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi3->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi3->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi3->Fill(Mass);
      }
      if ( iPhi5 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi5->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi5->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi5->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi5->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi5->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi5->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi5->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi5->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi5->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi5->Fill(Mass);
      }
      if ( iPhi7 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi7->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi7->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi7->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi7->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi7->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi7->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi7->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi7->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi7->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi7->Fill(Mass);
	if ( iEta40Plus || iEta40Minus ) eta40phi7->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi7->Fill(Mass);
      }
      if ( iPhi9 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi9->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi9->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi9->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi9->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi9->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi9->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi9->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi9->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi9->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi9->Fill(Mass);
      }
      if ( iPhi11 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi11->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi11->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi11->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi11->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi11->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi11->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi11->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi11->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi11->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi11->Fill(Mass);
      }
      if ( iPhi13 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi13->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi13->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi13->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi13->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi13->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi13->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi13->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi13->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi13->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi13->Fill(Mass);
      }
      if ( iPhi15 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi15->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi15->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi15->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi15->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi15->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi15->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi15->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi15->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi15->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi15->Fill(Mass);
      }
      if ( iPhi17 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi17->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi17->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi17->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi17->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi17->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi17->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi17->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi17->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi17->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi17->Fill(Mass);
      }
      if ( iPhi19 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi19->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi19->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi19->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi19->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi19->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi19->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi19->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi19->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi19->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi19->Fill(Mass);
      }
      if ( iPhi21 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi21->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi21->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi21->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi21->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi21->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi21->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi21->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi21->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi21->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi21->Fill(Mass);
      }
      if ( iPhi23 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi23->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi23->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi23->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi23->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi23->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi23->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi23->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi23->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi23->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi23->Fill(Mass);
      }
      if ( iPhi25 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi25->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi25->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi25->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi25->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi25->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi25->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi25->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi25->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi25->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi25->Fill(Mass);
      }
      if ( iPhi27 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi27->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi27->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi27->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi27->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi27->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi27->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi27->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi27->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi27->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi27->Fill(Mass);
      }
      if ( iPhi29 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi29->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi29->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi29->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi29->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi29->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi29->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi29->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi29->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi29->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi29->Fill(Mass);
      }
      if ( iPhi31 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi31->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi31->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi31->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi31->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi31->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi31->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi31->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi31->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi31->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi31->Fill(Mass);
      }
      if ( iPhi33 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi33->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi33->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi33->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi33->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi33->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi33->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi33->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi33->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi33->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi33->Fill(Mass);
      }
      if ( iPhi35 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi35->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi35->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi35->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi35->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi35->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi35->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi35->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi35->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi35->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi35->Fill(Mass);
      }
      if ( iPhi37 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi37->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi37->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi37->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi37->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi37->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi37->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi37->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi37->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi37->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi37->Fill(Mass);
      }
      if ( iPhi39 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi39->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi39->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi39->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi39->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi39->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi39->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi39->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi39->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi39->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi39->Fill(Mass);
      }
      if ( iPhi41 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi41->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi41->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi41->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi41->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi41->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi41->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi41->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi41->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi41->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi41->Fill(Mass);
      }
      if ( iPhi43 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi43->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi43->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi43->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi43->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi43->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi43->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi43->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi43->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi43->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi43->Fill(Mass);
      }
      if ( iPhi45 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi45->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi45->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi45->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi45->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi45->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi45->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi45->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi45->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi45->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi45->Fill(Mass);
      }
      if ( iPhi47 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi47->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi47->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi47->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi47->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi47->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi47->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi47->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi47->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi47->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi47->Fill(Mass);
      }
      if ( iPhi49 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi49->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi49->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi49->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi49->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi49->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi49->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi49->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi49->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi49->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi49->Fill(Mass);
      }
      if ( iPhi51 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi51->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi51->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi51->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi51->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi51->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi51->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi51->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi51->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi51->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi51->Fill(Mass);
      }
      if ( iPhi53 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi53->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi53->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi53->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi53->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi53->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi53->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi53->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi53->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi53->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi53->Fill(Mass);
      }
      if ( iPhi55 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi55->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi55->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi55->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi55->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi55->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi55->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi55->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi55->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi55->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi55->Fill(Mass);
      }
      if ( iPhi57 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi57->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi57->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi57->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi57->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi57->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi57->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi57->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi57->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi57->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi57->Fill(Mass);
      }
      if ( iPhi59 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi59->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi59->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi59->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi59->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi59->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi59->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi59->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi59->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi59->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi59->Fill(Mass);
      }
      if ( iPhi61 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi61->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi61->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi61->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi61->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi61->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi61->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi61->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi61->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi61->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi61->Fill(Mass);
      }
      if ( iPhi63 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi63->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi63->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi63->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi63->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi63->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi63->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi63->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi63->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi63->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi63->Fill(Mass);
      }
      if ( iPhi65 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi65->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi65->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi65->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi65->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi65->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi65->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi65->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi65->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi65->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi65->Fill(Mass);
      }
      if ( iPhi67 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi67->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi67->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi67->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi67->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi67->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi67->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi67->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi67->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi67->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi67->Fill(Mass);
      }
      if ( iPhi69 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi69->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi69->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi69->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi69->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi69->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi69->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi69->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi69->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi69->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi69->Fill(Mass);
      }
      if ( iPhi71 ) {
	if ( iEta30Plus || iEta30Minus ) eta30phi71->Fill(Mass);
	if ( iEta31Plus || iEta31Minus ) eta31phi71->Fill(Mass);
	if ( iEta32Plus || iEta32Minus ) eta32phi71->Fill(Mass);
	if ( iEta33Plus || iEta33Minus ) eta33phi71->Fill(Mass);
	if ( iEta34Plus || iEta34Minus ) eta34phi71->Fill(Mass);
	if ( iEta35Plus || iEta35Minus ) eta35phi71->Fill(Mass);
	if ( iEta36Plus || iEta36Minus ) eta36phi71->Fill(Mass);
	if ( iEta37Plus || iEta37Minus ) eta37phi71->Fill(Mass);
	if ( iEta38Plus || iEta38Minus ) eta38phi71->Fill(Mass);
	if ( iEta39Plus || iEta39Minus ) eta39phi71->Fill(Mass);
      }
      
      if ( iPhi3_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi3->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi3->Fill(Mass);
      }
      if ( iPhi7_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi7->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi7->Fill(Mass);
      }
      if ( iPhi11_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi11->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi11->Fill(Mass);
      }
      if ( iPhi15_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi15->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi15->Fill(Mass);
      }
      if ( iPhi19_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi19->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi19->Fill(Mass);
      }
      if ( iPhi23_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi23->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi23->Fill(Mass);
      }
      if ( iPhi27_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi27->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi27->Fill(Mass);
      }
      if ( iPhi31_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi31->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi31->Fill(Mass);
      }
      if ( iPhi35_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi35->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi35->Fill(Mass);
      }
      if ( iPhi39_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi39->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi39->Fill(Mass);
      }
      if ( iPhi43_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi43->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi43->Fill(Mass);
      }
      if ( iPhi47_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi47->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi47->Fill(Mass);
      }
      if ( iPhi51_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi51->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi51->Fill(Mass);
      }
      if ( iPhi55_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi55->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi55->Fill(Mass);
      }
      if ( iPhi59_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi59->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi59->Fill(Mass);
      }
      if ( iPhi63_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi63->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi63->Fill(Mass);
      }
      if ( iPhi67_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi67->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi67->Fill(Mass);
      }
      if ( iPhi71_EtaEnd ) {
	if ( iEta40Plus || iEta40Minus ) eta40phi71->Fill(Mass);
	if ( iEta41Plus || iEta41Minus ) eta41phi71->Fill(Mass);
      }
      
   }

   h_mass->Write();
   h_nvtx->Write();
   h_lsRatio->Write();
 
   etaPlus30->Write();
   etaPlus31->Write();
   etaPlus32->Write();
   etaPlus33->Write();
   etaPlus34->Write();
   etaPlus35->Write();
   etaPlus36->Write();
   etaPlus37->Write();
   etaPlus38->Write();
   etaPlus39->Write();
   etaPlus40->Write();
   etaPlus41->Write();
   etaMinus30->Write();
   etaMinus31->Write();
   etaMinus32->Write();
   etaMinus33->Write();
   etaMinus34->Write();
   etaMinus35->Write();
   etaMinus36->Write();
   etaMinus37->Write();
   etaMinus38->Write();
   etaMinus39->Write();
   etaMinus40->Write();
   etaMinus41->Write();

   phi1->Write();
   phi3->Write();
   phi5->Write();
   phi7->Write();
   phi9->Write();
   phi11->Write();
   phi13->Write();
   phi15->Write();
   phi17->Write();
   phi19->Write();
   phi21->Write();
   phi23->Write();
   phi25->Write();
   phi27->Write();
   phi29->Write();
   phi31->Write();
   phi33->Write();
   phi35->Write();
   phi37->Write();
   phi39->Write();
   phi41->Write();
   phi43->Write();
   phi45->Write();
   phi47->Write();
   phi49->Write();
   phi51->Write();
   phi53->Write();
   phi55->Write();
   phi57->Write();
   phi59->Write();
   phi61->Write();
   phi63->Write();
   phi65->Write();
   phi67->Write();
   phi69->Write();
   phi71->Write();
   
   nVtx1->Write();
   nVtx2->Write();
   nVtx3->Write();
   nVtx4->Write();
   nVtx5->Write();
   nVtx6->Write();
   nVtx7->Write();
   nVtx8->Write();
   nVtx9->Write();
   
   h_mass_iEta33_before->Write();
   h_mass_iEta33_after->Write();
    
   eta30phi1->Write();
   eta30phi3->Write();
   eta30phi5->Write();
   eta30phi7->Write();
   eta30phi9->Write();
   eta30phi11->Write();
   eta30phi13->Write();
   eta30phi15->Write();
   eta30phi17->Write();
   eta30phi19->Write();
   eta30phi21->Write();
   eta30phi23->Write();
   eta30phi25->Write();
   eta30phi27->Write();
   eta30phi29->Write();
   eta30phi31->Write();
   eta30phi33->Write();
   eta30phi35->Write();
   eta30phi37->Write();
   eta30phi39->Write();
   eta30phi41->Write();
   eta30phi43->Write();
   eta30phi45->Write();
   eta30phi47->Write();
   eta30phi49->Write();
   eta30phi51->Write();
   eta30phi53->Write();
   eta30phi55->Write();
   eta30phi57->Write();
   eta30phi59->Write();
   eta30phi61->Write();
   eta30phi63->Write();
   eta30phi65->Write();
   eta30phi67->Write();
   eta30phi69->Write();
   eta30phi71->Write();
   eta31phi1->Write();
   eta31phi3->Write();
   eta31phi5->Write();
   eta31phi7->Write();
   eta31phi9->Write();
   eta31phi11->Write();
   eta31phi13->Write();
   eta31phi15->Write();
   eta31phi17->Write();
   eta31phi19->Write();
   eta31phi21->Write();
   eta31phi23->Write();
   eta31phi25->Write();
   eta31phi27->Write();
   eta31phi29->Write();
   eta31phi31->Write();
   eta31phi33->Write();
   eta31phi35->Write();
   eta31phi37->Write();
   eta31phi39->Write();
   eta31phi41->Write();
   eta31phi43->Write();
   eta31phi45->Write();
   eta31phi47->Write();
   eta31phi49->Write();
   eta31phi51->Write();
   eta31phi53->Write();
   eta31phi55->Write();
   eta31phi57->Write();
   eta31phi59->Write();
   eta31phi61->Write();
   eta31phi63->Write();
   eta31phi65->Write();
   eta31phi67->Write();
   eta31phi69->Write();
   eta31phi71->Write();
   eta32phi1->Write();
   eta32phi3->Write();
   eta32phi5->Write();
   eta32phi7->Write();
   eta32phi9->Write();
   eta32phi11->Write();
   eta32phi13->Write();
   eta32phi15->Write();
   eta32phi17->Write();
   eta32phi19->Write();
   eta32phi21->Write();
   eta32phi23->Write();
   eta32phi25->Write();
   eta32phi27->Write();
   eta32phi29->Write();
   eta32phi31->Write();
   eta32phi33->Write();
   eta32phi35->Write();
   eta32phi37->Write();
   eta32phi39->Write();
   eta32phi41->Write();
   eta32phi43->Write();
   eta32phi45->Write();
   eta32phi47->Write();
   eta32phi49->Write();
   eta32phi51->Write();
   eta32phi53->Write();
   eta32phi55->Write();
   eta32phi57->Write();
   eta32phi59->Write();
   eta32phi61->Write();
   eta32phi63->Write();
   eta32phi65->Write();
   eta32phi67->Write();
   eta32phi69->Write();
   eta32phi71->Write();
   eta33phi1->Write();
   eta33phi3->Write();
   eta33phi5->Write();
   eta33phi7->Write();
   eta33phi9->Write();
   eta33phi11->Write();
   eta33phi13->Write();
   eta33phi15->Write();
   eta33phi17->Write();
   eta33phi19->Write();
   eta33phi21->Write();
   eta33phi23->Write();
   eta33phi25->Write();
   eta33phi27->Write();
   eta33phi29->Write();
   eta33phi31->Write();
   eta33phi33->Write();
   eta33phi35->Write();
   eta33phi37->Write();
   eta33phi39->Write();
   eta33phi41->Write();
   eta33phi43->Write();
   eta33phi45->Write();
   eta33phi47->Write();
   eta33phi49->Write();
   eta33phi51->Write();
   eta33phi53->Write();
   eta33phi55->Write();
   eta33phi57->Write();
   eta33phi59->Write();
   eta33phi61->Write();
   eta33phi63->Write();
   eta33phi65->Write();
   eta33phi67->Write();
   eta33phi69->Write();
   eta33phi71->Write();
   eta34phi1->Write();
   eta34phi3->Write();
   eta34phi5->Write();
   eta34phi7->Write();
   eta34phi9->Write();
   eta34phi11->Write();
   eta34phi13->Write();
   eta34phi15->Write();
   eta34phi17->Write();
   eta34phi19->Write();
   eta34phi21->Write();
   eta34phi23->Write();
   eta34phi25->Write();
   eta34phi27->Write();
   eta34phi29->Write();
   eta34phi31->Write();
   eta34phi33->Write();
   eta34phi35->Write();
   eta34phi37->Write();
   eta34phi39->Write();
   eta34phi41->Write();
   eta34phi43->Write();
   eta34phi45->Write();
   eta34phi47->Write();
   eta34phi49->Write();
   eta34phi51->Write();
   eta34phi53->Write();
   eta34phi55->Write();
   eta34phi57->Write();
   eta34phi59->Write();
   eta34phi61->Write();
   eta34phi63->Write();
   eta34phi65->Write();
   eta34phi67->Write();
   eta34phi69->Write();
   eta34phi71->Write();
   eta35phi1->Write();
   eta35phi3->Write();
   eta35phi5->Write();
   eta35phi7->Write();
   eta35phi9->Write();
   eta35phi11->Write();
   eta35phi13->Write();
   eta35phi15->Write();
   eta35phi17->Write();
   eta35phi19->Write();
   eta35phi21->Write();
   eta35phi23->Write();
   eta35phi25->Write();
   eta35phi27->Write();
   eta35phi29->Write();
   eta35phi31->Write();
   eta35phi33->Write();
   eta35phi35->Write();
   eta35phi37->Write();
   eta35phi39->Write();
   eta35phi41->Write();
   eta35phi43->Write();
   eta35phi45->Write();
   eta35phi47->Write();
   eta35phi49->Write();
   eta35phi51->Write();
   eta35phi53->Write();
   eta35phi55->Write();
   eta35phi57->Write();
   eta35phi59->Write();
   eta35phi61->Write();
   eta35phi63->Write();
   eta35phi65->Write();
   eta35phi67->Write();
   eta35phi69->Write();
   eta35phi71->Write();
   eta36phi1->Write();
   eta36phi3->Write();
   eta36phi5->Write();
   eta36phi7->Write();
   eta36phi9->Write();
   eta36phi11->Write();
   eta36phi13->Write();
   eta36phi15->Write();
   eta36phi17->Write();
   eta36phi19->Write();
   eta36phi21->Write();
   eta36phi23->Write();
   eta36phi25->Write();
   eta36phi27->Write();
   eta36phi29->Write();
   eta36phi31->Write();
   eta36phi33->Write();
   eta36phi35->Write();
   eta36phi37->Write();
   eta36phi39->Write();
   eta36phi41->Write();
   eta36phi43->Write();
   eta36phi45->Write();
   eta36phi47->Write();
   eta36phi49->Write();
   eta36phi51->Write();
   eta36phi53->Write();
   eta36phi55->Write();
   eta36phi57->Write();
   eta36phi59->Write();
   eta36phi61->Write();
   eta36phi63->Write();
   eta36phi65->Write();
   eta36phi67->Write();
   eta36phi69->Write();
   eta36phi71->Write();
   eta37phi1->Write();
   eta37phi3->Write();
   eta37phi5->Write();
   eta37phi7->Write();
   eta37phi9->Write();
   eta37phi11->Write();
   eta37phi13->Write();
   eta37phi15->Write();
   eta37phi17->Write();
   eta37phi19->Write();
   eta37phi21->Write();
   eta37phi23->Write();
   eta37phi25->Write();
   eta37phi27->Write();
   eta37phi29->Write();
   eta37phi31->Write();
   eta37phi33->Write();
   eta37phi35->Write();
   eta37phi37->Write();
   eta37phi39->Write();
   eta37phi41->Write();
   eta37phi43->Write();
   eta37phi45->Write();
   eta37phi47->Write();
   eta37phi49->Write();
   eta37phi51->Write();
   eta37phi53->Write();
   eta37phi55->Write();
   eta37phi57->Write();
   eta37phi59->Write();
   eta37phi61->Write();
   eta37phi63->Write();
   eta37phi65->Write();
   eta37phi67->Write();
   eta37phi69->Write();
   eta37phi71->Write();
   eta38phi1->Write();
   eta38phi3->Write();
   eta38phi5->Write();
   eta38phi7->Write();
   eta38phi9->Write();
   eta38phi11->Write();
   eta38phi13->Write();
   eta38phi15->Write();
   eta38phi17->Write();
   eta38phi19->Write();
   eta38phi21->Write();
   eta38phi23->Write();
   eta38phi25->Write();
   eta38phi27->Write();
   eta38phi29->Write();
   eta38phi31->Write();
   eta38phi33->Write();
   eta38phi35->Write();
   eta38phi37->Write();
   eta38phi39->Write();
   eta38phi41->Write();
   eta38phi43->Write();
   eta38phi45->Write();
   eta38phi47->Write();
   eta38phi49->Write();
   eta38phi51->Write();
   eta38phi53->Write();
   eta38phi55->Write();
   eta38phi57->Write();
   eta38phi59->Write();
   eta38phi61->Write();
   eta38phi63->Write();
   eta38phi65->Write();
   eta38phi67->Write();
   eta38phi69->Write();
   eta38phi71->Write();
   eta39phi1->Write();
   eta39phi3->Write();
   eta39phi5->Write();
   eta39phi7->Write();
   eta39phi9->Write();
   eta39phi11->Write();
   eta39phi13->Write();
   eta39phi15->Write();
   eta39phi17->Write();
   eta39phi19->Write();
   eta39phi21->Write();
   eta39phi23->Write();
   eta39phi25->Write();
   eta39phi27->Write();
   eta39phi29->Write();
   eta39phi31->Write();
   eta39phi33->Write();
   eta39phi35->Write();
   eta39phi37->Write();
   eta39phi39->Write();
   eta39phi41->Write();
   eta39phi43->Write();
   eta39phi45->Write();
   eta39phi47->Write();
   eta39phi49->Write();
   eta39phi51->Write();
   eta39phi53->Write();
   eta39phi55->Write();
   eta39phi57->Write();
   eta39phi59->Write();
   eta39phi61->Write();
   eta39phi63->Write();
   eta39phi65->Write();
   eta39phi67->Write();
   eta39phi69->Write();
   eta39phi71->Write();
   eta40phi3->Write();
   eta40phi7->Write();
   eta40phi11->Write();
   eta40phi15->Write();
   eta40phi19->Write();
   eta40phi23->Write();
   eta40phi27->Write();
   eta40phi31->Write();
   eta40phi35->Write();
   eta40phi39->Write();
   eta40phi43->Write();
   eta40phi47->Write();
   eta40phi51->Write();
   eta40phi55->Write();
   eta40phi59->Write();
   eta40phi63->Write();
   eta40phi67->Write();
   eta40phi71->Write();
   eta41phi3->Write();
   eta41phi7->Write();
   eta41phi11->Write();
   eta41phi15->Write();
   eta41phi19->Write();
   eta41phi23->Write();
   eta41phi27->Write();
   eta41phi31->Write();
   eta41phi35->Write();
   eta41phi39->Write();
   eta41phi43->Write();
   eta41phi47->Write();
   eta41phi51->Write();
   eta41phi55->Write();
   eta41phi59->Write();
   eta41phi63->Write();
   eta41phi67->Write();
   eta41phi71->Write();
    
   eta30lsRatio->Write();
   eta31lsRatio->Write();
   eta32lsRatio->Write();
   eta33lsRatio->Write();
   eta34lsRatio->Write();
   eta35lsRatio->Write();
   eta36lsRatio->Write();
   eta37lsRatio->Write();
   eta38lsRatio->Write();
   eta39lsRatio->Write();
   eta40lsRatio->Write();
   eta41lsRatio->Write();
   
   eta30nvtx->Write();
   eta31nvtx->Write();
   eta32nvtx->Write();
   eta33nvtx->Write();
   eta34nvtx->Write();
   eta35nvtx->Write();
   eta36nvtx->Write();
   eta37nvtx->Write();
   eta38nvtx->Write();
   eta39nvtx->Write();
   eta40nvtx->Write();
   eta41nvtx->Write();
   
   eta30phi->Write();
   eta31phi->Write();
   eta32phi->Write();
   eta33phi->Write();
   eta34phi->Write();
   eta35phi->Write();
   eta36phi->Write();
   eta37phi->Write();
   eta38phi->Write();
   eta39phi->Write();
   eta40phi->Write();
   eta41phi->Write();
   
   eta30etaEE->Write();
   eta31etaEE->Write();
   eta32etaEE->Write();
   eta33etaEE->Write();
   eta34etaEE->Write();
   eta35etaEE->Write();
   eta36etaEE->Write();
   eta37etaEE->Write();
   eta38etaEE->Write();
   eta39etaEE->Write();
   eta40etaEE->Write();
   eta41etaEE->Write();
   
   eta30phiEE->Write();
   eta31phiEE->Write();
   eta32phiEE->Write();
   eta33phiEE->Write();
   eta34phiEE->Write();
   eta35phiEE->Write();
   eta36phiEE->Write();
   eta37phiEE->Write();
   eta38phiEE->Write();
   eta39phiEE->Write();
   eta40phiEE->Write();
   eta41phiEE->Write();
   
   eta30dphi->Write();
   eta31dphi->Write();
   eta32dphi->Write();
   eta33dphi->Write();
   eta34dphi->Write();
   eta35dphi->Write();
   eta36dphi->Write();
   eta37dphi->Write();
   eta38dphi->Write();
   eta39dphi->Write();
   eta40dphi->Write();
   eta41dphi->Write();
   
   eta30en->Write();
   eta31en->Write();
   eta32en->Write();
   eta33en->Write();
   eta34en->Write();
   eta35en->Write();
   eta36en->Write();
   eta37en->Write();
   eta38en->Write();
   eta39en->Write();
   eta40en->Write();
   eta41en->Write();
   
   eta30enEE->Write();
   eta31enEE->Write();
   eta32enEE->Write();
   eta33enEE->Write();
   eta34enEE->Write();
   eta35enEE->Write();
   eta36enEE->Write();
   eta37enEE->Write();
   eta38enEE->Write();
   eta39enEE->Write();
   eta40enEE->Write();
   eta41enEE->Write();
     
}


