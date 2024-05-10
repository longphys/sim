#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
  //fFile = new TFile("out.root", "recreate");
  fFile = new TFile();
  fTree = new TTree("dEEtree", "dEEtree");
  fEventNr = -1;
  fdE = -1.0;
  fdEL = -1.0;
  fdER = -1.0;
  fE = -1.0;
  fEL = -1.0;
  fER = -1.0;
  fcomptNr = -1;
  fcomptEDep.clear();
  
  fTree->Branch("EventID", &fEventNr, "EventID/I");
  
  fTree->Branch("Scintillator", &fdE, "Scintillator/D");
  fTree->Branch("ScintillatorL", &fdEL, "ScintillatorL/D");
  fTree->Branch("ScintillatorR", &fdER, "ScintillatorR/D");

  fTree->Branch("PMT", &fE, "PMT/D");
  fTree->Branch("PMTL", &fEL, "PMTL/D");
  fTree->Branch("PMTR", &fER, "PMTR/D");

  fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
  fTree->Branch("ComptonEnergyDeposition", &fcomptEDep);
  fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");
}

G4int MyTreeHandler::Open()
{
  fFile = TFile::Open("out.root", "recreate");
  return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr, G4double dE, G4double dEL, 
G4double dER, G4double E, G4double EL, G4double ER, int64_t comptNr, 
std::vector <G4double> comptEDep, G4double backEDep)
{
  fEventNr = eventNr;

  fdE = dE;
  fdEL = dEL;
  fdER = dER;
  
  fE = E;
  fEL = EL;
  fER = ER;

  fcomptNr = comptNr;
  fcomptEDep = comptEDep;
  fbackEDep = backEDep;

  fTree->Fill();

  return 0;
}

G4int MyTreeHandler::Close()
{
  fTree->Write();
  fFile->Close();

  return 0;
}

G4int MyTreeHandler::Print()
{
  G4cout << "fEventNr = " << fEventNr << ": fdE = " << fdE << ": fE = " << fE << "\n";

  return 0;
}
