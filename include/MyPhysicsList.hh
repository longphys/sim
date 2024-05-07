#ifndef MyPhysicsList_hh
#define MyPhysicsList_hh

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"

class MyPhysicsList : public G4VModularPhysicsList // Create a new class that inherets from the implemented "G4VModularPhysicsList" from Geant4
{
public:
	MyPhysicsList();
	virtual ~MyPhysicsList();
};
#endif
