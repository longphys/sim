#ifndef MyEventAction_hh
#define MyEventAction_hh

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "MyTreeHandler.hh"

#include "globals.hh"
#include "Randomize.hh"

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction() = default;
	~MyEventAction() override = default;
	
	virtual void BeginOfEventAction(const G4Event* event);
	virtual void EndOfEventAction(const G4Event* event);

	void AddDEdep(G4double dedep) { fDEdep += dedep; }
	void AddDEdepL(G4double dedep) { fDEdepL += dedep; }
	void AddDEdepR(G4double dedep) { fDEdepR += dedep; }

	void AddEdep(G4double edep) { fEdep += edep; }
	void AddEdepL(G4double edep) { fEdepL += edep; }
	void AddEdepR(G4double edep) { fEdepR += edep; }

	void AddComptCount() { fcomptCount += 1; }
	void AddInfo(G4String StepInfo) { AllStepInfo += '\n' + StepInfo; }
	void SwitchBS() { aBSCheck = true; }
private:
	G4double fEdep, fEdepL, fEdepR, fDEdep, fDEdepL, fDEdepR, backEDep;
	
	G4int fcomptCount;
	G4String AllStepInfo;
	G4bool aBSCheck;
	std::vector <G4double> comptEDep;
};

#endif
