#include "MyTreeHandler.hh"

#include "G4ios.hh"

MyTreeHandler::MyTreeHandler()
{
    fFile = new TFile();
    fTree = new TTree("dEEtree", "dEEtree");
    fEventNr = -1;

      fdE.clear();
      fE.clear();

    // fdE = 0.;
    // fE = 0.;

    fcomptNr = -1;
    fcomptEDep.clear();

    neutronEDep.clear();
    neutronEDep.resize(7,0.);
    protonEDep.clear();
    protonEDep.resize(7,0.);
    gammaEDep.clear();
    gammaEDep.resize(7,0.);
    alphaEDep.clear();
    alphaEDep.resize(7,0.);
    C12EDep.clear();
    C12EDep.resize(7,0.);
    otherEDep.clear();
    otherEDep.resize(7,0.);

    // neutronEDep = 0.;
    // protonEDep = 0.;
    // gammaEDep = 0.;
    // alphaEDep = 0.;
    // C12EDep = 0.;
    // otherEDep = 0.;
    
    fTree->Branch("EventID", &fEventNr, "EventID/I");
    
    // fTree->Branch("Scintillator", &fdE, "Scintillator/D");
    fTree->Branch("Scintillator", &fdE);
    // fTree->Branch("Scintillator", &fdE[0], "Scintillator/D");
    // fTree->Branch("Scintillator1", &fdE[1], "Scintillator1/D");
    // fTree->Branch("Scintillator2", &fdE[2], "Scintillator2/D");
    // fTree->Branch("Scintillator3", &fdE[3], "Scintillator3/D");
    // fTree->Branch("Scintillator4", &fdE[4], "Scintillator4/D");
    // fTree->Branch("Scintillator5", &fdE[5], "Scintillator5/D");
    // fTree->Branch("Scintillator6", &fdE[6], "Scintillator6/D");

    // fTree->Branch("PMT", &fE, "PMT/D");
    fTree->Branch("PMT", &fE);
    // fTree->Branch("PMT", &fE[0], "PMT/D");
    // fTree->Branch("PMT1", &fE[1], "PMT1/D");
    // fTree->Branch("PMT2", &fE[2], "PMT2/D");
    // fTree->Branch("PMT3", &fE[3], "PMT3/D");
    // fTree->Branch("PMT4", &fE[4], "PMT4/D");
    // fTree->Branch("PMT5", &fE[5], "PMT5/D");
    // fTree->Branch("PMT6", &fE[6], "PMT6/D");

    fTree->Branch("ComptonInteractions", &fcomptNr, "ComptonInteractions/L");
    fTree->Branch("ComptonEnergyDeposition", &fcomptEDep);
    fTree->Branch("BackScatteredComptonEnergyDeposition", &fbackEDep, "BackScatteredComptonEnergyDeposition/D");

    fTree->Branch("NeutronEDep", &neutronEDep);
    fTree->Branch("ProtonEDep", &protonEDep);
    fTree->Branch("GammaEDep", &gammaEDep);
    fTree->Branch("AlphaEDep", &alphaEDep);
    fTree->Branch("C12EDep", &C12EDep);
    fTree->Branch("OtherEDep", &otherEDep);

    // fTree->Branch("NeutronEDep", &neutronEDep, "NeutronEDep/D");
    // fTree->Branch("ProtonEDep", &protonEDep, "ProtonEDep/D");
    // fTree->Branch("GammaEDep", &gammaEDep, "GammaEDep/D");
    // fTree->Branch("AlphaEDep", &alphaEDep, "AlphaEDep/D");
    // fTree->Branch("C12EDep", &C12EDep, "C12EDep/D");
    // fTree->Branch("OtherEDep", &otherEDep, "OtherEDep/D");
}

G4int MyTreeHandler::Open()
{
    fFile = TFile::Open("out.root", "recreate");
    return 0;
}

G4int MyTreeHandler::Push(int64_t eventNr,
        // G4double dE, 
        // G4double E, 
        std::vector <G4double> dE,
        std::vector <G4double> E, 
        int64_t comptNr, 
        std::vector <G4double> comptEDep,
        G4double backEDep,

        std::vector <G4double> neutronE,
        std::vector <G4double> protonE,
        std::vector <G4double> gammaE,
        std::vector <G4double> alphaE,
        std::vector <G4double> C12E,
        std::vector <G4double> otherE

        // G4double neutronE,
        // G4double protonE,
        // G4double gammaE,
        // G4double alphaE,
        // G4double C12E,
        // G4double otherE
        )
{
    fEventNr = eventNr;

    fdE = dE;
    fE = E;

    // fdE = dE;
    // fE = E;

    fcomptNr = comptNr;
    fcomptEDep = comptEDep;
    fbackEDep = backEDep;

    neutronEDep = neutronE;
    protonEDep = protonE;
    gammaEDep = gammaE;
    alphaEDep = alphaE;
    C12EDep = C12E;
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
