void demonstration(){
  TFile* file = new TFile("out.root", "read");
  TTree* tree =  (TTree*) file->Get("dEEtree");
  
  double a_res = 0.0552472;
  double b_res = 0.;
  double c_res = 0.0209245;
  
  double e1;
  double e2;
  double e3;
  
  tree->SetBranchAddress("Scintillator", &e1);
  tree->SetBranchAddress("ScintillatorL", &e2);
  tree->SetBranchAddress("ScintillatorR", &e3);
  
  TH1D* hist1 = new TH1D("hist1", "hist1", 1600, 0.1, 1.6);
  TH1D* hist2 = new TH1D("hist2", "hist2", 1600, 0.1, 1.6);
  
  TRandom3* ranGen = new TRandom3();
  for (int i = 0; i < tree->GetEntries(); i++)
  {
    tree->GetEntry(i);
    
    hist1->Fill(e1);
    hist1->Fill(e2);
    hist1->Fill(e3);
    
    double sigma1 = e1*sqrt( pow(a_res,2) + pow(b_res/sqrt(e1),2) + pow(c_res/e1,2) );
    double energy1 = ranGen->Gaus(e1,sigma1);
    
    double sigma2 = e2*sqrt( pow(a_res,2) + pow(b_res/sqrt(e2),2) + pow(c_res/e2,2) );
    double energy2 = ranGen->Gaus(e2,sigma2);
    
    double sigma3 = e3*sqrt( pow(a_res,2) + pow(b_res/sqrt(e3),2) + pow(c_res/e3,2) );
    double energy3 = ranGen->Gaus(e3,sigma3);
    
    hist2->Fill(energy1);
    hist2->Fill(energy2);
    hist2->Fill(energy3);
  }
  
  TCanvas* canvas1 = new TCanvas("canvas1", "canvas1", 800, 800);
  canvas1->cd();
  hist1->Draw();
  
  TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 800, 800);
  canvas2->cd();
  hist2->Draw();
  
  TCanvas* canvas3 = new TCanvas("canvas3", "canvas3", 800, 800);
  canvas3->cd();
  //hist3->Draw();
}
