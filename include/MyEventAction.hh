#ifndef MyEventAction_hh
#define MyEventAction_hh

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "MyTreeHandler.hh"

#include "globals.hh"
#include "Randomize.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "MyRunAction.hh"

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction() = default;
	~MyEventAction() override = default;
	
	virtual void BeginOfEventAction(const G4Event* event);
	virtual void EndOfEventAction(const G4Event* event);

	void AddDEdep(G4double edep, G4int NoDet){
    fDEdep[NoDet] += edep;
  }
	void AddEdep(G4double edep, G4int NoDet){
    fEdep[NoDet] += edep;
  }

  void AddParEdep(G4double edep, G4String parName, G4int parentID){
    // if(parName == "neutron"){
    //   neutronEDep.resize(parentID+1, 0.);
    //   neutronEDep[parentID] += edep;
    // }
    // else if(parName == "proton"){
    //   protonEDep.resize(parentID+1, 0.);
    //   protonEDep[parentID] += edep;
    // }
    // else if(parName == "gamma"){
    //   gammaEDep.resize(parentID+1, 0.);
    //   gammaEDep[parentID] += edep;
    // }
    // else{
    //   otherEDep.resize(parentID+1, 0.);
    //   otherEDep[parentID] += edep;
    // }

    if(parName == "neutron"){
      neutronEDep += edep;
    }
    else if(parName == "proton"){
      protonEDep += edep;
    }
    else if(parName == "gamma"){
      gammaEDep += edep;
    }
    else{
      otherEDep += edep;
    }
  }

	void AddComptCount() { fcomptCount += 1; }
	void AddInfo(G4String StepInfo) { AllStepInfo += '\n' + StepInfo; }
	void SwitchBS() { aBSCheck = true; }
private:
	G4double backEDep;
	
	G4int fcomptCount;
	G4String AllStepInfo;
	G4bool aBSCheck;
	std::vector <G4double> comptEDep;
  G4double fEdep[7], fDEdep[7];
	// std::vector <G4double> neutronEDep, protonEDep, gammaEDep, otherEDep;
  G4double neutronEDep, protonEDep, gammaEDep, otherEDep;

  int events = 0;
};

#endif
