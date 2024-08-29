#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
    //fFile = new TFile("out.root", "recreate");
    fFile = new TFile();
    fTree = new TTree("dEEtree", "dEEtree");
    fEventNr = -1;
    fdE = -1.0;
    fdE1 = -1.0;
    fdE2 = -1.0;
    fE = -1.0;
    fE1 = -1.0;
    fE2 = -1.0;
    fcomptNr = -1;
    fcomptEDep.clear();
    
    fTree->Branch("EventID", &fEventNr, "EventID/I");
    
    fTree->Branch("Scintillator", &fdE, "Scintillator/D");
    fTree->Branch("ScintillatorL", &fdE1, "ScintillatorL/D");
    fTree->Branch("ScintillatorR", &fdE2, "ScintillatorR/D");

    fTree->Branch("PMT", &fE, "PMT/D");
    fTree->Branch("PMTL", &fE1, "PMTL/D");
    fTree->Branch("PMTR", &fE2, "PMTR/D");

    fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
    fTree->Branch("ComptonEnergyDeposition", &fcomptEDep);
    fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");
}

G4int MyTreeHandler::Open()
{
    fFile = TFile::Open("out.root", "recreate");
    return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr, G4double dE, G4double dE1, 
G4double dE2, G4double E, G4double E1, G4double E2, int64_t comptNr, 
std::vector <G4double> comptEDep, G4double backEDep)
{
    fEventNr = eventNr;

    fdE = dE;
    fdE1 = dE1;
    fdE2 = dE2;
    
    fE = E;
    fE1 = E1;
    fE2 = E2;

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
