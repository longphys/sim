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

  std::vector <double> *xVer = nullptr;
  std::vector <double> *yVer = nullptr;
  
  TBranch *bxVer = nullptr;
  TBranch *byVer = nullptr;
  
  tree->SetBranchAddress("xVer", &xVer, &bxVer);
  tree->SetBranchAddress("yVer", &yVer, &byVer);

  int size = xVer->size();
  std::cout << "size = " << size << "\n";

  // double x, y;
	// TGraph* gr = new TGraph(size, xVer, yVer);
	// gr->SetMarkerStyle(7);
	// gr->SetMarkerColor(kBlue);

	// TCanvas* c1 = new TCanvas("c1", "c1", 700, 700);
	// c1->cd();

	// gr->Draw("AP");
}
