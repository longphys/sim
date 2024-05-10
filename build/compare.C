#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1D.h"
#include "TF1.h"
#include "TLegend.h"
#include "TRandom3.h"

void compare()
{
  //! Files and trees
  TFile* fsimCs137 = new TFile("withAl_simCs137.root", "read");
  TFile* fsimNa22 = new TFile("withAl_simNa22.root", "read");
  TFile* fexpCs137 = new TFile("old_divider_Cs137_ch0_9751_ch1_9800_ch2_9841_run_0_0001.root", "read");
  TFile* fexpNa22 = new TFile("old_divider_Na22_ch0_9751_ch1_9800_ch2_9841_run_0_0001.root", "read");

  TTree* tsimCs137 =  (TTree*) fsimCs137->Get("dEEtree");
  TTree* tsimNa22 =  (TTree*) fsimNa22->Get("dEEtree");
  TTree* texpCs137 =  (TTree*) fexpCs137->Get("AnalysisxTree");
  TTree* texpNa22 =  (TTree*) fexpNa22->Get("AnalysisxTree");

  //! Calibration
  double a = 0.002633333333333;
  double b = -0.254766666666667;

  //! Resolution coefficients

  double coA = 0.01;
  double coB = 0.001;
  double coC = 0.01;

  //! histogram options
  int binSim = 1300;
  int binExp = 700;
  double xminSim = 0.;
  double xmaxSim = 1.3;
  double xminExp = 100;
  double xmaxExp = 800;

  TH1D* hsimCs137 = new TH1D("hsimCs137", "Cs137 Simulation", binSim, xminSim, xmaxSim);
  TH1D* hsimNa22 = new TH1D("hsimNa22", "Na22 Simulation", binSim, xminSim, xmaxSim);
  TH1D* hexpCs137 = new TH1D("hexpCs137", "Cs137 Experiment", binExp, xminExp, xmaxExp);
  TH1D* hexpNa22 = new TH1D("hexpNa22", "Na22 Experiment", binExp, xminExp, xmaxExp);

  TH1D* hcalCs137 = new TH1D("hCalexpCs137", "Cs137 Experiment Calibrated", binExp, xminExp*a+b, xmaxExp*a+b);
  TH1D* hcalNa22 = new TH1D("hcalNa22", "Na22 Experiment Calibrated", binExp, xminExp*a+b, xmaxExp*a+b);

  hsimCs137->GetXaxis()->SetTitle("Energy(MeV)");
  hsimCs137->GetYaxis()->SetTitle("Count");
  hsimNa22->GetXaxis()->SetTitle("Energy(MeV)");
  hsimNa22->GetYaxis()->SetTitle("Count");

  //! Fill experiment histograms
  UShort_t x_exp[48], y_exp[48];

  texpCs137->SetBranchAddress("NeEvent.neutAmp[48]", x_exp);
  texpNa22->SetBranchAddress("NeEvent.neutAmp[48]", y_exp);

  Long64_t entries = texpCs137->GetEntries();

  for(int i = 0; i < entries; i++){
    texpCs137->GetEntry(i);
    hcalCs137->Fill(a*(x_exp[0]+0.5) + b);
  }
  
  entries = texpNa22->GetEntries();

  for(int i = 0; i < entries; i++){
    texpNa22->GetEntry(i);
    hcalNa22->Fill(a*(y_exp[0]+0.5) + b);
  }

  //! Resolution for simulation histograms
  double x_sim, y_sim;

  tsimCs137->SetBranchAddress("Scintillator", &x_sim);
  tsimNa22->SetBranchAddress("Scintillator", &y_sim);

  TRandom3* ranGen = new TRandom3();

  entries = tsimCs137->GetEntries();

  for (int i = 0; i < entries; i++)
  {
    tsimCs137->GetEntry(i);
    double sigma = sqrt( pow(coA, 2) + pow(coB/sqrt(x_sim), 2) + pow(coC/x_sim, 2) );
    if(ranGen->Gaus(x_sim, sigma) <= 0.00001)
    {
      continue;
    }
    hsimCs137->Fill(ranGen->Gaus(x_sim, sigma));
  }

  entries = tsimNa22->GetEntries();

  for (int i = 0; i < entries; i++)
  {
    tsimNa22->GetEntry(i);
    double sigma = sqrt( pow(coA,2) + pow(coB/sqrt(y_sim),2) + pow(coC/y_sim,2) );
    hsimNa22->Fill(ranGen->Gaus(y_sim,sigma));
  }

  //! Canvas and draw
  TCanvas *c1 = new TCanvas("c1", "c1", 1600, 800);
  c1->cd();
  c1->Divide(2, 1);

  c1->cd(1);
  hsimCs137->Draw();
  hcalCs137->SetLineColor(kRed);
  hcalCs137->Scale(0.52);
  hcalCs137->Draw("same L");

  TLegend *leg1 = new TLegend(0.75, 0.6, 0.98, 0.75);
  leg1->SetHeader("Cs137", "C");
  leg1->SetBorderSize(2);
  leg1->AddEntry(hsimCs137, "simulation", "l");
  leg1->AddEntry(hcalCs137, "experiment", "l");
  leg1->Draw();

  c1->cd(2);
  hsimNa22->Draw();
  hcalNa22->SetLineColor(kRed);
  hcalNa22->Scale(0.057);
  hcalNa22->Draw("same L");

  TLegend *leg2 = new TLegend(0.75, 0.6, 0.98, 0.75);
  leg2->SetHeader("Na22", "C");
  leg2->SetBorderSize(2);
  leg2->AddEntry(hsimNa22, "simulation", "l");
  leg2->AddEntry(hcalNa22, "experiment", "l");
  leg2->Draw();

}