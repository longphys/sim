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

	// void AddDEdep(G4double edep){
  //   fDEdep += edep;
  // }
	// void AddEdep(G4double edep){
  //   fEdep += edep;
  // }

  void AddParEdep(G4double edep, G4String parName, G4int NoDet){
    // if(parName == "neutron"){
    //   neutronEDep += edep;
    // }
    // else if(parName == "proton"){
    //   protonEDep += edep;
    // }
    // else if(parName == "gamma"){
    //   gammaEDep += edep;
    // }
    // else if(parName == "alpha"){
    //   alphaEDep += edep;
    // }
    // else if(parName == "C12"){
    //   C12EDep += edep;
    // }
    // else{
    //   otherEDep += edep;
    // }

    if(parName == "neutron"){
      neutronEDep[NoDet] += edep;
    }
    else if(parName == "proton"){
      protonEDep[NoDet] += edep;
    }
    else if(parName == "gamma"){
      gammaEDep[NoDet] += edep;
    }
    else if(parName == "alpha"){
      alphaEDep[NoDet] += edep;
    }
    else if(parName == "C12"){
      C12EDep[NoDet] += edep;
    }
    else{
      otherEDep[NoDet] += edep;
    }
  }

	void AddComptCount() { fcomptCount += 1; }
	void AddInfo(G4String StepInfo) { AllStepInfo += '\n' + StepInfo; }

	void SwitchBS() { aBSCheck = true; }

  void CheckProton() { protonCheck = true; }
  void CheckGamma() { gammaCheck = true; }
  void CheckAlpha() { alphaCheck = true; }
  void CheckC12() { c12Check = true; }

private:
	G4double backEDep;
	
	G4int fcomptCount;
	G4String AllStepInfo;
	G4bool aBSCheck, protonCheck, gammaCheck, alphaCheck, c12Check;
	std::vector <G4double> comptEDep;

  std::vector <G4double> fEdep, fDEdep;
  // G4double fEdep[7], fDEdep[7];
  // G4double fEdep, fDEdep;

	std::vector <G4double> neutronEDep, protonEDep, gammaEDep, alphaEDep, C12EDep, otherEDep;
  // G4double neutronEDep, protonEDep, gammaEDep, alphaEDep, C12EDep, otherEDep;

  G4int count = 0;
};

#endif
