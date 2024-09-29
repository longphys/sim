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
  double xmin = 0.;
  double xmax = 15.;

  int bin = (xmax - xmin)*100;

  TH1D* hist1 = new TH1D("hist1", "Simulation", bin, xmin, xmax);
  TH1D* hist2 = new TH1D("hist2", "Simulation", bin, xmin, xmax);
  TH1D* hist3 = new TH1D("hist3", "Simulation", bin, xmin, xmax);
  TH1D* hist4 = new TH1D("hist4", "Simulation", bin, xmin, xmax);

  TCanvas* c1 = new TCanvas("c1", "c1", 1500, 1000);
  int cols = 2;
  int rows = 2;
  c1->cd();
  c1->Divide(cols, rows);

  c1->cd(1);
  hist1->GetXaxis()->SetTitle("Energy(Mev)");
  hist1->GetYaxis()->SetTitle("Count");
  
  // tree1->Draw("Scintillator[0]>>hist1");
  tree1->Draw("OtherEDep[0]>>hist1", "AlphaEDep[0]>0", "same");

  c1->cd(2);
  hist2->GetXaxis()->SetTitle("Energy(Mev)");
  hist2->GetYaxis()->SetTitle("Count");
  
  // tree1->Draw("Scintillator[1]>>hist2");
  tree1->Draw("ProtonEDep[1]>>hist2", "ProtonEDep[1]>0", "same");

  c1->cd(3);
  hist3->GetXaxis()->SetTitle("Energy(Mev)");
  hist3->GetYaxis()->SetTitle("Count");
  
  // tree1->Draw("Scintillator[2]>>hist3");
  tree1->Draw("ProtonEDep[2]>>hist3", "ProtonEDep[2]>0", "same");

  c1->cd(4);
  hist4->GetXaxis()->SetTitle("Energy(Mev)");
  hist4->GetYaxis()->SetTitle("Count");
  
  tree1->Draw("Scintillator[3]>>hist4");
}