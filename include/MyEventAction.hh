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
	void AddDEdep1(G4double dedep) { fDEdep1 += dedep; }
	void AddDEdep2(G4double dedep) { fDEdep2 += dedep; }
	void AddDEdep3(G4double dedep) { fDEdep3 += dedep; }
	void AddDEdep4(G4double dedep) { fDEdep4 += dedep; }
	void AddDEdep5(G4double dedep) { fDEdep5 += dedep; }
	void AddDEdep6(G4double dedep) { fDEdep6 += dedep; }

	void AddEdep(G4double edep) { fEdep += edep; }
	void AddEdep1(G4double edep) { fEdep1 += edep; }
	void AddEdep2(G4double edep) { fEdep2 += edep; }
	void AddEdep3(G4double edep) { fEdep3 += edep; }
	void AddEdep4(G4double edep) { fEdep4 += edep; }
	void AddEdep5(G4double edep) { fEdep5 += edep; }
	void AddEdep6(G4double edep) { fEdep6 += edep; }

	void AddComptCount() { fcomptCount += 1; }
	void AddInfo(G4String StepInfo) { AllStepInfo += '\n' + StepInfo; }
	void SwitchBS() { aBSCheck = true; }
private:
	G4double fEdep, fEdep1, fEdep2, fEdep3, fEdep4, fEdep5, fEdep6, fDEdep, fDEdep1, fDEdep2, fDEdep3, fDEdep4, fDEdep5, fDEdep6, backEDep;
	
	G4int fcomptCount;
	G4String AllStepInfo;
	G4bool aBSCheck;
	std::vector <G4double> comptEDep;
};

#endif
