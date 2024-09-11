#include "Raddam.C"

void drawFactors( TH1F* hp, TH1F* hm) {
  TCanvas* factors = new TCanvas("factors");
  hp->SetMarkerStyle(20);
  hp->SetMarkerSize(1);
  hp->SetMarkerColor(kRed);
  hp->SetLineColor(kRed);
  hp->SetStats(0);
  hp->SetTitle("");
  hp->Draw("HIST P");
  hp->GetXaxis()->SetTitle("i#eta");
  hp->GetYaxis()->SetTitle("Raddam Correction");
  hp->GetYaxis()->SetTitleOffset(1.24);
  
  hm->SetMarkerStyle(20);
  hm->SetMarkerSize(1);
  hm->SetMarkerColor(kBlue);
  hm->SetLineColor(kBlue);
  hm->Draw("SAME HIST P");

  TF1 *fEta = new TF1("fEta","x",2.964,4.714);
  TGaxis *axisEta = new TGaxis(29.5,100,39.5,100,"fEta",510,"-");
  axisEta->SetLabelFont(42);
  axisEta->SetLabelSize(0.035);
  axisEta->SetTitleSize(0.05);
  axisEta->SetLabelOffset(0.0025);
  axisEta->SetTitle("|#eta|");
  axisEta->Draw();
  hp->SetMinimum(0);
  hp->SetMaximum(2.5);

  TLegend* legendEta = new TLegend(0.2,0.2,0.6,0.4,"","NDC");
  legendEta->AddEntry(hp, "2022 HF+ Corrections", "ep");
  legendEta->AddEntry(hm, "2022 HF- Corrections", "ep");
  legendEta->SetBorderSize(0);
  legendEta->Draw();

  TLatex CMSlabel = TLatex(); 
  CMSlabel.SetTextFont(42);     
  CMSlabel.SetNDC();     
  CMSlabel.SetTextSize(0.04);
  CMSlabel.DrawLatex(0.128,0.955,"#bf{CMS} #it{Preliminary}");
  factors->Print( "RaddamCorrections.png");
  factors->SaveAs( "RaddamCorrections.C");
}

void factorCalc() {
  TH1F* raddCorrsPlus  = new TH1F("raddcorrsplus" , "Raddam Corrections", 9, 29.5, 38.5);
  TH1F* raddCorrsMinus = new TH1F("raddcorrsminus" , "Raddam Corrections", 9, 29.5, 38.5);
  
  for (auto& ele : RaddamCorrections) {
    if (ele.first > 0)
      raddCorrsPlus->Fill( ele.first, ele.second);
    else
      raddCorrsMinus->Fill( fabs(ele.first), ele.second);
    std::cout << "iEta " << setw(4) << ele.first << ": " << ele.second << std::endl;
  }

  drawFactors( raddCorrsPlus, raddCorrsMinus);
}

void factorCalcOld() {
  int num = EtaMinus_RaddamCorrections.size();
  for (int i = 0; i < num; ++i)
    std::cout << "iEta -" << i+30 << ": " 
	      << EtaMinus_RaddamCorrections[i] * EtaMinus_RaddamFactors[i] << std::endl;

  for (int i = 0; i < num; ++i)
    std::cout << "iEta +" << i+30 << ": " 
	      << EtaPlus_RaddamCorrections[i] * EtaPlus_RaddamFactors[i] << std::endl;
}
