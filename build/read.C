#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1D.h"
#include "TF1.h"
#include "TLegend.h"

void read()
{
  TFile* file1 = new TFile("out.root", "read");
  TTree* tree1 =  (TTree*) file1->Get("dEEtree");

  // histogram options
  int binSim = 1300;
  int binExp = 700;
  double xminSim = 0.;
  double xmaxSim = 1.3;
  double xminExp = 100;
  double xmaxExp = 800;

  TH1D* hist1 = new TH1D("hist1", "Simulation", binSim, xminSim, xmaxSim);
  TH1D* hist2 = new TH1D("hist2", "Simulation", binSim, xminSim, xmaxSim);
  TH1D* hist3 = new TH1D("hist3", "Simulation", binSim, xminSim, xmaxSim);
  TH1D* hist4 = new TH1D("hist4", "Simulation", binSim, xminSim, xmaxSim);

  TCanvas* c1 = new TCanvas("c1", "c1", 1500, 1000);
  int cols = 2;
  int rows = 2;
  c1->cd();
  c1->Divide(cols, rows);

  c1->cd(1);
  hist1->GetXaxis()->SetTitle("Energy(Mev)");
  hist1->GetYaxis()->SetTitle("Count");
  
  tree1->Draw("Scintillator[0]>>hist1");

  c1->cd(2);
  hist2->GetXaxis()->SetTitle("Energy(Mev)");
  hist2->GetYaxis()->SetTitle("Count");
  
  tree1->Draw("Scintillator[1]>>hist2");

  c1->cd(3);
  hist3->GetXaxis()->SetTitle("Energy(Mev)");
  hist3->GetYaxis()->SetTitle("Count");
  
  tree1->Draw("Scintillator[2]>>hist3");

  c1->cd(4);
  hist4->GetXaxis()->SetTitle("Energy(Mev)");
  hist4->GetYaxis()->SetTitle("Count");
  
  tree1->Draw("Scintillator[3]>>hist4");

}