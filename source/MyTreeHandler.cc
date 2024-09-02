#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
    fFile = new TFile();
    fTree = new TTree("dEEtree", "dEEtree");
    fEventNr = -1;

    fdE = -1.0;
    fdE1 = -1.0;
    fdE2 = -1.0;
    fdE3 = -1.0;
    fdE4 = -1.0;
    fdE5 = -1.0;
    fdE6 = -1.0;
    
    fE = -1.0;
    fE1 = -1.0;
    fE2 = -1.0;
    fE3 = -1.0;
    fE4 = -1.0;
    fE5 = -1.0;
    fE6 = -1.0;
    fcomptNr = -1;
    fcomptEDep.clear();
    
    fTree->Branch("EventID", &fEventNr, "EventID/I");
    
    fTree->Branch("Scintillator", &fdE, "Scintillator/D");
    fTree->Branch("Scintillator1", &fdE1, "Scintillator1/D");
    fTree->Branch("Scintillator2", &fdE2, "Scintillator2/D");
    fTree->Branch("Scintillator3", &fdE3, "Scintillator3/D");
    fTree->Branch("Scintillator4", &fdE4, "Scintillator4/D");
    fTree->Branch("Scintillator5", &fdE5, "Scintillator5/D");
    fTree->Branch("Scintillator6", &fdE6, "Scintillator6/D");

    fTree->Branch("PMT", &fE, "PMT/D");
    fTree->Branch("PMT1", &fE1, "PMT1/D");
    fTree->Branch("PMT2", &fE2, "PMT2/D");
    fTree->Branch("PMT3", &fE3, "PMT3/D");
    fTree->Branch("PMT4", &fE4, "PMT4/D");
    fTree->Branch("PMT5", &fE5, "PMT5/D");
    fTree->Branch("PMT6", &fE6, "PMT6/D");

    // fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
    // fTree->Branch("ComptonEnergyDeposition", &fcomptEDep);
    // fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");
}

G4int MyTreeHandler::Open()
{
    fFile = TFile::Open("out.root", "recreate");
    return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr, 
        G4double dE, 
        G4double dE1, G4double dE2, G4double dE3, 
        G4double dE4, G4double dE5, G4double dE6, 
        G4double E, 
        G4double E1, G4double E2, G4double E3, 
        G4double E4, G4double E5, G4double E6, 
        int64_t comptNr, 
        std::vector <G4double> comptEDep, G4double backEDep)
{
    fEventNr = eventNr;

    fdE = dE;
    fdE1 = dE1;
    fdE2 = dE2;
    fdE3 = dE3;
    fdE4 = dE4;
    fdE5 = dE5;
    fdE6 = dE6;
    
    fE = E;
    fE1 = E1;
    fE2 = E2;
    fE3 = E3;
    fE4 = E4;
    fE5 = E5;
    fE6 = E6;

    // fcomptNr = comptNr;
    // fcomptEDep = comptEDep;
    // fbackEDep = backEDep;

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
