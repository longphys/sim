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
        G4int Push(int64_t eventNr, G4double dE, G4double dEL, 
        G4double dER, G4double E, G4double EL, G4double ER, int64_t comptNr, 
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

        G4double fdE, fdEL, fdER,
        fE, fEL, fER, fbackEDep;
        
        int64_t fcomptNr;
        std::vector <G4double> fcomptEDep;
        
};

#endif
