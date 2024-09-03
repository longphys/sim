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

	void AddDEdep(G4double dedep, G4int NoDet){
    fDEdep[NoDet] += dedep;
  }
	void AddEdep(G4double edep, G4int NoDet){
    fEdep[NoDet] += edep;
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

  int events = 0;
};

#endif
