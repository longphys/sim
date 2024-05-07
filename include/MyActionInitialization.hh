#ifndef MyActionInitialization_hh
#define MyActionInitialization_hh

#include "G4VUserActionInitialization.hh"

#include "MyPrimaryGenerator.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MySteppingAction.hh"

#include "MyTreeHandler.hh"

class MyActionInitialization: public G4VUserActionInitialization // Inhereting from Geant4 class
{
public:
	MyActionInitialization();
	virtual ~MyActionInitialization();
	
	virtual void BuildForMaster() const;
	virtual void Build() const;
	// why virtual?
	// A "Build" function from Geant4 Action class (virtual, the same as that of "construction.hh"), which will run the particle gun and compute the stepping.
};
#endif
