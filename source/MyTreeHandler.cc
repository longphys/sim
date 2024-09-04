#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
    fFile = new TFile();
    fTree = new TTree("dEEtree", "dEEtree");
    fEventNr = -1;

    // for(int i = 0; i <= 6; i++){
    //   fdE[i] = 0.;
    //   fE[i] = 0.;
    // }

    fdE = 0.;
    fE = 0.;

    fcomptNr = -1;
    fcomptEDep.clear();

    // neutronEDep.clear();
    // protonEDep.clear();
    // gammaEDep.clear();
    // otherEDep.clear();

    neutronEDep = 0.;
    protonEDep = 0.;
    gammaEDep = 0.;
    otherEDep = 0.;
    
    fTree->Branch("EventID", &fEventNr, "EventID/I");
    
    fTree->Branch("Scintillator", &fdE, "Scintillator/D");
    // fTree->Branch("Scintillator", &fdE[0], "Scintillator/D");
    // fTree->Branch("Scintillator1", &fdE[1], "Scintillator1/D");
    // fTree->Branch("Scintillator2", &fdE[2], "Scintillator2/D");
    // fTree->Branch("Scintillator3", &fdE[3], "Scintillator3/D");
    // fTree->Branch("Scintillator4", &fdE[4], "Scintillator4/D");
    // fTree->Branch("Scintillator5", &fdE[5], "Scintillator5/D");
    // fTree->Branch("Scintillator6", &fdE[6], "Scintillator6/D");

    fTree->Branch("PMT", &fE, "PMT/D");
    // fTree->Branch("PMT", &fE[0], "PMT/D");
    // fTree->Branch("PMT1", &fE[1], "PMT1/D");
    // fTree->Branch("PMT2", &fE[2], "PMT2/D");
    // fTree->Branch("PMT3", &fE[3], "PMT3/D");
    // fTree->Branch("PMT4", &fE[4], "PMT4/D");
    // fTree->Branch("PMT5", &fE[5], "PMT5/D");
    // fTree->Branch("PMT6", &fE[6], "PMT6/D");

    // fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
    // fTree->Branch("ComptonEnergyDeposition", &fcomptEDep);
    // fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");

    // fTree->Branch("NeutronEDep", &neutronEDep);
    // fTree->Branch("ProtonEDep", &protonEDep);
    // fTree->Branch("GammaEDep", &gammaEDep);
    // fTree->Branch("OtherEDep", &otherEDep);

    fTree->Branch("NeutronEDep", &neutronEDep, "NeutronEDep/D");
    fTree->Branch("ProtonEDep", &protonEDep, "ProtonEDep/D");
    fTree->Branch("GammaEDep", &gammaEDep, "GammaEDep/D");
    fTree->Branch("OtherEDep", &otherEDep, "OtherEDep/D");
}

G4int MyTreeHandler::Open()
{
    fFile = TFile::Open("out.root", "recreate");
    return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr,
        G4double dE, 
        G4double E, 
        // G4double dE[7], 
        // G4double E[7], 
        int64_t comptNr, 
        std::vector <G4double> comptEDep,
        G4double backEDep,
        // std::vector <G4double> neutronE,
        // std::vector <G4double> protonE,
        // std::vector <G4double> gammaE,
        // std::vector <G4double> otherE
        G4double neutronE,
        G4double protonE,
        G4double gammaE,
        G4double otherE
        )
{
    fEventNr = eventNr;

    // for(int i = 0; i <= 6; i++){
    //   fdE[i] = dE[i];
    //   fE[i] = E[i];
    // }

    fdE = dE;
    fE = E;

    fcomptNr = comptNr;
    fcomptEDep = comptEDep;
    fbackEDep = backEDep;

    neutronEDep = neutronE;
    protonEDep = protonE;
    gammaEDep = gammaE;
    otherEDep = otherE;

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
