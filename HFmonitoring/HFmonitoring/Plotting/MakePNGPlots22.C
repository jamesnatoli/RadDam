#include <sys/stat.h>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include "setTDRStyle.C"

void MakePNGPlots22() {
  std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
  setTDRStyle();
  TCanvas* canvas = new TCanvas("canvas");
  // Make Changes Here
  TString figdir = "Figures22FG_afterHFTiming_noPU_RaddCorr_testAgain/";
  TString year = "2022";
  TFile *fMC = new TFile("outplots/output_DYJetsToLL_M-50_Winter22_PLOTS_mc_noPU_test.root");
  TFile *fData = new TFile("outplots/output_data_EGamma_Run2022FG_afterHFTiming_PLOTS_data_noPU_RaddCorr_testAgain.root");
  
  // TFile *fMC = new TFile("outplots/output_MC_DYto2L-4Jets_MLL-50_Winter23_PLOTS_mc_noPU_test.root");
  // TFile *fData = new TFile("outplots/output_data_EGamma_Run2023D_BPix_PLOTS_data_noPU_RaddCorr_testOriginalRatio.root");

  TF1 *funcGaus = new TF1("fitGaus","gaus",0,100);
  funcGaus->SetLineWidth(2);
  canvas->SetLogy(0);
  TLatex CMSlabel = TLatex(); 
  CMSlabel.SetTextFont(42);     
  CMSlabel.SetNDC();     
  CMSlabel.SetTextSize(0.04);

  if ((!fData) || (!fData->IsOpen())) {
    std::cout << "Data file didn't exist!" << std::endl;
    return;
  } else if ((!fMC) || (!fMC->IsOpen())){
    std::cout << "MC file didn't exist!" << std::endl;
    return;
  }

  std::cout << ">>> Figures Dirctory: " << figdir << std::endl;
  std::cout << ">>> Input MC: " << fMC->GetName() << std::endl;
  std::cout << ">>> Input Data: " << fData->GetName() << std::endl;
		
  //Inv Mass
  TH1F *hMassMC = (TH1F*)fMC->Get("h_mass");
  funcGaus->SetRange(hMassMC->GetMaximumBin()+5,hMassMC->GetMaximumBin()+35);
  hMassMC->GetXaxis()->SetTitleFont(42);
  hMassMC->GetYaxis()->SetTitleFont(42);
  hMassMC->GetXaxis()->SetTitleSize(0.04);
  hMassMC->GetYaxis()->SetTitleSize(0.04);
  hMassMC->GetXaxis()->SetTitleOffset(1.1);
  hMassMC->GetYaxis()->SetTitleOffset(1.54);
  hMassMC->GetXaxis()->SetLabelFont(42);
  hMassMC->GetYaxis()->SetLabelFont(42);
  hMassMC->GetXaxis()->SetLabelOffset(0.007);
  hMassMC->GetYaxis()->SetLabelOffset(0.007);
  hMassMC->GetXaxis()->SetLabelSize(0.04);
  hMassMC->GetYaxis()->SetLabelSize(0.03);
  hMassMC->SetLineColor(kBlack);
  hMassMC->Fit("fitGaus","RSQ");
  TString EntriesMassMC = TString::Format("Entries: %.0f", hMassMC->GetEntries());
  TString MeanMassMC = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
  TString SigmaMassMC = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
  TLatex TextMassMC = TLatex(); 
  TextMassMC.SetTextFont(42);     
  TextMassMC.SetNDC();     
  TextMassMC.SetTextSize(0.03);
  TextMassMC.DrawLatex(0.6,0.86,"#scale[1.2]{#font[62]{Inv. mass (MC LO)}}");
  TextMassMC.DrawLatex(0.6,0.81,EntriesMassMC);
  TextMassMC.DrawLatex(0.6,0.77,MeanMassMC);
  TextMassMC.DrawLatex(0.6,0.73,SigmaMassMC);
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "InvMass_mc.png");
  canvas->Clear();
  gStyle->SetPadLeftMargin(0.13);
	
  TH1F *hMassData = (TH1F*)fData->Get("h_mass");
  funcGaus->SetRange(hMassData->GetMaximumBin()+5,hMassData->GetMaximumBin()+35);
  hMassData->GetXaxis()->SetTitleFont(42);
  hMassData->GetYaxis()->SetTitleFont(42);
  hMassData->GetXaxis()->SetTitleSize(0.04);
  hMassData->GetYaxis()->SetTitleSize(0.04);
  hMassData->GetXaxis()->SetTitleOffset(1.1);
  hMassData->GetYaxis()->SetTitleOffset(1.54);
  hMassData->GetXaxis()->SetLabelFont(42);
  hMassData->GetYaxis()->SetLabelFont(42);
  hMassData->GetXaxis()->SetLabelOffset(0.007);
  hMassData->GetYaxis()->SetLabelOffset(0.007);
  hMassData->GetXaxis()->SetLabelSize(0.04);
  hMassData->GetYaxis()->SetLabelSize(0.03);
  hMassData->SetLineColor(kBlack);
  hMassData->Fit("fitGaus","RSQ");
  TString EntriesMassData = TString::Format("Entries: %.0f", hMassData->GetEntries());
  TString MeanMassData = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
  TString SigmaMassData = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
  TLatex TextMassData = TLatex(); 
  TextMassData.SetTextFont(42);     
  TextMassData.SetNDC();     
  TextMassData.SetTextSize(0.03);
  TextMassData.DrawLatex(0.6,0.86,"#scale[1.2]{#font[62]{Inv. mass (" + year + ")}}");
  TextMassData.DrawLatex(0.6,0.81,EntriesMassData);
  TextMassData.DrawLatex(0.6,0.77,MeanMassData);
  TextMassData.DrawLatex(0.6,0.73,SigmaMassData);
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "InvMass_data.png");
  canvas->Clear();
  gStyle->SetPadLeftMargin(0.13);

    
  TH1F *hLSRAtioData = (TH1F*)fData->Get("h_lsRatio");
  TH1F *hLSRAtioMC = (TH1F*)fMC->Get("h_lsRatio");
  hLSRAtioData->SetMarkerStyle(21);
  hLSRAtioData->SetMarkerSize(0.5);
  hLSRAtioData->SetMarkerColor(kRed);
  hLSRAtioData->SetLineColor(kRed);
  hLSRAtioData->Scale(1/hLSRAtioData->GetEntries());
  hLSRAtioMC->SetMarkerStyle(21);
  hLSRAtioMC->SetMarkerSize(0.5);
  hLSRAtioMC->SetMarkerColor(kBlue);
  hLSRAtioMC->SetLineColor(kBlue);
  hLSRAtioMC->Scale(1/hLSRAtioMC->GetEntries());
  THStack *LSRAtioStack = new THStack();
  LSRAtioStack->Add(hLSRAtioMC);
  LSRAtioStack->Add(hLSRAtioData);
  LSRAtioStack->Draw("nostack");
  LSRAtioStack->GetXaxis()->SetTitle("Long/Short Fiber Energy Ratio");
  LSRAtioStack->GetYaxis()->SetTitle("Norm. events");
  LSRAtioStack->SetMinimum(0);
  double MC_maxDPhi = 1.25*hLSRAtioMC->GetBinContent(hLSRAtioMC->GetMaximumBin());
  double Data_maxDPhi = 1.25*hLSRAtioData->GetBinContent(hLSRAtioData->GetMaximumBin());
  if (MC_maxDPhi > Data_maxDPhi) LSRAtioStack->SetMaximum(MC_maxDPhi);
  if (MC_maxDPhi < Data_maxDPhi) LSRAtioStack->SetMaximum(Data_maxDPhi);
  TLegend* legendLSRAtio = new TLegend(0.475,0.775,0.625,0.875,"","NDC");
  legendLSRAtio->AddEntry(hLSRAtioData, year, "p");
  legendLSRAtio->AddEntry(hLSRAtioMC, "MC LO", "p");
  legendLSRAtio->SetBorderSize(0);
  legendLSRAtio->Draw();
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  TString LSRAtioFitName = TString::Format( "%slsRatio.png", figdir.Data());
  canvas->Print(LSRAtioFitName);
  canvas->Clear();
  
  canvas->SetLogy(0);
  
  // Eta Loop
  TH1F *hEtaMCAll = new TH1F("hEtaMCAll", "", 10, 29.5, 39.5);
  TH1F *hEtaPlusDataAll = new TH1F("hEtaPlusDataAll", "", 10, 29.5, 39.5);
  TH1F *hEtaMinusDataAll = new TH1F("hEtaMinusDataAll", "", 10, 29.5, 39.5);
  TH1F *hEtaWidthMCAll = new TH1F("hEtaWidthMCAll", "", 10, 29.5, 39.5);
  TH1F *hEtaWidthDataAll = new TH1F("hEtaWidthDataAll", "", 10, 29.5, 39.5);
  for(int i = 30; i <= 39; ++i) {
    TString EtaPlusNum = TString::Format("etaPlus%i", i);
    TString EtaPlusBin = TString::Format("#eta%i (HF+)", i);
    canvas->SetLogy(0);		
    
    TH1F *hEtaPlusMC = (TH1F*)fMC->Get(EtaPlusNum);
    hEtaPlusMC->Draw();
    funcGaus->SetRange(hEtaPlusMC->GetMaximumBin()+5,hEtaPlusMC->GetMaximumBin()+35);
    TFitResultPtr FitResultEtaPlusMC = hEtaPlusMC->Fit("fitGaus","RSQ");
    double mcPlus = funcGaus->GetParameter(1);
    double mcPlusErr = funcGaus->GetParError(1);
    double mcWidthPlus = funcGaus->GetParameter(2);
    double mcWidthPlusErr = funcGaus->GetParError(2);
    TString EntriesEtaPlusMC = TString::Format("Entries: %.0f", hEtaPlusMC->GetEntries());
    TString MeanEtaPlusMC = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaEtaPlusMC = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2EtaPlusMC = TString::Format("#chi^{2} = %.2f", FitResultEtaPlusMC->Chi2());
    TString NDOFEtaPlusMC = TString::Format("ndf = %.0u",FitResultEtaPlusMC->Ndf());
    TLatex TextEtaPlusMC = TLatex(); 
    TextEtaPlusMC.SetTextFont(42);     
    TextEtaPlusMC.SetNDC();     
    TextEtaPlusMC.SetTextSize(0.02);
    TextEtaPlusMC.DrawLatex(0.7,0.86,"#scale[1.4]{i"+EtaPlusBin+" (MC LO)}");
    TextEtaPlusMC.DrawLatex(0.7,0.82,EntriesEtaPlusMC);
    TextEtaPlusMC.DrawLatex(0.7,0.79,MeanEtaPlusMC);
    TextEtaPlusMC.DrawLatex(0.7,0.76,SigmaEtaPlusMC);
    TextEtaPlusMC.DrawLatex(0.7,0.73,Chi2EtaPlusMC);
    TextEtaPlusMC.DrawLatex(0.7,0.70,NDOFEtaPlusMC);
    hEtaPlusMC->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hEtaPlusMC->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaPlusNameMC = TString::Format( figdir + "Eta/EtaPlus%i_mc.png", i);
    canvas->Print(EtaPlusNameMC);
    canvas->Clear();
		
    TH1F *hEtaPlusData = (TH1F*)fData->Get(EtaPlusNum);
    hEtaPlusData->Draw();
    funcGaus->SetRange(hEtaPlusData->GetMaximumBin()+5,hEtaPlusData->GetMaximumBin()+35);
    TFitResultPtr FitResultEtaPlusData = hEtaPlusData->Fit("fitGaus","RSQ");
    double dataPlus = funcGaus->GetParameter(1);
    double dataPlusErr = funcGaus->GetParError(1);
    double dataWidthPlus = funcGaus->GetParameter(2);
    double dataWidthPlusErr = funcGaus->GetParError(2);
    TString EntriesEtaPlusData = TString::Format("Entries: %.0f", hEtaPlusData->GetEntries());
    TString MeanEtaPlusData = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaEtaPlusData = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2EtaPlusData = TString::Format("#chi^{2} = %.2f", FitResultEtaPlusData->Chi2());
    TString NDOFEtaPlusData = TString::Format("ndf = %.0u",FitResultEtaPlusData->Ndf());
    TLatex TextEtaPlusData = TLatex();
    TextEtaPlusData.SetTextFont(42);     
    TextEtaPlusData.SetNDC();     
    TextEtaPlusData.SetTextSize(0.02);
    TextEtaPlusData.DrawLatex(0.7,0.86,"#scale[1.4]{i"+EtaPlusBin+" ("+year+")}");
    TextEtaPlusData.DrawLatex(0.7,0.82,EntriesEtaPlusData);
    TextEtaPlusData.DrawLatex(0.7,0.79,MeanEtaPlusData);
    TextEtaPlusData.DrawLatex(0.7,0.76,SigmaEtaPlusData);
    TextEtaPlusData.DrawLatex(0.7,0.73,Chi2EtaPlusData);
    TextEtaPlusData.DrawLatex(0.7,0.70,NDOFEtaPlusData);
    hEtaPlusData->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hEtaPlusData->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaPlusNameData = TString::Format( figdir + "Eta/EtaPlus%i_data.png", i);
    canvas->Print(EtaPlusNameData);
    canvas->Clear();
		
    TString EtaMinusNum = TString::Format("etaMinus%i", i);
    TString EtaMinusBin = TString::Format("#eta%i (HF-)", i);
				
    TH1F *hEtaMinusMC = (TH1F*)fMC->Get(EtaMinusNum);
    hEtaMinusMC->Draw();
    funcGaus->SetRange(hEtaMinusMC->GetMaximumBin()+5,hEtaMinusMC->GetMaximumBin()+35);
    TFitResultPtr FitResultEtaMinusMC = hEtaMinusMC->Fit("fitGaus","RSQ");
    double mcMinus = funcGaus->GetParameter(1);
    double mcMinusErr = funcGaus->GetParError(1);
    double mcWidthMinus = funcGaus->GetParameter(2);
    double mcWidthMinusErr = funcGaus->GetParError(2);
    TString EntriesEtaMinusMC = TString::Format("Entries: %.0f", hEtaMinusMC->GetEntries());
    TString MeanEtaMinusMC = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaEtaMinusMC = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2EtaMinusMC = TString::Format("#chi^{2} = %.2f", FitResultEtaMinusMC->Chi2());
    TString NDOFEtaMinusMC = TString::Format("ndf = %.0u",FitResultEtaMinusMC->Ndf());
    TLatex TextEtaMinusMC = TLatex(); 
    TextEtaMinusMC.SetTextFont(42);     
    TextEtaMinusMC.SetNDC();     
    TextEtaMinusMC.SetTextSize(0.02);
    TextEtaMinusMC.DrawLatex(0.7,0.86,"#scale[1.4]{i"+EtaMinusBin+" (MC LO)}");
    TextEtaMinusMC.DrawLatex(0.7,0.82,EntriesEtaMinusMC);
    TextEtaMinusMC.DrawLatex(0.7,0.79,MeanEtaMinusMC);
    TextEtaMinusMC.DrawLatex(0.7,0.76,SigmaEtaMinusMC);
    TextEtaMinusMC.DrawLatex(0.7,0.73,Chi2EtaMinusMC);
    TextEtaMinusMC.DrawLatex(0.7,0.70,NDOFEtaMinusMC);
    hEtaMinusMC->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hEtaMinusMC->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaMinusNameMC = TString::Format( figdir + "Eta/EtaMinus%i_mc.png", i);
    canvas->Print(EtaMinusNameMC);
    canvas->Clear();
		
    TH1F *hEtaMinusData = (TH1F*)fData->Get(EtaMinusNum);
    hEtaMinusData->Draw();
    funcGaus->SetRange(hEtaMinusData->GetMaximumBin()+5,hEtaMinusData->GetMaximumBin()+35);
    TFitResultPtr FitResultEtaMinusData = hEtaMinusData->Fit("fitGaus","RSQ");
    double dataMinus = funcGaus->GetParameter(1);
    double dataMinusErr = funcGaus->GetParError(1);
    double dataWidthMinus = funcGaus->GetParameter(2);
    double dataWidthMinusErr = funcGaus->GetParError(2);
    TString EntriesEtaMinusData = TString::Format("Entries: %.0f", hEtaMinusData->GetEntries());
    TString MeanEtaMinusData = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaEtaMinusData = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2EtaMinusData = TString::Format("#chi^{2} = %.2f", FitResultEtaMinusData->Chi2());
    TString NDOFEtaMinusData = TString::Format("ndf = %.0u",FitResultEtaMinusData->Ndf());
    TLatex TextEtaMinusData = TLatex(); 
    TextEtaMinusData.SetTextFont(42);     
    TextEtaMinusData.SetNDC();     
    TextEtaMinusData.SetTextSize(0.02);
    TextEtaMinusData.DrawLatex(0.7,0.86,"#scale[1.4]{i"+EtaMinusBin+" ("+year+")}");
    TextEtaMinusData.DrawLatex(0.7,0.82,EntriesEtaMinusData);
    TextEtaMinusData.DrawLatex(0.7,0.79,MeanEtaMinusData);
    TextEtaMinusData.DrawLatex(0.7,0.76,SigmaEtaMinusData);
    TextEtaMinusData.DrawLatex(0.7,0.73,Chi2EtaMinusData);
    TextEtaMinusData.DrawLatex(0.7,0.70,NDOFEtaMinusData);
    hEtaMinusData->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hEtaMinusData->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaMinusNameData = TString::Format( figdir + "Eta/EtaMinus%i_data.png", i);
    canvas->Print(EtaMinusNameData);
    canvas->Clear();
		
    hEtaMCAll->SetBinContent(i-29, (mcPlus+mcMinus)*0.5);
		
    hEtaPlusDataAll->SetBinContent(i-29, dataPlus);
    hEtaPlusDataAll->SetBinError(i-29, dataPlusErr);
    hEtaMinusDataAll->SetBinContent(i-29, dataMinus);
    hEtaMinusDataAll->SetBinError(i-29, dataMinusErr);
    
    hEtaWidthMCAll->SetBinContent(i-29, (mcWidthPlus+mcWidthMinus)*0.5);
    hEtaWidthDataAll->SetBinContent(i-29, (dataWidthPlus+dataWidthMinus)*0.5);
    hEtaWidthDataAll->SetBinError(i-29, (dataWidthPlusErr+dataWidthMinusErr)*0.5);
    
    canvas->SetLogy(0);
  } // end eta loop
  // std::cout << "EXITING" << std::endl;
  // return;
	
  TF1 *fEta = new TF1("fEta","x",2.964,4.714);
  TGaxis *axisEtaRMS = new TGaxis(29.5,30,39.5,30,"fEta",510,"-");
  axisEtaRMS->SetLabelFont(42);
  axisEtaRMS->SetLabelSize(0.035);
  axisEtaRMS->SetTitleSize(0.035);
  axisEtaRMS->SetLabelOffset(0.0025);
  axisEtaRMS->SetTitle("|#eta|");
	
  hEtaMCAll->SetLineWidth(2);
  hEtaMCAll->SetLineStyle(1);
  hEtaMCAll->SetLineColor(kBlack);
	
  hEtaPlusDataAll->SetMarkerStyle(20);
  hEtaPlusDataAll->SetMarkerSize(1);
  hEtaPlusDataAll->SetMarkerColor(kRed);
  hEtaPlusDataAll->SetLineColor(kRed);
  hEtaPlusDataAll->Draw();
  hEtaPlusDataAll->GetYaxis()->SetRangeUser(50,100);
	
  hEtaMinusDataAll->SetMarkerStyle(21);
  hEtaMinusDataAll->SetMarkerSize(1);
  hEtaMinusDataAll->SetMarkerColor(kBlue);
  hEtaMinusDataAll->SetLineColor(kBlue);
  hEtaMinusDataAll->Draw();
  hEtaMinusDataAll->GetYaxis()->SetRangeUser(50,100);
	
  THStack *EtaStack = new THStack();
  EtaStack->Add(hEtaPlusDataAll);
  EtaStack->Add(hEtaMinusDataAll);
  EtaStack->Draw("nostackP9E1");
  EtaStack->GetXaxis()->SetTitle("i#eta");
  EtaStack->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
  EtaStack->GetYaxis()->SetTitleOffset(1.54);
  TGaxis *axisEta = new TGaxis(29.5,100,39.5,100,"fEta",510,"-");
  axisEta->SetLabelFont(42);
  axisEta->SetLabelSize(0.035);
  axisEta->SetTitleSize(0.05);
  axisEta->SetLabelOffset(0.0025);
  axisEta->SetTitle("|#eta|");
  axisEta->Draw();
  EtaStack->SetMinimum(50);
  EtaStack->SetMaximum(100);
  hEtaMCAll->Draw("LSAME");
  hEtaMCAll->GetYaxis()->SetRangeUser(50,100);
  //TLegend* legendEta = new TLegend(0.63,0.65,0.83,0.85,"","NDC");
  TLegend* legendEta = new TLegend(0.63,0.15,0.83,0.30,"","NDC");
  legendEta->AddEntry(hEtaMCAll, "MC LO", "l");
  legendEta->AddEntry(hEtaPlusDataAll, ""+year+" HF+", "ep");
  legendEta->AddEntry(hEtaMinusDataAll, ""+year+" HF-", "ep");
  legendEta->SetBorderSize(0);
  legendEta->Draw();
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "EtaFit.png");
  canvas->SaveAs( figdir + "EtaFit.C");
  canvas->Clear();

  // Ratio EtaFit
  TH1F* hEtaPRatio = (TH1F*)hEtaMCAll->Clone("pratio");
  hEtaPRatio->SetMarkerStyle(20);
  hEtaPRatio->SetMarkerSize(1);
  hEtaPRatio->SetMarkerColor(kRed);
  hEtaPRatio->SetLineColor(kRed);
  hEtaPRatio->Divide( hEtaPlusDataAll);
  hEtaPRatio->SetStats(0);
  hEtaPRatio->Draw();

  // Print out the ratios for Raddam.C
  float etabin = 0;
  float binval = 0;
  std::cout << ">>> Eta PLUS Ratios " << std::endl;
  for (unsigned int i = 0; i < hEtaPRatio->GetNbinsX(); ++i) {
    etabin = hEtaPRatio->GetXaxis()->GetBinCenter(i);
    binval = hEtaPRatio->GetBinContent(i);
    std::cout << "{" << etabin << ", " << binval << "}," << std::endl;
  }
  
  TH1F* hEtaMRatio = (TH1F*)hEtaMCAll->Clone("mratio");
  hEtaMRatio->SetMarkerStyle(20);
  hEtaMRatio->SetMarkerSize(1);
  hEtaMRatio->SetMarkerColor(kBlue);
  hEtaMRatio->SetLineColor(kBlue);
  hEtaMRatio->Divide( hEtaMinusDataAll);

  std::cout << ">>> Eta MINUS Ratios " << std::endl;
  for (unsigned int i = 0; i < hEtaMRatio->GetNbinsX(); ++i) {
    etabin = hEtaMRatio->GetXaxis()->GetBinCenter(i);
    binval = hEtaMRatio->GetBinContent(i);
    std::cout << "{-" << etabin << ", " << binval << "}," << std::endl;
  }

  THStack *EtaRatioStack = new THStack();
  EtaRatioStack->Add(hEtaPRatio);
  EtaRatioStack->Add(hEtaMRatio);
  EtaRatioStack->Draw("nostackP9E1");  
  EtaRatioStack->GetXaxis()->SetTitle("i#eta");
  EtaRatioStack->GetYaxis()->SetTitle("MC / Data");
  EtaRatioStack->GetYaxis()->SetTitleOffset(1.54);
  TGaxis *axisEtaRatio = new TGaxis(29.5,1.6,39.5,1.6,"fEta",510,"-");
  axisEtaRatio->SetLabelFont(42);
  axisEtaRatio->SetLabelSize(0.035);
  axisEtaRatio->SetTitleSize(0.05);
  axisEtaRatio->SetLabelOffset(0.0025);
  axisEtaRatio->SetTitle("|#eta|");
  axisEtaRatio->Draw();
  EtaRatioStack->SetMinimum(0);
  EtaRatioStack->SetMaximum(1.6);
  hEtaMRatio->Draw("SAME P9E1");
  hEtaMRatio->GetYaxis()->SetRangeUser(0,1.6);
  TLegend* legendEtaRatio = new TLegend(0.2,0.2,0.5,0.3,"","NDC");
  legendEtaRatio->AddEntry(hEtaPRatio, ""+year+" HF+ Ratio", "ep");
  legendEtaRatio->AddEntry(hEtaMRatio, ""+year+" HF- Ratio", "ep");
  legendEtaRatio->SetBorderSize(0);
  legendEtaRatio->Draw();
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "EtaFitRatio.png");
  canvas->SaveAs( figdir + "EtaFitRatio.C");
  canvas->Clear();

  hEtaWidthMCAll->SetLineWidth(2);
  hEtaWidthMCAll->SetLineStyle(1);
  hEtaWidthMCAll->SetLineColor(kBlack);
	
  hEtaWidthDataAll->SetMarkerStyle(20);
  hEtaWidthDataAll->SetMarkerSize(1);
  hEtaWidthDataAll->SetMarkerColor(kRed);
  hEtaWidthDataAll->SetLineColor(kRed);
  hEtaWidthDataAll->Draw();
  hEtaWidthDataAll->GetYaxis()->SetRangeUser(0,15);
	
  THStack *EtaWidthStack = new THStack();
  EtaWidthStack->Add(hEtaWidthDataAll);
  EtaWidthStack->Draw("nostackP9E1");
  EtaWidthStack->GetXaxis()->SetTitle("i#eta");
  EtaWidthStack->GetYaxis()->SetTitle("Width #sigma of M_{e, hf}^{fit} (GeV)");
  EtaWidthStack->GetYaxis()->SetTitleOffset(1.54);
  TGaxis *axisEtaWidth = new TGaxis(29.5,20,39.5,20,"fEta",510,"-");
  axisEtaWidth->SetLabelFont(42);
  axisEtaWidth->SetLabelSize(0.035);
  axisEtaWidth->SetTitleSize(0.05);
  axisEtaWidth->SetLabelOffset(0.0025);
  axisEtaWidth->SetTitle("|#eta|");
  axisEtaWidth->Draw();
  EtaWidthStack->SetMinimum(0);
  EtaWidthStack->SetMaximum(20);
  hEtaWidthMCAll->Draw("LSAME");
  hEtaWidthMCAll->GetYaxis()->SetRangeUser(0,20);
  //TLegend* legendEtaWidth = new TLegend(0.63,0.65,0.83,0.85,"","NDC");
  TLegend* legendEtaWidth = new TLegend(0.23,0.65,0.43,0.85,"","NDC");
  legendEtaWidth->AddEntry(hEtaWidthMCAll, "MC LO", "l");
  legendEtaWidth->AddEntry(hEtaWidthDataAll, ""+year+" HF", "ep");
  legendEtaWidth->SetBorderSize(0);
  legendEtaWidth->Draw();
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "EtaWidthFit.png");
  canvas->Clear();
	
  // Phi Loop
  TH1F *hPhiMCAll = new TH1F("hPhiMCAll", "", 71, 0.5, 71.5);
  TH1F *hPhiDataAll = new TH1F("hPhiDataAll", "", 71, 0.5, 71.5);
  for(int i = 1; i <= 71; i+=2) {
    TString PhiNum = TString::Format("phi%i", i);
    TString PhiBin = TString::Format("#phi%i", i);
    canvas->SetLogy(0);
				
    TH1F *hPhiMC = (TH1F*)fMC->Get(PhiNum);
    funcGaus->SetRange(hPhiMC->GetMaximumBin()+5,hPhiMC->GetMaximumBin()+35);
    TFitResultPtr FitResultPhiMC = hPhiMC->Fit("fitGaus","RSQ");		
    hPhiMC->Draw();
    hPhiMCAll->SetBinContent(i, funcGaus->GetParameter(1));
    hPhiMCAll->SetBinError(i, funcGaus->GetParError(1));
    TString EntriesPhiMC = TString::Format("Entries: %.0f", hPhiMC->GetEntries());
    TString MeanPhiMC = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaPhiMC = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2PhiMC = TString::Format("#chi^{2} = %.2f", FitResultPhiMC->Chi2());
    TString NDOFPhiMC = TString::Format("ndf = %.0u",FitResultPhiMC->Ndf());
    TLatex TextPhiMC = TLatex(); 
    TextPhiMC.SetTextFont(42);     
    TextPhiMC.SetNDC();     
    TextPhiMC.SetTextSize(0.02);
    TextPhiMC.DrawLatex(0.7,0.86,"#scale[1.4]{i"+PhiBin+" (MC LO)}");
    TextPhiMC.DrawLatex(0.7,0.82,EntriesPhiMC);
    TextPhiMC.DrawLatex(0.7,0.79,MeanPhiMC);
    TextPhiMC.DrawLatex(0.7,0.76,SigmaPhiMC);
    TextPhiMC.DrawLatex(0.7,0.73,Chi2PhiMC);
    TextPhiMC.DrawLatex(0.7,0.70,NDOFPhiMC);
    hPhiMC->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hPhiMC->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString PhiNameMC = TString::Format( figdir + "Phi/Phi%i_mc.png", i);
    canvas->Print(PhiNameMC);
    canvas->Clear();
		
    TH1F *hPhiData = (TH1F*)fData->Get(PhiNum);
    funcGaus->SetRange(hPhiData->GetMaximumBin()+5,hPhiData->GetMaximumBin()+35);
    TFitResultPtr FitResultPhiData = hPhiData->Fit("fitGaus","RSQ");		
    hPhiData->Draw();
    hPhiDataAll->SetBinContent(i, funcGaus->GetParameter(1));
    hPhiDataAll->SetBinError(i, funcGaus->GetParError(1));
    TString EntriesPhiData = TString::Format("Entries: %.0f", hPhiData->GetEntries());
    TString MeanPhiData = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaPhiData = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2PhiData = TString::Format("#chi^{2} = %.2f", FitResultPhiData->Chi2());
    TString NDOFPhiData = TString::Format("ndf = %.0u",FitResultPhiData->Ndf());
    TLatex TextPhiData = TLatex(); 
    TextPhiData.SetTextFont(42);     
    TextPhiData.SetNDC();     
    TextPhiData.SetTextSize(0.02);
    TextPhiData.DrawLatex(0.7,0.86,"#scale[1.4]{i"+PhiBin+" ("+year+")}");
    TextPhiData.DrawLatex(0.7,0.82,EntriesPhiData);
    TextPhiData.DrawLatex(0.7,0.79,MeanPhiData);
    TextPhiData.DrawLatex(0.7,0.76,SigmaPhiData);
    TextPhiData.DrawLatex(0.7,0.73,Chi2PhiData);
    TextPhiData.DrawLatex(0.7,0.70,NDOFPhiData);
    hPhiData->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hPhiData->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString PhiNameData = TString::Format( figdir + "Phi/Phi%i_data.png", i);
    canvas->Print(PhiNameData);
    canvas->Clear();
		
    canvas->SetLogy(0);
  } // end phi loop
	
  hPhiMCAll->SetMarkerStyle(20);
  hPhiMCAll->SetMarkerSize(0.75);
  hPhiMCAll->SetMarkerColor(kBlue);
  hPhiMCAll->SetLineColor(kBlue);
  hPhiMCAll->Draw();
  hPhiMCAll->GetYaxis()->SetRangeUser(50,100);
	
  hPhiDataAll->SetMarkerStyle(21);
  hPhiDataAll->SetMarkerSize(0.75);
  hPhiDataAll->SetMarkerColor(kRed);
  hPhiDataAll->SetLineColor(kRed);
  hPhiDataAll->Draw();
  hPhiDataAll->GetYaxis()->SetRangeUser(50,100);
	
  THStack *PhiStack = new THStack();
  PhiStack->Add(hPhiMCAll);
  PhiStack->Add(hPhiDataAll);
  PhiStack->Draw("nostackP9E1");
  PhiStack->GetXaxis()->SetTitle("i#phi");
  PhiStack->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
  PhiStack->SetMinimum(60);
  PhiStack->SetMaximum(90);
  TLegend* legendPhi = new TLegend(0.2,0.2,0.35,0.3,"","NDC");
  legendPhi->AddEntry(hPhiMCAll, "MC LO", "ep");
  legendPhi->AddEntry(hPhiDataAll, year, "ep");
  legendPhi->SetLineColor(kWhite);
  legendPhi->SetBorderSize(0);
  legendPhi->Draw();
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "PhiFit.png");
  canvas->Clear();
	
  //PU
  TH1F *hnVtxMC = (TH1F*)fMC->Get("h_nvtx");
  hnVtxMC->Draw();
  hnVtxMC->GetYaxis()->SetRangeUser(0,1.1*hnVtxMC->GetBinContent(hnVtxMC->GetMaximumBin()));
  canvas->Print( figdir + "nvtx_mc.png");
  canvas->Clear();
	
  TH1F *hnVtxData = (TH1F*)fData->Get("h_nvtx");
  hnVtxData->Draw();
  hnVtxData->GetYaxis()->SetRangeUser(0,1.1*hnVtxData->GetBinContent(hnVtxData->GetMaximumBin()));
  canvas->Print( figdir + "nvtx_data.png");
  canvas->Clear();
	
  TF1 *funcLinData = new TF1("fitLinData","pol1",0,54);
  TF1 *funcLinMC = new TF1("fitLinMC","pol1",0,54);
  funcLinMC->SetLineColor(kBlue);
  funcLinData->SetLineWidth(2);
  funcLinMC->SetLineWidth(2);
  TH1F *hPUmcFit = new TH1F("hPUmcFit", "", 9, 0, 54);
  TH1F *hPUdataFit = new TH1F("hPUdataFit", "", 9, 0, 54);
  const TString PUbin[] = {"nVtx 1-6","nVtx 6-12","nVtx 12-18","nVtx 18-24","nVtx 24-30","nVtx 30-36","nVtx 36-42","nVtx 42-48","nVtx 48+"};
  for(int i = 1; i <= 9; ++i) {
    TString PUnum = TString::Format("nVtx%i", i);
    canvas->SetLogy(0);
		
    TH1F *hPUmc = (TH1F*)fMC->Get(PUnum);
    if (hPUmc->GetEntries() > 0) {
      funcGaus->SetRange(hPUmc->GetMaximumBin()+5,hPUmc->GetMaximumBin()+35);
      TFitResultPtr FitResultPUmc = hPUmc->Fit("fitGaus","RSQ");		
      hPUmcFit->SetBinContent(i, funcGaus->GetParameter(1));
      hPUmcFit->SetBinError(i, funcGaus->GetParError(1));
      TString EntriesPUmc = TString::Format("Entries: %.0f", hPUmc->GetEntries());
      TString MeanPUmc = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
      TString SigmaPUmc = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
      TString Chi2PUmc = TString::Format("#chi^{2} = %.2f", FitResultPUmc->Chi2());
      TString NDOFPUmc = TString::Format("ndf = %.0u",FitResultPUmc->Ndf());
      TLatex TextPUmc = TLatex(); 
      TextPUmc.SetTextFont(42);     
      TextPUmc.SetNDC();     
      TextPUmc.SetTextSize(0.02);
      TextPUmc.DrawLatex(0.7,0.86,"#scale[1.4]{"+PUbin[i-1]+" (MC LO)}");
      TextPUmc.DrawLatex(0.7,0.82,EntriesPUmc);
      TextPUmc.DrawLatex(0.7,0.79,MeanPUmc);
      TextPUmc.DrawLatex(0.7,0.76,SigmaPUmc);
      TextPUmc.DrawLatex(0.7,0.73,Chi2PUmc);
      TextPUmc.DrawLatex(0.7,0.70,NDOFPUmc);
      hPUmc->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
      hPUmc->GetYaxis()->SetTitle("Events");
      CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
      TString PUmcName = TString::Format( figdir + "PU/PU%i_mc.png", i);
      canvas->Print(PUmcName);
      canvas->Clear();}
		
    TH1F *hPUdata = (TH1F*)fData->Get(PUnum);
    if (hPUdata->GetEntries() > 0) {
      funcGaus->SetRange(hPUdata->GetMaximumBin()+5,hPUdata->GetMaximumBin()+35);
      TFitResultPtr FitResultPUdata = hPUdata->Fit("fitGaus","RSQ");		
      hPUdataFit->SetBinContent(i, funcGaus->GetParameter(1));
      hPUdataFit->SetBinError(i, funcGaus->GetParError(1));
      TString EntriesPUdata = TString::Format("Entries: %.0f", hPUdata->GetEntries());
      TString MeanPUdata = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
      TString SigmaPUdata = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
      TString Chi2PUdata = TString::Format("#chi^{2} = %.2f", FitResultPUdata->Chi2());
      TString NDOFPUdata = TString::Format("ndf = %.0u",FitResultPUdata->Ndf());
      TLatex TextPUdata = TLatex(); 
      TextPUdata.SetTextFont(42);     
      TextPUdata.SetNDC();     
      TextPUdata.SetTextSize(0.02);
      TextPUdata.DrawLatex(0.7,0.86,"#scale[1.4]{"+PUbin[i-1]+" ("+year+")}");
      TextPUdata.DrawLatex(0.7,0.82,EntriesPUdata);
      TextPUdata.DrawLatex(0.7,0.79,MeanPUdata);
      TextPUdata.DrawLatex(0.7,0.76,SigmaPUdata);
      TextPUdata.DrawLatex(0.7,0.73,Chi2PUdata);
      TextPUdata.DrawLatex(0.7,0.70,NDOFPUdata);
      hPUdata->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
      hPUdata->GetYaxis()->SetTitle("Events");
      CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
      TString PUdataName = TString::Format( figdir + "PU/PU%i_data.png", i);
      canvas->Print(PUdataName);
      canvas->Clear();}
		
    canvas->SetLogy(0);
  } // end PU loop
	
  hPUmcFit->SetMarkerStyle(21);
  hPUmcFit->SetMarkerSize(1);
  hPUmcFit->SetMarkerColor(kBlue);
  hPUmcFit->SetLineColor(kBlue);
  hPUmcFit->Draw("E1");
  hPUmcFit->GetYaxis()->SetRangeUser(50,100);
  hPUmcFit->GetXaxis()->SetTitle("nVtx");
  hPUmcFit->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
  hPUmcFit->Fit("fitLinMC","RQ");
  TString LinFitMC = TString::Format("MC LO: %.3f + %.3f #times nVtx", funcLinMC->GetParameter(0), funcLinMC->GetParameter(1));
  if (funcLinMC->GetParameter(1) < 0) LinFitMC = TString::Format("MC LO: %.3f - %.3f #times nVtx", funcLinMC->GetParameter(0), (-1)*funcLinMC->GetParameter(1));
	
  hPUdataFit->SetMarkerStyle(21);
  hPUdataFit->SetMarkerSize(1);
  hPUdataFit->SetMarkerColor(kRed);
  hPUdataFit->SetLineColor(kRed);
  hPUdataFit->Draw("E1");
  hPUdataFit->GetYaxis()->SetRangeUser(50,100);
  hPUdataFit->GetXaxis()->SetTitle("nVtx");
  hPUdataFit->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
  hPUdataFit->Fit("fitLinData","RQ");
  TString LinFitData = TString::Format(year+": %.3f + %.3f #times nVtx", funcLinData->GetParameter(0), funcLinData->GetParameter(1));
  if (funcLinData->GetParameter(1) < 0) LinFitData = TString::Format(year+": %.3f - %.3f #times nVtx", funcLinData->GetParameter(0), (-1)*funcLinData->GetParameter(1));
	
  THStack *PUStack = new THStack("PUstack", "");
  PUStack->Add(hPUmcFit);
  PUStack->Add(hPUdataFit);
  PUStack->Draw("nostackP9E1");
  PUStack->GetXaxis()->SetTitle("nVtx");
  PUStack->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
  PUStack->SetMinimum(50);
  PUStack->SetMaximum(100);
  TLegend* legendPU = new TLegend(0.4,0.2,0.85,0.5,"Pile-Up","NDC");
  legendPU->AddEntry(hPUmcFit, LinFitMC, "ep");
  legendPU->AddEntry(hPUdataFit, LinFitData, "ep");
  legendPU->SetBorderSize(0);
  legendPU->Draw();
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  canvas->Print( figdir + "PUFit.png");
  canvas->SaveAs( figdir + "PUFit.C");
  canvas->Clear();

  // Memory leaks on 'hEtaPhiFitDataAll' and 'hEtaPhiFitMCAll'
  TH1F *hEtaPhiFitDataAll = new TH1F("hEtaPhiFitDataAll", "", 71, 0.5, 71.5);
  TH1F *hEtaPhiFitMCAll = new TH1F("hEtaPhiFitMCAll", "", 71, 0.5, 71.5);
  TString EtaRange[12] = {"i#eta30","i#eta31","i#eta32","i#eta33","i#eta34","i#eta35","i#eta36","i#eta37","i#eta38","i#eta39","i#eta40","i#eta41"};
  for (int e = 30; e <= 41; ++e) {
    int count = 0;
    for(int i = 1; i <= 71; i+=2) {
      
      if(e >= 40) i+=2;
      
      TString EtaPhiFitNum = TString::Format("eta%iphi%i", e, i);
      TH1F *hEtaPhiFitData = (TH1F*)fData->Get(EtaPhiFitNum);
      funcGaus->SetRange(hEtaPhiFitData->GetMaximumBin()+10,hEtaPhiFitData->GetMaximumBin()+30);
      hEtaPhiFitData->Fit("fitGaus","RSQ");
      hEtaPhiFitData->Draw();
      hEtaPhiFitDataAll->SetBinContent(i, funcGaus->GetParameter(1));
      hEtaPhiFitDataAll->SetBinError(i, funcGaus->GetParError(1));
      canvas->Clear();
				
      TH1F *hEtaPhiFitMC = (TH1F*)fMC->Get(EtaPhiFitNum);
      funcGaus->SetRange(hEtaPhiFitMC->GetMaximumBin()+10,hEtaPhiFitMC->GetMaximumBin()+30);
      hEtaPhiFitMC->Fit("fitGaus","RSQ");
      hEtaPhiFitMC->Draw();
      hEtaPhiFitMCAll->SetBinContent(i, funcGaus->GetParameter(1));
      hEtaPhiFitMCAll->SetBinError(i, funcGaus->GetParError(1));
      canvas->Clear();
			
      count++;
    }
    hEtaPhiFitDataAll->SetMarkerStyle(21);
    hEtaPhiFitDataAll->SetMarkerSize(0.75);
    hEtaPhiFitDataAll->SetMarkerColor(kRed);
    hEtaPhiFitDataAll->SetLineColor(kRed);
    hEtaPhiFitDataAll->Draw();
    hEtaPhiFitDataAll->GetYaxis()->SetRangeUser(50,100);

    hEtaPhiFitMCAll->SetMarkerStyle(21);
    hEtaPhiFitMCAll->SetMarkerSize(0.75);
    hEtaPhiFitMCAll->SetMarkerColor(kBlue);
    hEtaPhiFitMCAll->SetLineColor(kBlue);
    hEtaPhiFitMCAll->Draw();
    hEtaPhiFitMCAll->GetYaxis()->SetRangeUser(50,100);
		
    THStack *EtaPhiFitStack = new THStack();
    EtaPhiFitStack->Add(hEtaPhiFitMCAll);
    EtaPhiFitStack->Add(hEtaPhiFitDataAll);
    EtaPhiFitStack->Draw("nostackP9E1");
    EtaPhiFitStack->GetXaxis()->SetTitle("i#phi");
    EtaPhiFitStack->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
    EtaPhiFitStack->SetMinimum(50);
    EtaPhiFitStack->SetMaximum(100);
    TLegend* legendEtaPhiFit = new TLegend(0.25,0.75,0.4,0.85,EtaRange[e-30],"NDC");
    legendEtaPhiFit->AddEntry(hEtaPhiFitDataAll, year, "ep");
    legendEtaPhiFit->AddEntry(hEtaPhiFitMCAll, "MC LO", "ep");
    legendEtaPhiFit->SetBorderSize(0);
    legendEtaPhiFit->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaPhiFitName = TString::Format( figdir + "EtaPhiFit/Eta%iPhiFit.png", e);
    canvas->Print(EtaPhiFitName);
    canvas->Clear();
        
    TString EtaPUNum = TString::Format("eta%invtx", e);
    TH1F *hEtaPUData = (TH1F*)fData->Get(EtaPUNum);
    TH1F *hEtaPUMC = (TH1F*)fMC->Get(EtaPUNum);
    hEtaPUData->SetMarkerStyle(21);
    hEtaPUData->SetMarkerSize(0.5);
    hEtaPUData->SetMarkerColor(kRed);
    hEtaPUData->SetLineColor(kRed);
    hEtaPUData->Scale(1/hEtaPUData->GetEntries());
    hEtaPUMC->SetMarkerStyle(21);
    hEtaPUMC->SetMarkerSize(0.5);
    hEtaPUMC->SetMarkerColor(kBlue);
    hEtaPUMC->SetLineColor(kBlue);
    hEtaPUMC->Scale(1/hEtaPUMC->GetEntries());
    THStack *EtaPUStack = new THStack();
    EtaPUStack->Add(hEtaPUMC);
    EtaPUStack->Add(hEtaPUData);
    EtaPUStack->Draw("nostack");
    EtaPUStack->GetXaxis()->SetTitle("nVtx");
    EtaPUStack->GetYaxis()->SetTitle("Norm. events");
    EtaPUStack->SetMinimum(0);
    double MC_maxPU = 1.25*hEtaPUMC->GetBinContent(hEtaPUMC->GetMaximumBin());
    double Data_maxPU = 1.25*hEtaPUData->GetBinContent(hEtaPUData->GetMaximumBin());
    if (MC_maxPU > Data_maxPU) EtaPUStack->SetMaximum(MC_maxPU);
    if (MC_maxPU < Data_maxPU) EtaPUStack->SetMaximum(Data_maxPU);
    TLegend* legendEtaPU = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaPU->AddEntry(hEtaPUData, year, "p");
    legendEtaPU->AddEntry(hEtaPUMC, "MC LO", "p");
    legendEtaPU->SetBorderSize(0);
    legendEtaPU->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaPUFitName = TString::Format( figdir + "EtaBin/Eta%iPU.png", e);
    canvas->Print(EtaPUFitName);
    canvas->Clear();
		
    TString EtaPhiNum = TString::Format("eta%iphi", e);
    TH1F *hEtaPhiData = (TH1F*)fData->Get(EtaPhiNum);
    TH1F *hEtaPhiMC = (TH1F*)fMC->Get(EtaPhiNum);
    hEtaPhiData->SetMarkerStyle(21);
    hEtaPhiData->SetMarkerSize(0.5);
    hEtaPhiData->SetMarkerColor(kRed);
    hEtaPhiData->SetLineColor(kRed);
    hEtaPhiData->Scale(1/hEtaPhiData->GetEntries());
    hEtaPhiMC->SetMarkerStyle(21);
    hEtaPhiMC->SetMarkerSize(0.5);
    hEtaPhiMC->SetMarkerColor(kBlue);
    hEtaPhiMC->SetLineColor(kBlue);
    hEtaPhiMC->Scale(1/hEtaPhiMC->GetEntries());
    THStack *EtaPhiStack = new THStack();
    EtaPhiStack->Add(hEtaPhiMC);
    EtaPhiStack->Add(hEtaPhiData);
    EtaPhiStack->Draw("nostack");
    EtaPhiStack->GetXaxis()->SetTitle("#phi_{HF}");
    EtaPhiStack->GetYaxis()->SetTitle("Norm. events");
    EtaPhiStack->SetMinimum(0);
    double MC_maxPhi = 1.25*hEtaPhiMC->GetBinContent(hEtaPhiMC->GetMaximumBin());
    double Data_maxPhi = 1.25*hEtaPhiData->GetBinContent(hEtaPhiData->GetMaximumBin());
    if (MC_maxPhi > Data_maxPhi) EtaPhiStack->SetMaximum(MC_maxPhi);
    if (MC_maxPhi < Data_maxPhi) EtaPhiStack->SetMaximum(Data_maxPhi);
    TLegend* legendEtaPhi = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaPhi->AddEntry(hEtaPhiData, year, "p");
    legendEtaPhi->AddEntry(hEtaPhiMC, "MC LO", "p");
    legendEtaPhi->SetBorderSize(0);
    legendEtaPhi->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaPhiName = TString::Format( figdir + "EtaBin/Eta%iPhi.png", e);
    canvas->Print(EtaPhiName);
    canvas->Clear();
		
    TString EtaPhiEENum = TString::Format("eta%iphiEE", e);
    TH1F *hEtaPhiEEData = (TH1F*)fData->Get(EtaPhiEENum);
    TH1F *hEtaPhiEEMC = (TH1F*)fMC->Get(EtaPhiEENum);
    hEtaPhiEEData->SetMarkerStyle(21);
    hEtaPhiEEData->SetMarkerSize(0.5);
    hEtaPhiEEData->SetMarkerColor(kRed);
    hEtaPhiEEData->SetLineColor(kRed);
    hEtaPhiEEData->Scale(1/hEtaPhiEEData->GetEntries());
    hEtaPhiEEMC->SetMarkerStyle(21);
    hEtaPhiEEMC->SetMarkerSize(0.5);
    hEtaPhiEEMC->SetMarkerColor(kBlue);
    hEtaPhiEEMC->SetLineColor(kBlue);
    hEtaPhiEEMC->Scale(1/hEtaPhiEEMC->GetEntries());
    THStack *EtaPhiEEStack = new THStack();
    EtaPhiEEStack->Add(hEtaPhiEEMC);
    EtaPhiEEStack->Add(hEtaPhiEEData);
    EtaPhiEEStack->Draw("nostack");
    EtaPhiEEStack->GetXaxis()->SetTitle("#phi_{ECAL}");
    EtaPhiEEStack->GetYaxis()->SetTitle("Norm. events");
    EtaPhiEEStack->SetMinimum(0);
    double MC_maxPhiEE = 1.25*hEtaPhiEEMC->GetBinContent(hEtaPhiEEMC->GetMaximumBin());
    double Data_maxPhiEE = 1.25*hEtaPhiEEData->GetBinContent(hEtaPhiEEData->GetMaximumBin());
    if (MC_maxPhiEE > Data_maxPhiEE) EtaPhiEEStack->SetMaximum(MC_maxPhiEE);
    if (MC_maxPhiEE < Data_maxPhiEE) EtaPhiEEStack->SetMaximum(Data_maxPhiEE);
    TLegend* legendEtaPhiEE = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaPhiEE->AddEntry(hEtaPhiEEData, year, "p");
    legendEtaPhiEE->AddEntry(hEtaPhiEEMC, "MC LO", "p");
    legendEtaPhiEE->SetBorderSize(0);
    legendEtaPhiEE->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaPhiEEFitName = TString::Format( figdir + "EtaBin/Eta%iPhiEE.png", e);
    canvas->Print(EtaPhiEEFitName);
    canvas->Clear();
		
    TString EtaEtaEENum = TString::Format("eta%ietaEE", e);
    TH1F *hEtaEtaEEData = (TH1F*)fData->Get(EtaEtaEENum);
    TH1F *hEtaEtaEEMC = (TH1F*)fMC->Get(EtaEtaEENum);
    hEtaEtaEEData->SetMarkerStyle(21);
    hEtaEtaEEData->SetMarkerSize(0.5);
    hEtaEtaEEData->SetMarkerColor(kRed);
    hEtaEtaEEData->SetLineColor(kRed);
    hEtaEtaEEData->Scale(1/hEtaEtaEEData->GetEntries());
    hEtaEtaEEMC->SetMarkerStyle(21);
    hEtaEtaEEMC->SetMarkerSize(0.5);
    hEtaEtaEEMC->SetMarkerColor(kBlue);
    hEtaEtaEEMC->SetLineColor(kBlue);
    hEtaEtaEEMC->Scale(1/hEtaEtaEEMC->GetEntries());
    THStack *EtaEtaEEStack = new THStack();
    EtaEtaEEStack->Add(hEtaEtaEEMC);
    EtaEtaEEStack->Add(hEtaEtaEEData);
    EtaEtaEEStack->Draw("nostack");
    EtaEtaEEStack->GetXaxis()->SetTitle("#eta_{ECAL}");
    EtaEtaEEStack->GetYaxis()->SetTitle("Norm. events");
    EtaEtaEEStack->SetMinimum(0);
    double MC_maxEtaEE = 1.25*hEtaEtaEEMC->GetBinContent(hEtaEtaEEMC->GetMaximumBin());
    double Data_maxEtaEE = 1.25*hEtaEtaEEData->GetBinContent(hEtaEtaEEData->GetMaximumBin());
    if (MC_maxEtaEE > Data_maxEtaEE) EtaEtaEEStack->SetMaximum(MC_maxEtaEE);
    if (MC_maxEtaEE < Data_maxEtaEE) EtaEtaEEStack->SetMaximum(Data_maxEtaEE);
    TLegend* legendEtaEtaEE = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaEtaEE->AddEntry(hEtaEtaEEData, year, "p");
    legendEtaEtaEE->AddEntry(hEtaEtaEEMC, "MC LO", "p");
    legendEtaEtaEE->SetBorderSize(0);
    legendEtaEtaEE->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaEtaEEFitName = TString::Format( figdir + "EtaBin/Eta%iEtaEE.png", e);
    canvas->Print(EtaEtaEEFitName);
    canvas->Clear();
		
    TString EtaDPhiNum = TString::Format("eta%idphi", e);
    TH1F *hEtaDPhiData = (TH1F*)fData->Get(EtaDPhiNum);
    TH1F *hEtaDPhiMC = (TH1F*)fMC->Get(EtaDPhiNum);
    hEtaDPhiData->SetMarkerStyle(21);
    hEtaDPhiData->SetMarkerSize(0.5);
    hEtaDPhiData->SetMarkerColor(kRed);
    hEtaDPhiData->SetLineColor(kRed);
    hEtaDPhiData->Scale(1/hEtaDPhiData->GetEntries());
    hEtaDPhiMC->SetMarkerStyle(21);
    hEtaDPhiMC->SetMarkerSize(0.5);
    hEtaDPhiMC->SetMarkerColor(kBlue);
    hEtaDPhiMC->SetLineColor(kBlue);
    hEtaDPhiMC->Scale(1/hEtaDPhiMC->GetEntries());
    THStack *EtaDPhiStack = new THStack();
    EtaDPhiStack->Add(hEtaDPhiMC);
    EtaDPhiStack->Add(hEtaDPhiData);
    EtaDPhiStack->Draw("nostack");
    EtaDPhiStack->GetXaxis()->SetTitle("#Delta#phi_{ECAL, HF}");
    EtaDPhiStack->GetYaxis()->SetTitle("Norm. events");
    EtaDPhiStack->SetMinimum(0);
    double MC_maxDPhi = 1.25*hEtaDPhiMC->GetBinContent(hEtaDPhiMC->GetMaximumBin());
    double Data_maxDPhi = 1.25*hEtaDPhiData->GetBinContent(hEtaDPhiData->GetMaximumBin());
    if (MC_maxDPhi > Data_maxDPhi) EtaDPhiStack->SetMaximum(MC_maxDPhi);
    if (MC_maxDPhi < Data_maxDPhi) EtaDPhiStack->SetMaximum(Data_maxDPhi);
    TLegend* legendEtaDPhi = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaDPhi->AddEntry(hEtaDPhiData, year, "p");
    legendEtaDPhi->AddEntry(hEtaDPhiMC, "MC LO", "p");
    legendEtaDPhi->SetBorderSize(0);
    legendEtaDPhi->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaDPhiFitName = TString::Format( figdir + "EtaBin/Eta%iDPhi.png", e);
    canvas->Print(EtaDPhiFitName);
    canvas->Clear();
		
    TString EtaEnNum = TString::Format("eta%ien", e);
    TH1F *hEtaEnData = (TH1F*)fData->Get(EtaEnNum);
    TH1F *hEtaEnMC = (TH1F*)fMC->Get(EtaEnNum);
    hEtaEnData->SetMarkerStyle(21);
    hEtaEnData->SetMarkerSize(0.5);
    hEtaEnData->SetMarkerColor(kRed);
    hEtaEnData->SetLineColor(kRed);
    hEtaEnData->Scale(1/hEtaEnData->GetEntries());
    hEtaEnMC->SetMarkerStyle(21);
    hEtaEnMC->SetMarkerSize(0.5);
    hEtaEnMC->SetMarkerColor(kBlue);
    hEtaEnMC->SetLineColor(kBlue);
    hEtaEnMC->Scale(1/hEtaEnMC->GetEntries());
    THStack *EtaEnStack = new THStack();
    EtaEnStack->Add(hEtaEnMC);
    EtaEnStack->Add(hEtaEnData);
    EtaEnStack->Draw("nostack");
    EtaEnStack->GetXaxis()->SetTitle("E_{T}^{HF} [GeV]");
    EtaEnStack->GetYaxis()->SetTitle("Norm. events");
    EtaEnStack->SetMinimum(0);
    double MC_maxEn = 1.25*hEtaEnMC->GetBinContent(hEtaEnMC->GetMaximumBin());
    double Data_maxEn = 1.25*hEtaEnData->GetBinContent(hEtaEnData->GetMaximumBin());
    if (MC_maxEn > Data_maxEn) EtaEnStack->SetMaximum(MC_maxEn);
    if (MC_maxEn < Data_maxEn) EtaEnStack->SetMaximum(Data_maxEn);
    TLegend* legendEtaEn = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaEn->AddEntry(hEtaEnData, year, "p");
    legendEtaEn->AddEntry(hEtaEnMC, "MC LO", "p");
    legendEtaEn->SetBorderSize(0);
    legendEtaEn->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaEnFitName = TString::Format( figdir + "EtaBin/Eta%iEn.png", e);
    canvas->Print(EtaEnFitName);
    canvas->Clear();
		
    TString EtaEnEENum = TString::Format("eta%ienEE", e);
    TH1F *hEtaEnEEData = (TH1F*)fData->Get(EtaEnEENum);
    TH1F *hEtaEnEEMC = (TH1F*)fMC->Get(EtaEnEENum);
    hEtaEnEEData->SetMarkerStyle(21);
    hEtaEnEEData->SetMarkerSize(0.5);
    hEtaEnEEData->SetMarkerColor(kRed);
    hEtaEnEEData->SetLineColor(kRed);
    hEtaEnEEData->Scale(1/hEtaEnEEData->GetEntries());
    hEtaEnEEMC->SetMarkerStyle(21);
    hEtaEnEEMC->SetMarkerSize(0.5);
    hEtaEnEEMC->SetMarkerColor(kBlue);
    hEtaEnEEMC->SetLineColor(kBlue);
    hEtaEnEEMC->Scale(1/hEtaEnEEMC->GetEntries());
    THStack *EtaEnEEStack = new THStack();
    EtaEnEEStack->Add(hEtaEnEEMC);
    EtaEnEEStack->Add(hEtaEnEEData);
    EtaEnEEStack->Draw("nostack");
    EtaEnEEStack->GetXaxis()->SetTitle("E_{T}^{ECAL} [GeV]");
    EtaEnEEStack->GetYaxis()->SetTitle("Norm. events");
    EtaEnEEStack->SetMinimum(0);
    double MC_maxEnEE = 1.25*hEtaEnEEMC->GetBinContent(hEtaEnEEMC->GetMaximumBin());
    double Data_maxEnEE = 1.25*hEtaEnEEData->GetBinContent(hEtaEnEEData->GetMaximumBin());
    if (MC_maxEnEE > Data_maxEnEE) EtaEnEEStack->SetMaximum(MC_maxEnEE);
    if (MC_maxEnEE < Data_maxEnEE) EtaEnEEStack->SetMaximum(Data_maxEnEE);
    TLegend* legendEtaEnEE = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEtaEnEE->AddEntry(hEtaEnEEData, year, "p");
    legendEtaEnEE->AddEntry(hEtaEnEEMC, "MC LO", "p");
    legendEtaEnEE->SetBorderSize(0);
    legendEtaEnEE->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString EtaEnEEFitName = TString::Format( figdir + "EtaBin/Eta%iEnEE.png", e);
    canvas->Print(EtaEnEEFitName);
    canvas->Clear();
        
    TString Eta_lsRatioNum = TString::Format("eta%ilsRatio", e);
    TH1F *hEta_lsRatioData = (TH1F*)fData->Get(Eta_lsRatioNum);
    TH1F *hEta_lsRatioMC = (TH1F*)fMC->Get(Eta_lsRatioNum);
    hEta_lsRatioData->SetMarkerStyle(21);
    hEta_lsRatioData->SetMarkerSize(0.5);
    hEta_lsRatioData->SetMarkerColor(kRed);
    hEta_lsRatioData->SetLineColor(kRed);
    hEta_lsRatioData->Scale(1/hEta_lsRatioData->GetEntries());
    hEta_lsRatioMC->SetMarkerStyle(21);
    hEta_lsRatioMC->SetMarkerSize(0.5);
    hEta_lsRatioMC->SetMarkerColor(kBlue);
    hEta_lsRatioMC->SetLineColor(kBlue);
    hEta_lsRatioMC->Scale(1/hEta_lsRatioMC->GetEntries());
    THStack *Eta_lsRatioStack = new THStack();
    Eta_lsRatioStack->Add(hEta_lsRatioMC);
    Eta_lsRatioStack->Add(hEta_lsRatioData);
    Eta_lsRatioStack->Draw("nostack");
    Eta_lsRatioStack->GetXaxis()->SetTitle("Long/Short Fiber Energy Ratio");
    Eta_lsRatioStack->GetYaxis()->SetTitle("Norm. events");
    Eta_lsRatioStack->SetMinimum(0);
    double MC_max_lsRatio = 1.25*hEta_lsRatioMC->GetBinContent(hEta_lsRatioMC->GetMaximumBin());
    double Data_max_lsRatio = 1.25*hEta_lsRatioData->GetBinContent(hEta_lsRatioData->GetMaximumBin());
    if (MC_max_lsRatio > Data_max_lsRatio) Eta_lsRatioStack->SetMaximum(MC_max_lsRatio);
    if (MC_max_lsRatio < Data_max_lsRatio) Eta_lsRatioStack->SetMaximum(Data_max_lsRatio);
    TLegend* legendEta_lsRatio = new TLegend(0.475,0.775,0.625,0.875,EtaRange[e-30],"NDC");
    legendEta_lsRatio->AddEntry(hEta_lsRatioData, year, "p");
    legendEta_lsRatio->AddEntry(hEta_lsRatioMC, "MC LO", "p");
    legendEta_lsRatio->SetBorderSize(0);
    legendEta_lsRatio->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString Eta_lsRatioFitName = TString::Format( figdir + "EtaBin/Eta%ilsRatio.png", e);
    canvas->Print(Eta_lsRatioFitName);
    canvas->Clear();

    hEtaPhiFitDataAll->Reset();
    hEtaPhiFitMCAll->Reset();
  } // end etaphi loop
	
  //Run Data
  /*TH1F *hRunData = new TH1F("hRunData", "", 5, 0, 5);
    TString RunName[5] = {"runB","runC","runD","runE","runF"};
    TString RunLabel[5] = {"4.8 fb^{-1}","14.6 fb^{-1}","18.9 fb^{-1}","28.3 fb^{-1}","42.0 fb^{-1}"};
    for(int i = 1; i <= 5; ++i) {
    TH1F *hRun = (TH1F*)fData->Get(RunName[i-1]);
    funcGaus->SetRange(hRun->GetMaximumBin()+5,hRun->GetMaximumBin()+35);
    TFitResultPtr FitResultRunData = hRun->Fit("fitGaus","RSQ");
    hRunData->SetBinContent(i, funcGaus->GetParameter(1));
    hRunData->SetBinError(i, funcGaus->GetParError(1));
    hRunData->GetXaxis()->SetBinLabel(i,RunLabel[i-1]);		
    TString EntriesRunData = TString::Format("Entries: %.0f", hRun->GetEntries());
    TString MeanRunData = TString::Format("#mu = %.3f #pm %.3f", funcGaus->GetParameter(1), funcGaus->GetParError(1));
    TString SigmaRunData = TString::Format("#sigma = %.3f #pm %.3f", funcGaus->GetParameter(2), funcGaus->GetParError(2));
    TString Chi2RunData = TString::Format("#chi^{2} = %.2f", FitResultRunData->Chi2());
    TString NDOFRunData = TString::Format("ndf = %.0u",FitResultRunData->Ndf());
    TLatex TextRunData = TLatex(); 
    TextRunData.SetTextFont(42);     
    TextRunData.SetNDC();     
    TextRunData.SetTextSize(0.02);
    TextRunData.DrawLatex(0.7,0.86,"#scale[1.4]{"+RunName[i-1]+"}");
    TextRunData.DrawLatex(0.7,0.82,EntriesRunData);
    TextRunData.DrawLatex(0.7,0.79,MeanRunData);
    TextRunData.DrawLatex(0.7,0.76,SigmaRunData);
    TextRunData.DrawLatex(0.7,0.73,Chi2RunData);
    TextRunData.DrawLatex(0.7,0.70,NDOFRunData);
    hRunData->GetXaxis()->SetTitle("M_{e, hf} (GeV)");
    hRunData->GetYaxis()->SetTitle("Events");
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    TString RunFile =  figdir + "Run/" + RunName[i-1] + ".png";
    canvas->Print(RunFile);
    canvas->Clear();
    }
    gStyle->SetOptStat(0);
    hRunData->SetMarkerStyle(21);
    hRunData->SetMarkerSize(0.75);
    hRunData->SetMarkerColor(kRed);
    hRunData->SetLineColor(kRed);
    hRunData->Draw("PE");
    hRunData->GetXaxis()->SetTitle("Luminosity");
    hRunData->GetYaxis()->SetTitleOffset(1.54);
    hRunData->GetYaxis()->SetTitle("M_{e, hf}^{fit} (GeV)");
    hRunData->SetMinimum(65);
    hRunData->SetMaximum(85);
    TLegend* legendRun = new TLegend(0.7,0.7,0.85,0.85,"","NDC");
    legendRun->AddEntry(hRunData, year, "ep");
    legendRun->SetBorderSize(0);
    legendRun->Draw();
    CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
    canvas->Print( figdir + "Run.png");
    canvas->Clear();*/

  // std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
  std::cout << "Finished in " << round(std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - start).count()) << " seconds" << std::endl;
  std::cout << "All Done!" << std::endl;
}
