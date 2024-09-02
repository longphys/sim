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
        G4double dE, 
        G4double dE1, G4double dE2, G4double dE3, 
        G4double dE4, G4double dE5, G4double dE6, 
        G4double E, 
        G4double E1, G4double E2, G4double E3, 
        G4double E4, G4double E5, G4double E6, 
        int64_t comptNr, 
        std::vector <G4double> comptEDep, G4double backEDep);
        G4int Open();
        G4int Close();
        G4int Print();

    protected:
        static MyTreeHandler* fTreeHandlerPtr;

        MyTreeHandler();

        TFile* fFile;
        TTree* fTree;
        int64_t fEventNr;

        G4double fdE, fdE1, fdE2,
        fdE3, fdE4,
        fdE5, fdE6,
        fE, fE1, fE2,
        fE3, fE4,
        fE5, fE6, 
        fbackEDep;
        
        int64_t fcomptNr;
        std::vector <G4double> fcomptEDep;
        
};

#endif
