#include <iostream>

#include "TRandom3.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"

void drawVer()
{
  TFile* file = new TFile("out.root", "read");

  TTree* tree = (TTree*) file->Get("verTree");

  std::vector <double> *xVer, *yVer;
  tree->SetBranchAddress("xVer", &xVer);
  tree->SetBranchAddress("yVer", &yVer);

  int size = (*xVer).size();
  std::cout << "size = " << size << "\n";

  // double x, y;
	// TGraph* gr = new TGraph(size, x, y);
	// gr->SetMarkerStyle(7);
	// gr->SetMarkerColor(kBlue);

	// TCanvas* c1 = new TCanvas("c1", "c1", 700, 700);
	// c1->cd();

	// gr->Draw("AP");
}
