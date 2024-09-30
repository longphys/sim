#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH1D.h"
#include "TF1.h"
#include "TLegend.h"
#include "TRandom3.h"
#include "TStopwatch.h"

double A = 1.;
double kB; //? (mm/MeV)

// double birk(double E, std::string par){
//   if (par == "neutron"){
//     return E;
//   }
//   else if (par == "gamma"){
//     return E;
//   }
//   else if (par == "proton"){
//     if ()
//     return ( E/(1+kB*E) );
//   }
// };

void readNeutronSim()
{
  auto timer = new TStopwatch();
  timer->Start();

  TFile* file = new TFile("out.root", "read");
  TTree* tree =  (TTree*) file->Get("dEEtree");

  TRandom3* ranGen = new TRandom3();

  //! histogram options
  double xmin = 0.;
  double xmax = 20.;

  int bin = (xmax - xmin)*100;

  TH1D* hist1 = new TH1D("hist1", "Simulation original", bin, xmin, xmax);
  TH1D* hist2 = new TH1D("hist2", "Simulation modified", bin, xmin, xmax);
  TH1D* hist3 = new TH1D("hist3", "Simulation", bin, xmin, xmax);
  TH1D* hist4 = new TH1D("hist4", "Simulation", bin, xmin, xmax);

  TCanvas* c1 = new TCanvas("c1", "c1", 1500, 1000);
  int cols = 2;
  int rows = 1;
  c1->Divide(cols, rows);

  c1->cd(1);
  hist1->GetXaxis()->SetTitle("Energy(Mev)");
  hist1->GetYaxis()->SetTitle("Count");
  tree->Draw("Scintillator[0]>>hist1");

  c1->cd(2);
  std::vector <double> *neutronE = nullptr;
  std::vector <double> *protonE = nullptr;
  std::vector <double> *gammaE = nullptr;
  std::vector <double> *alphaE = nullptr;
  std::vector <double> *c12E = nullptr;
  std::vector <double> *otherE = nullptr;

  tree->SetBranchAddress("NeutronEDep", &neutronE);
  tree->SetBranchAddress("ProtonEDep", &protonE);
  tree->SetBranchAddress("GammaEDep", &gammaE);
  tree->SetBranchAddress("AlphaEDep", &alphaE);
  tree->SetBranchAddress("C12EDep", &c12E);
  tree->SetBranchAddress("OtherEDep", &otherE);

  unsigned int entries = tree->GetEntriesFast();
  for (int i = 0; i < entries; i++){
    tree->GetEntry(i);

    int neutronE_size = neutronE->size();
    int protonE_size = protonE->size();
    int gammaE_size = gammaE->size();
    int alphaE_size = alphaE->size();
    int c12E_size = c12E->size();
    int otherE_size = otherE->size();

    double* neutronE_data = neutronE->data();
    double* protonE_data = protonE->data();
    double* gammaE_data = gammaE->data();
    double* alphaE_data = alphaE->data();
    double* c12E_data = c12E->data();
    double* otherE_data = otherE->data();

    hist2->Fill(neutronE_data[0]+protonE_data[0]+gammaE_data[0]+alphaE_data[0]+c12E_data[0]+otherE_data[0]);
  }

  hist2->GetXaxis()->SetTitle("Energy(Mev)");
  hist2->GetYaxis()->SetTitle("Count");
  hist2->Draw();
}