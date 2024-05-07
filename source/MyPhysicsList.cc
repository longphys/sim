#include "MyPhysicsList.hh"

MyPhysicsList::MyPhysicsList()
{
// Here we will add/register new "Physics lists" or interactions, pre-defined by Geant4
	RegisterPhysics (new G4EmStandardPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
