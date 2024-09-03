#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
    fFile = new TFile();
    fTree = new TTree("dEEtree", "dEEtree");
    fEventNr = -1;

    for(int i = 0; i < 7; i++){
      fdE[i] = 0.;
      fE[i] = 0.;
    }

    fcomptNr = -1;
    fcomptEDep.clear();
    
    fTree->Branch("EventID", &fEventNr, "EventID/I");
    
    fTree->Branch("Scintillator", &fdE, "Scintillator/D");

    fTree->Branch("PMT", &fE, "PMT/D");

    // fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
    // fTree->Branch("ComptonEnergyDeposition", &fcomptEDep, "ComptonEnergyDepostion/D");
    // fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");
}

G4int MyTreeHandler::Open()
{
    fFile = TFile::Open("out.root", "recreate");
    return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr, 
        G4double dE[7], 
        G4double E[7], 
        int64_t comptNr, 
        std::vector <G4double> comptEDep, G4double backEDep)
{
    fEventNr = eventNr;

    for(int i = 0; i < 7; i++){
      fdE[i] = dE[i];
      fE[i] = E[i];
    }

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
    // G4cout << "fEventNr = " << fEventNr << ": fdE = " << fdE << ": fE = " << fE << "\n";

    return 0;
}
