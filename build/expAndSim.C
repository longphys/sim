#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1D.h"
#include "TF1.h"
#include "TLegend.h"

void expAndSim()
{
  TFile* file1 = new TFile("simCs137.root", "read");
  TFile* file2 = new TFile("simNa22.root", "read");
  TFile* file3 = new TFile("new_passive_divider_ch2_Cs137_ch0_9751_ch1_9800_ch2_9841_run_0_0001.root", "read");
  TFile* file4 = new TFile("new_passive_divider_ch2_Na22_ch0_9751_ch1_9800_ch2_9841_run_0_0001.root", "read");

  TTree* tree1 =  (TTree*) file1->Get("dEEtree");
  TTree* tree2 =  (TTree*) file2->Get("dEEtree");
  TTree* tree3 =  (TTree*) file3->Get("AnalysisxTree");
  TTree* tree4 =  (TTree*) file4->Get("AnalysisxTree");

  // histogram options
  int binSim = 1300;
  int binExp = 700;
  double xminSim = 0.;
  double xmaxSim = 1.3;
  double xminExp = 100;
  double xmaxExp = 800;

  TH1D* hist1 = new TH1D("hist1", "Cs137 Simulation", binSim, xminSim, xmaxSim);
  TH1D* hist2 = new TH1D("hist2", "Na22 Simulation", binSim, xminSim, xmaxSim);
  TH1D* hist3 = new TH1D("hist3", "Cs137 Experiment", binExp, xminExp, xmaxExp);
  TH1D* hist4 = new TH1D("hist4", "Na22 Experiment", binExp, xminExp, xmaxExp);

  TCanvas* c1 = new TCanvas("c1", "c1", 1500, 1000);
  int cols = 2;
  int rows = 2;
  c1->cd();
  c1->Divide(cols, rows);

  c1->cd(1);
  c1->cd(1)->SetGridx();
  c1->cd(1)->SetGridy();
  hist1->SetLineColor(kBlack);
  hist1->GetXaxis()->SetTitle("Energy(Mev)");
  hist1->GetYaxis()->SetTitle("Count");
  
  tree1->Draw("Scintillator>>hist1", "Scintillator>0");

  c1->cd(2);
  c1->cd(2)->SetGridx();
  c1->cd(2)->SetGridy();
  hist2->SetLineColor(kBlack);
  hist2->GetXaxis()->SetTitle("Energy(Mev)");
  hist2->GetYaxis()->SetTitle("Count");
  
  tree2->Draw("Scintillator>>hist2", "Scintillator>0");

  c1->cd(3);
  c1->cd(3)->SetGridx();
  c1->cd(3)->SetGridy();
  hist3->GetXaxis()->SetTitle("Channel");
  hist3->GetYaxis()->SetTitle("Count");
  
  tree3->Draw("NeEvent.neutAmp[0]>>hist3", "");

  TF1 *fEnergySpread = new TF1("function", "[0]*x+[1]", 250, 300);
  hist3->Fit(fEnergySpread, "", "", 274, 286);

  c1->cd(4);
  c1->cd(4)->SetGridx();
  c1->cd(4)->SetGridy();
  hist4->GetXaxis()->SetTitle("Channel");
  hist4->GetYaxis()->SetTitle("Count");
  
  tree4->Draw("NeEvent.neutAmp[0]>>hist4", "");

  TCanvas* c2 = new TCanvas("c2", "c2", 1400, 700);
  c2->cd();
  c2->Divide(2, 1);
  c2->cd(1);
  c2->cd(1)->SetGridx();
  c2->cd(1)->SetGridy();
  double a = 0.002633333333333;
  double b = -0.254766666666667;

  // double a = 0.0021246;
  // double b = -0.0004077;
  
  // TH1D* hist5 = new TH1D("hist5", "Cs137", 800, b, 800*a+b);
  TH1D* hist5 = new TH1D("hist5", "Cs137", binExp, xminExp*a+b, xmaxExp*a+b);
  // TH1D* hist5 = new TH1D("hist5", "Cs137", 800, 0*a+b, 800*a+b);

  Long64_t entries = tree3->GetEntries();
  std::cout << "entries = " << entries << "\n";

  hist5->GetXaxis()->SetTitle("Energy(MeV)");
  hist5->GetYaxis()->SetTitle("Count");

  UShort_t x[48];
  tree3->SetBranchAddress("NeEvent.neutAmp[48]", x);

  for(int i = 0; i < entries; i++){
  // for(int i = 0; i < 10; i++){
    tree3->GetEntry(i);
    std::cout << x[0] << std::endl;
    // std::cout << a*x[0] + b << std::endl;
    // hist5->Fill(a*x[0] + b);
    hist5->Fill(a*(x[0]+0.5) + b);
  }
  hist5->Draw();

  c2->cd(2);
  c2->cd(2)->SetGridx();
  c2->cd(2)->SetGridy();
  
  TH1D* hist6 = new TH1D("hist6", "Na22", binExp, xminExp*a+b, xmaxExp*a+b);

  entries = tree4->GetEntries();
  std::cout << "entries = " << entries << "\n";

  hist6->GetXaxis()->SetTitle("Energy(MeV)");
  hist6->GetYaxis()->SetTitle("Count");

  UShort_t y[48];
  tree4->SetBranchAddress("NeEvent.neutAmp[48]", y);

  for(int i = 0; i < entries; i++){
    tree4->GetEntry(i);
    hist6->Fill(a*(y[0]+0.5) + b);
  }
  hist6->Draw();

  TCanvas *c3 = new TCanvas("c3", "c3", 1400, 700);
  c3->cd();
  c3->Divide(2, 1);

  c3->cd(1);
  hist1->Draw();
  hist5->SetLineColor(kRed);
  hist5->Scale(0.075);
  hist5->Draw("same L");

  TLegend *leg1 = new TLegend(0.75, 0.6, 0.98, 0.75);
  leg1->SetBorderSize(2);
  leg1->AddEntry(hist1, "simulation", "l");
  leg1->AddEntry(hist5, "experiment", "l");
  leg1->Draw();

  c3->cd(2);
  hist2->Draw();
  hist6->SetLineColor(kRed);
  hist6->Scale(0.01);
  hist6->Draw("same L");

  TLegend *leg2 = new TLegend(0.75, 0.6, 0.98, 0.75);
  leg2->SetBorderSize(2);
  leg2->AddEntry(hist2, "simulation", "l");
  leg2->AddEntry(hist6, "experiment", "l");
  leg2->Draw();

}