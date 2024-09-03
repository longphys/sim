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
        G4double dE[7], 
        G4double E[7], 
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

        G4double fdE[7];
        G4double fE[7];
        G4double fbackEDep;
        
        int64_t fcomptNr;
        std::vector <G4double> fcomptEDep;
        
};

#endif
