#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include "setTDRStyle.C"

#include "Raddam.C"

void beautify( TGraph* g1, short col) {
  g1->SetMarkerStyle(20);
  g1->SetMarkerSize(1);
  g1->SetMarkerColor( col);
  g1->SetLineColor( col);
  g1->SetTitle("");
}

void drawCMSLabel( std::string label) {
  TLatex CMSlabel = TLatex(); 
  CMSlabel.SetTextFont(42);     
  CMSlabel.SetNDC();     
  CMSlabel.SetTextSize(0.04);
  CMSlabel.DrawLatex( 0.128, 0.955, TString("#bf{CMS} #it{Preliminary} (" + label + ")"));
}

void printRaddam( std::string year) {
  TCanvas* canvas = new TCanvas("canvas");
  std::string figdir = "RaddamCorrections";
  int nFactors = 10;
  setRaddam(year, true);

  // Extract the factors
  std::vector<Float_t> xVals;
  std::vector<Float_t> yValsPlus, yValsMinus;
  
  // std::cout << ">>> Print & Plotting  RADDAM CORRECTIONS for " << year << std::endl;
  for (int iEta= 30; iEta <= 42; ++iEta) {
    xVals.push_back(iEta);
    yValsMinus.push_back( RaddamCorrections[-iEta]);
    yValsPlus.push_back( RaddamCorrections[iEta]);
  }
  
  auto graphPlus = new TGraph( nFactors, &xVals[0], &yValsPlus[0]);
  beautify( graphPlus, kRed);

  auto graphMinus = new TGraph( nFactors, &xVals[0], &yValsMinus[0]);
  beautify( graphMinus, kBlue);

  graphPlus->GetXaxis()->SetTitle("i#eta");
  graphPlus->GetYaxis()->SetTitle("Raddam Correction");
  graphPlus->GetYaxis()->SetTitleOffset(1.54);

  float max = 1.8;
  graphPlus->SetMinimum( 0);
  graphPlus->SetMaximum( max);
  graphPlus->GetYaxis()->SetRangeUser( 0, max);
  graphPlus->Draw("AP");
  graphMinus->Draw("PSAME");

  TF1 *fEta = new TF1("fEta","x",2.964,4.714);
  TGaxis *axisRaddamCorrs = new TGaxis( 29.5, max, 39.5, max, "fEta", 510, "-");
  axisRaddamCorrs->SetLabelFont(42);
  axisRaddamCorrs->SetLabelSize(0.035);
  axisRaddamCorrs->SetTitleSize(0.05);
  axisRaddamCorrs->SetLabelOffset(0.0025);
  axisRaddamCorrs->SetTitle("|#eta|");
  axisRaddamCorrs->Draw();

  drawCMSLabel( year);
  
  TLegend* legendRaddamCorrs = new TLegend(0.5,0.2,0.8,0.3,"","NDC");
  legendRaddamCorrs->AddEntry( graphPlus, "HF+ Corrs", "ep");
  legendRaddamCorrs->AddEntry( graphMinus, "HF- Corrs", "ep");
  legendRaddamCorrs->SetBorderSize(0);
  legendRaddamCorrs->Draw();

  // canvas->Print( TString( figdir + year + "_RaddamCorrs.png"));
  // canvas->SaveAs( TString( figdir + year + "_RaddamCorrs.C"));
}
