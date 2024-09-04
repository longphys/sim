#ifndef MyTreeHandler_hh
#define MyTreeHandler_hh

#include "G4Types.hh"

#include "TFile.h"
#include "TTree.h"

class MyTreeHandler
{
    public: 
        MyTreeHandler(const MyTreeHandler& aTreeHandler) = delete;
        static MyTreeHandler* GetInstance()
        {
            if (fTreeHandlerPtr == NULL)
            {
                fTreeHandlerPtr = new MyTreeHandler();
                return fTreeHandlerPtr;
            }
            else
            {
                return fTreeHandlerPtr;
            }
        }
        G4int Push(int64_t eventNr,
        // G4double dE[7], 
        // G4double E[7], 
        G4double dE,
        G4double E,
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
        );
        
        G4int Open();
        G4int Close();
        G4int Print();

    protected:
        static MyTreeHandler* fTreeHandlerPtr;

        MyTreeHandler();

        TFile* fFile;
        TTree* fTree;
        int64_t fEventNr;

        // G4double fdE[7];
        // G4double fE[7];

        G4double fdE;
        G4double fE;

        G4double fbackEDep;
        
        int64_t fcomptNr;
        std::vector <G4double> fcomptEDep;

        // std::vector <G4double> neutronEDep;
        // std::vector <G4double> protonEDep;
        // std::vector <G4double> gammaEDep;
        // std::vector <G4double> otherEDep;

        G4double neutronEDep;
        G4double protonEDep;
        G4double gammaEDep;
        G4double otherEDep;
};

#endif
