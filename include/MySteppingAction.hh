#ifndef MySteppingAction_hh
#define MySteppingAction_hh

#include "G4UserSteppingAction.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"

#include "MyDetectorConstruction.hh"
#include "MyPrimaryGenerator.hh"
#include "MyEventAction.hh"

#include "globals.hh"

class MyEventAction;

class G4LogicalVolume;

class MySteppingAction : public G4UserSteppingAction
{
public:
	MySteppingAction(MyEventAction* eventAction);
	virtual ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);
private:
  MyEventAction* fEventAction;

  G4LogicalVolume *fDEScoringVolume, *fDEScoringVolume1, *fDEScoringVolume2, 
  *fEScoringVolume, *fEScoringVolume1, *fEScoringVolume2;

 
};

#endif
